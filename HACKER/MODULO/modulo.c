/* slightly smarter backtracking algorithm:
   take corners first, then take row-major order and zero out
   as we go */

/* TODO prune on cells that cannot be flipped to 0 (near corners) because
   of block shapes */

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>

typedef long long ll;

#define BUF 10000000
char buffer[BUF];
char name[1000],pw[1000];
int bptr;

void error(char *s) {
	puts(s);
	exit(1);
}

/* need to collect everything in one huge buffer, as data can be split in the
   middle of a line */
size_t webline(void *ptr,size_t size,size_t n,void *userdata) {
	int i;
	char *t=(char *)ptr;
	for(i=0;t[i];i++) buffer[bptr++]=t[i];
	buffer[bptr]=0;
	return n;
}

void loadwebpage(char *url) {
	CURL *curl=curl_easy_init();
	CURLcode res;
	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,webline);
	bptr=0;
	res=curl_easy_perform(curl);
	curl_easy_cleanup(curl);
}

char *strstr2(char *hay,char *needle) {
	char *p=strstr(hay,needle);
	if(!p) return 0;
	return p+strlen(needle);
}

void readlevel() {
  static char s[1000];
  sprintf(s,"http://www.hacker.org/modulo/index.php?name=%s&password=%s",name,pw);
  loadwebpage(s);
}

#define MAXX 20
#define MAXY 20
#define MAXP 40 /* max number of pieces */
#define MAXB 50 /* max area of piece */

int depth;
char board[MAXX][MAXY];
int x,y;
int px[MAXP][MAXB],py[MAXP][MAXB]; /* piece (0,0 is implicit) */
int pz[MAXP];                      /* number of entries in px,py */
int ex1[MAXP],ex2[MAXP],ey[MAXP];  /* block extent: minx maxx maxy */
int pn;                            /* number of pieces */
char pieces[MAXP][MAXX][MAXY];     /* actual piece data */
int pcx[MAXP],pcy[MAXP];           /* block size */

void parselevel() {
	char *p;
	int i,j,xx,yy,ux,uy;
	char piece[MAXX][MAXY];
	if(bptr<1000) printf("seems webpage didn't load properly"),error(buffer);
	if(!(p=strstr2(buffer,"><param name=\"depth\" value=\""))) error("vrael");
	depth=strtol(p,0,10);
	if(!(p=strstr2(buffer,"<param name=\"board\" value=\""))) error("vrael");
	for(x=0;p[x]!=',';x++);
	if(x>MAXX) error("increase MAXX and recompile");
	for(y=0;;) {
		if(y==MAXY) puts("increase MAXY and recompile");
		for(i=0;i<x;i++) board[i][y]=p[i]-'0';
		y++;
		if(p[x]!=',') break;
		p+=x+1;
	}
	if(!(p=strstr2(buffer,"<param name=\"pieces\" value=\""))) error("vrael");
	for(pn=0;;) {
		if(pn==MAXP) error("increase MAXP and recompile");
		for(xx=0;p[xx]=='X' || p[xx]=='.';xx++);
		for(yy=0;;) {
			for(i=0;i<xx;i++) piece[i][yy]=p[i];
			yy++;
			if(p[xx]!=',') break;
			p+=xx+1;
		}
		p+=xx;
		/* parse block */
		for(ux=uy=-1,j=0;j<yy;j++) for(i=0;i<xx;i++) if(piece[i][j]=='X') {
			ux=i; uy=j; goto ok;
		}
	ok:
		for(i=0;i<xx;i++) for(j=0;j<yy;j++) pieces[pn][i][j]=piece[i][j]=='X'?1:0;
		pcx[pn]=xx; pcy[pn]=yy;
		pz[pn]=0;
		ex1[pn]=0; ex2[pn]=0; ey[pn]=0;
		for(j=0;j<yy;j++) for(i=0;i<xx;i++) if(piece[i][j]=='X' && (i!=ux || j!=uy)) {
			if(pz[pn]==MAXB) error("increase MAXB and recompile");
			px[pn][pz[pn]]=i-ux;
			py[pn][pz[pn]++]=j-uy;
			if(ex1[pn]>i-ux) ex1[pn]=i-ux;
			if(ex2[pn]<i-ux) ex2[pn]=i-ux;
			if(ey[pn]<j-uy) ey[pn]=j-uy;
		}
		pn++;
		if(*p!=' ') break;
		p++;
	}
//	for(i=0;i<pn;i++) {printf("block %d [w %d h %d]:",i,ex2[i]-ex1[i]+1,ey[i]+1);for(j=0;j<pz[i];j++) printf(" (%d %d)",px[i][j],py[i][j]);printf("\n");}
}

char taken[MAXP];
int pathx[MAXP],pathy[MAXP];
#define INC(u,v) {board[(u)][(v)]++; if(board[(u)][(v)]==depth) board[(u)][(v)]=0;}
#define DEC(u,v) {board[(u)][(v)]--; if(board[(u)][(v)]<0) board[(u)][(v)]=depth-1;}

void printboard() {
	int i,j;
	for(j=0;j<y;j++) {
		for(i=0;i<x;i++) printf("%d",board[i][j]);
		printf("\n");
	}
}

int probe;
int heur;
ll teller,tot;
int restartteller=0;
int MOD=1;

int btr(int at,int atx,int aty) {
	int i,x1,y1,left,can=0,x2,y2,j;
/*	printf("at %d atx %d aty %d\n",at,atx,aty);
	for(i=0;i<pn;i++) printf("%d",taken[i]);printf("\n");
	for(i=0;i<pn;i++) if(taken[i]) printf("  took %d: %d %d\n",i,pathx[i],pathy[i]);
	printboard();puts("----------------");*/
again:
	if(atx==x) atx=0,aty++;
	if((atx==0 || atx==x-1) && (aty==0 || aty==y-1)) { atx++; goto again; }
	/* dubious heuristic: only place pieces such that its upper left clears something */
	if(heur && aty<y && !board[atx][aty]) { atx++; goto again; }
	/* did we win? */
	for(i=0;i<x;i++) for(j=0;j<y;j++) if(board[i][j]) goto ok1;
	/* board is empty, check for unplaced blocks */
	for(i=0;i<pn;i++) if(!taken[i]) break;
	return i==pn;
ok1:
	/* prune on no pieces left before clearing board */
	for(i=0;i<pn;i++) if(!taken[i]) goto ok;
	return 0;
ok:
	/* prune on high piece */
	for(i=0;i<pn;i++) if(!taken[i] && y-aty<pcy[i]) return 0;
	/* prune on wide piece that can't avoid lower corners */
	for(i=0;i<pn;i++) if(!taken[i] && y-aty==pcy[i] && pcx[i]>x-2) {
		if(pcx[i]==x && (pieces[i][0][pcy[i]-1] || pieces[i][4][pcy[i]-1])) return 0;
		else if(pcx[i]==x-1 && pieces[i][0][pcy[i]-1] && pieces[i][3][pcy[i]-1]) return 0;
	}
	/* prune on number of flips needed > number of cells in remaining pieces */
	x1=atx; y1=aty; left=0;
	while(y1<y) {
		if(board[x1][y1]) left+=depth-board[x1][y1];
		x1++; if(x1==x) x1=0,y1++;
	}
	for(i=0;i<pn;i++) if(!taken[i]) can+=1+pz[i];
//	printf("at %d %d: left %d can %d\n",atx,aty,left,can);
	if(left>can) return 0;
	/* try next cell */
	if(!board[atx][aty] && btr(0,atx+1,aty)) return 1;
	/* try a piece */
	for(;at<pn;at++) if(!taken[at]) {
		/* only place piece if it fits within grid and doesn't flip any corners */
		if(atx+ex1[at]<0) continue;
		if(atx+ex2[at]>=x) continue;
		x1=atx; y1=aty;
		for(i=0;i<pz[at];i++) {
			x2=x1+px[at][i]; y2=y1+py[at][i];
			if((x2==0 || x2==x-1) && (y2==0 || y2==y-1)) goto skip;
		}
		pathx[at]=x1+ex1[at]; pathy[at]=y1;
		INC(x1,y1)
		for(i=0;i<pz[at];i++) INC(x1+px[at][i],y1+py[at][i])
		taken[at]=1;
		if(btr(at+1,atx,aty)) return 1;
		DEC(x1,y1)
		for(i=0;i<pz[at];i++) DEC(x1+px[at][i],y1+py[at][i])
		taken[at]=0;
	skip:;
	}
	return 0;
}

/* try all combinations that leave lower left blank that don't affect the other 3 corners */
int btrlowerright(int at) {
	int i,x1,y1;
	for(;at<pn;at++) if(!taken[at] && pieces[at][pcx[at]-1][pcy[at]-1]) {
		x1=x-ex2[at]-1;
		y1=y-pcy[at];
		/* touch lower left? */
		if(pcx[at]==x && pieces[at][0][pcy[at]-1]) continue;
		/* touch upper right? */
		if(pcy[at]==y && pieces[at][pcx[at]-1][0]) continue;
		/* touch upper left? */
		if(pcy[at]==y && pcx[at]==x && pieces[at][0][0]) continue;
		INC(x1,y1)
		for(i=0;i<pz[at];i++) INC(x1+px[at][i],y1+py[at][i])
		pathx[at]=x1+ex1[at]; pathy[at]=y1;
		taken[at]=1;
//		printf("lr: place %d at %d,%d\n",at,x1,y1);
		if(btrlowerright(at+1)) return 1;
		DEC(x1,y1)
		for(i=0;i<pz[at];i++) DEC(x1+px[at][i],y1+py[at][i])
		taken[at]=0;
	}
	if(!board[x-1][y-1]) {
		if(probe) { teller++; return 0;}
		else {
			teller++;
			if(teller-1<restartteller) return 0;
			if((teller-1)%MOD==0) {
				if(heur) printf("{%I64d/%I64d} ",teller-1,tot);
				else printf("[%I64d/%I64d] ",teller-1,tot);
			}
			return btr(0,1,0);
		}
	}
	return 0;
}

/* try all combinations that leave lower left blank that don't affect upper corners */
int btrlowerleft(int at) {
	int i,x1,y1;
//	printf("at lower left: ");for(i=0;i<pn;i++) printf("%d",taken[i]);printf("\n");printboard();
	for(;at<pn;at++) if(!taken[at] && pieces[at][0][pcy[at]-1]) {
		x1=-ex1[at];
		y1=y-pcy[at];
		if(pcy[at]==y) {
			/* touch upper left? */
			if(pieces[at][0][0]) continue;
			/* touch upper right? */
			if(pieces[at][x-1][0]) continue;
		}
		INC(x1,y1)
		for(i=0;i<pz[at];i++) INC(x1+px[at][i],y1+py[at][i])
		pathx[at]=x1+ex1[at]; pathy[at]=y1;
		taken[at]=1;
//		printf("ll: place %d at %d,%d\n",at,x1,y1);
		if(btrlowerleft(at+1)) return 1;
		DEC(x1,y1)
		for(i=0;i<pz[at];i++) DEC(x1+px[at][i],y1+py[at][i])
		taken[at]=0;
	}
	if(!board[0][y-1]) return btrlowerright(0);
	return 0;
}

/* try all combinations that leave upper right blank that don't affect upper left */
int btrupperright(int at) {
	int i,x1,y1;
//	printf("at upper right, at %d: ",at);for(i=0;i<pn;i++) printf("%d",taken[i]);printf("\n");printboard();
	for(;at<pn;at++) if(!taken[at] && pieces[at][pcx[at]-1][0]) {
		if(pcx[at]==x && pieces[at][0][0]) continue;
		x1=x-ex2[at]-1;
		if(x1+ex1[at]<0) continue;
		y1=0;
		INC(x1,y1)
//		printf("ur: place %d at %d,%d\n",at,x1,y1);
		for(i=0;i<pz[at];i++) INC(x1+px[at][i],y1+py[at][i])
		pathx[at]=x1+ex1[at]; pathy[at]=y1;
		taken[at]=1;
		if(btrupperright(at+1)) return 1;
		DEC(x1,y1)
		for(i=0;i<pz[at];i++) DEC(x1+px[at][i],y1+py[at][i])
		taken[at]=0;
	}
	if(!board[x-1][0]) return btrlowerleft(0);
	return 0;
}

/* try all combinations that leave upper left blank */
int btrupperleft(int at) {
	int i;
	for(;at<pn;at++) if(!ex1[at] && !taken[at]) {
		/* apply block at upper left block can reach cell */
		INC(0,0)
//		printf("ul: place %d at 0,0\n",at);
		for(i=0;i<pz[at];i++) INC(px[at][i],py[at][i])
		pathx[at]=0; pathy[at]=0;
		taken[at]=1;
		if(btrupperleft(at+1)) return 1;
		DEC(0,0)
		for(i=0;i<pz[at];i++) DEC(px[at][i],py[at][i])
		taken[at]=0;
	}
	if(!board[0][0]) return btrupperright(0);
	return 0;
}

int restartheur=1,restartmod=0;

void solve() {
	int i,j;
	printf("solve level (modulo %d), %d pieces\n",depth,pn);
	for(j=0;j<y;j++) {
		for(i=0;i<x;i++) printf("%d",board[i][j]);
		printf("\n");
	}
	memset(taken,0,pn);
	probe=1; teller=tot=0;
	btrupperleft(0);
	tot=teller; probe=0;
	if(restartmod) MOD=restartmod,restartmod=0;
	else {
		MOD=1;
		while(teller/MOD>100000) MOD*=10;
	}
	if(restartheur<1) goto heur0;
	teller=0;
	printf("%I64d ways to do corners\n",tot);
	heur=1;
	if(btrupperleft(0)) return;
	printf("\n");
heur0:
	heur=0;
	teller=0;
	if(!btrupperleft(0)) error("error, couldn't find solution");
	restartheur=1;
	restartteller=0;
}

void submit() {
	static char s[10000000];
	int p,i,q;
	CURL *curl;
	CURLcode res;
	sprintf(s,"name=%s&password=%s&seq=",name,pw);
	q=p=strlen(s);
	for(i=0;i<pn;i++) {
		sprintf(s+p,"%02d%02d",pathx[i],pathy[i]);
		p+=strlen(s+p);
	}
	printf("\nfound solution, submitting [%s]\n",s+q);
	curl_global_init(CURL_GLOBAL_ALL);
	curl=curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl,CURLOPT_URL,"http://www.hacker.org/modulo/index.php");
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,s);
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,webline);
		bptr=0;
		res=curl_easy_perform(curl);
		if(CURLE_OK!=res) printf("failed post %s\n",curl_easy_strerror(res)),exit(1);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	if(bptr<1000) {
		printf("looks like level wasn't solved properly\n");
		puts(buffer);
		exit(1);
	}
}

int main(int argc,char **argv) {
	if(argc<3) error("usage: stupid name password");
	srand(time(0));
	strcpy(name,argv[1]);
	strcpy(pw,argv[2]);
	if(argc>3) restartteller=strtol(argv[3],0,10);
	if(argc>4) restartheur=strtol(argv[4],0,10);
	if(argc>5) restartmod=strtol(argv[5],0,10);
	while(1) {
		readlevel();
		parselevel();
		solve();
		submit();
	}
	return 0;
}
