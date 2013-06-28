/* backtracking from both sides with meet-in-the-middle
   use bitstate hashing to check for existence */

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>

typedef long long ll;
typedef unsigned char uchar;

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
char pieces[MAXP][MAXX][MAXY];     /* actual piece data (1:cell, 0:no cell) */
int pcx[MAXP],pcy[MAXP];           /* block size */
int pcn[MAXP];                     /* number of cells in piece */
int pn;                            /* number of pieces */
int pid[MAXP];
int prefix[MAXP];

void parselevel() {
	char *p;
	int i,j,xx,yy;
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
			for(i=0;i<xx;i++) piece[i][yy]=p[i]=='X'?1:0;
			yy++;
			if(p[xx]!=',') break;
			p+=xx+1;
		}
		p+=xx;
		/* parse block */
		pcn[pn]=0;
		for(i=0;i<xx;i++) for(j=0;j<yy;j++)
			pieces[pn][i][j]=piece[i][j],pcn[pn]+=pieces[pn][i][j];
		pcx[pn]=xx; pcy[pn]=yy;
		pn++;
		if(*p!=' ') break;
		p++;
	}
//	for(i=0;i<pn;i++) {printf("block %d [w %d h %d]:",i,ex2[i]-ex1[i]+1,ey[i]+1);for(j=0;j<pz[i];j++) printf(" (%d %d)",px[i][j],py[i][j]);printf("\n");}
}

int pathx[MAXP],pathy[MAXP];
int targetx,targety,tat;
#define INC(board,u,v) {board[(u)][(v)]++; if(board[(u)][(v)]==depth) board[(u)][(v)]=0;}
#define DEC(board,u,v) {board[(u)][(v)]--; if(board[(u)][(v)]<0) board[(u)][(v)]=depth-1;}

void printboard(char board[MAXX][MAXY]) {
	int i,j;
	for(j=0;j<y;j++) {
		for(i=0;i<x;i++) printf("%d",board[i][j]);
		printf("\n");
	}
}

ll MAXHASH=20000000000LL;
ll MAXELEM;
int meet;

#define MAXBIT 2
uchar *bit[MAXBIT];
ll prim[MAXBIT];
int mul[MAXBIT];

int isprime(ll z) {
	int i;
	if(z<4) return z>1;
	if(z%2==0) return 0;
	for(i=3;(ll)i*i<=z;i+=2) if(z%i==0) return 0;
	return 1;
}

void initbitstate() {
	ll p=MAXHASH;
	int i;
	for(i=0;i<MAXBIT;i++) {
		p--;
		while(!isprime(p)) p--;
		prim[i]=p;
	}
	for(i=0;i<MAXBIT;i++) if(!(bit[i]=malloc((prim[i]+7)/8))) error("out of mem");
	for(i=0;i<MAXBIT;i++) mul[i]=5+i*2;
}

void freebitstate() {
	int i;
	for(i=MAXBIT-1;i>=0;i--) free(bit[i]);
}

char board2[MAXX][MAXY];

ll gethash(char b[MAXX][MAXY],int ix) {
	ll h=0;
	int i,j;
	for(i=0;i<x;i++) for(j=0;j<y;j++) h=(h*mul[ix]+b[i][j])%prim[ix];
	return h;
}

void puthash(char b[MAXX][MAXY]) {
	ll h;
	int i;
	for(i=0;i<MAXBIT;i++) {
		h=gethash(b,i);
		bit[i][h>>3]|=1<<(h&7);
	}
}

int exists(char b[MAXX][MAXY]) {
	ll h;
	int i;
	for(i=0;i<MAXBIT;i++) {
		h=gethash(b,i);
		if(!(bit[i][h>>3]&(1<<(h&7)))) return 0;
	}
	return 1;
}

ll iter;
ll fail;
#define MOD 1
#define MODB 1000000

ll pruned[MAXP],prune;

void btrback(int at) {
	int i,j,k,l;
	if(at==meet-1) {
		if(++iter%MODB==0) printf("%I64d ",iter/MODB);
		return puthash(board2);
	}
	for(i=0;i<=x-pcx[at];i++) for(j=0;j<=y-pcy[at];j++) {
		for(k=0;k<pcx[at];k++) for(l=0;l<pcy[at];l++) if(pieces[at][k][l]) DEC(board2,i+k,j+l);
		btrback(at-1);
		for(k=0;k<pcx[at];k++) for(l=0;l<pcy[at];l++) if(pieces[at][k][l]) INC(board2,i+k,j+l);
	}
}

int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

int calcprune2() {
	int left=0,i,j;
	for(i=0;i<x;i++) for(j=0;j<y;j++) if(board[i][j]) left+=depth-board[i][j];
	return left;
}

/* TODO only use this function if there are no 1x1 blocks to be placed */
int calcprune() {
	int left=0,i,j,x2,y2,d,h=0;
	static char z[MAXX][MAXY];
	for(i=0;i<x;i++) for(j=0;j<y;j++) z[i][j]=0;
	for(i=0;i<x;i++) for(j=0;j<y;j++) if(board[i][j]) {
		left+=depth-board[i][j];
		for(d=0;d<4;d++) {
			x2=i+dx[d];
			y2=j+dy[d];
			if(x2<0 || y2<0 || x2>=x || y2>=y) continue;
			if(board[x2][y2]) goto fail;
		}
		h=depth; goto tral;
	fail:;
	}
	for(i=0;i<x;i++) for(j=0;j<y;j++) if(board[i][j]) {
		left+=depth-board[i][j];
		tral:;
	}
	return left+h;
}

/* TODO! for each remaining piece left, try all ways to place it. take
   max of all pieces (min of all ways to place piece) of the number of 0-cells
   that the piece is placed on */
int calcprune3(int at) {
	int left=0,i,j,best=0,cur,k,l,m,z,cnt=0;
	for(i=0;i<x;i++) for(j=0;j<y;j++) if(board[i][j]) left+=depth-board[i][j];
	/* for each piece */
	for(m=at;cnt<2 && m<pn && best<pcn[m];m++,cnt++) {
		/* try all ways to place piece */
		z=1000000;
		/* for each piece: place the piece so that the minimum number of 0-cells
		   are covered (or covers as many non-0-cells as possible) */
		for(i=0;i<=x-pcx[m];i++) for(j=0;j<=y-pcy[m];j++) {
			cur=0;
			for(k=0;k<pcx[m];k++) for(l=0;l<pcy[m];l++) if(pieces[m][k][l] && !board[i+k][j+l]) {
				cur+=depth;
				if(cur>=z) goto again;
			}
			if(z>cur) z=cur;
		again:;
		}
		if(best<z) best=z;
	}
	return left+best;
}

int btrfront2(int at) {
	int i,j,k,l,left;
	if(at==meet) {
		if(++iter%MOD==0) printf("%I64d ",iter/MOD);
	}
	else {
		left=calcprune3(at);
		if(left>prefix[at]) return 0;
	}
	if(at==pn) return 1;
	for(i=0;i<=x-pcx[at];i++) for(j=0;j<=y-pcy[at];j++) {
		for(k=0;k<pcx[at];k++) for(l=0;l<pcy[at];l++) if(pieces[at][k][l]) INC(board,i+k,j+l);
		pathx[pid[at]]=i; pathy[pid[at]]=j;
		if(btrfront2(at+1)) return 1;
		for(k=0;k<pcx[at];k++) for(l=0;l<pcy[at];l++) if(pieces[at][k][l]) DEC(board,i+k,j+l);
	}
	return 0;
}

#define FRONT 100000
#define PRUNE 10000000

int btrfront(int at) {
	int i,j,k,l,left;
	/* prune */
	left=calcprune3(at);
	if(left>prefix[at]) {
		pruned[at]++;
		prune++;
		if(prune%PRUNE==0) {
			printf("at:");
			for(i=0;i<at;i++) printf(" (%d %d)",pathx[pid[i]],pathy[pid[i]]);printf("\n");
			printf("prune:");
			for(i=0;i<=meet;i++) printf(" %I64d",pruned[i]);printf("\n");
		}
		return 0;
	}
	if(at==meet) {
		if(++fail%FRONT==0) printf("[%I64d] ",fail/FRONT);
		return exists(board) && btrfront2(at);
	}
	for(i=0;i<=x-pcx[at];i++) for(j=0;j<=y-pcy[at];j++) {
		if(at==tat && (i<targetx || (i==targetx && j<targety))) continue;
		for(k=0;k<pcx[at];k++) for(l=0;l<pcy[at];l++) if(pieces[at][k][l]) INC(board,i+k,j+l);
		pathx[pid[at]]=i; pathy[pid[at]]=j;
		if(btrfront(at+1)) return 1;
		for(k=0;k<pcx[at];k++) for(l=0;l<pcy[at];l++) if(pieces[at][k][l]) DEC(board,i+k,j+l);
	}
	return 0;
}

void solve() {
	int i,j,k,l,t;
	double comb=1,z;
	MAXELEM=MAXHASH/20;
	/* sort blocks, most cells first */
	for(i=0;i<pn;i++) pid[i]=i;
	for(i=0;i<pn;i++) for(j=0;j<pn-1;j++) if(pcn[j]<pcn[j+1]) {
		t=pid[j],pid[j]=pid[j+1],pid[j+1]=t;
		t=pcn[j],pcn[j]=pcn[j+1],pcn[j+1]=t;
		t=pcx[j],pcx[j]=pcx[j+1],pcx[j+1]=t;
		t=pcy[j],pcy[j]=pcy[j+1],pcy[j+1]=t;
		for(k=0;k<x;k++) for(l=0;l<y;l++)
			t=pieces[j][k][l],pieces[j][k][l]=pieces[j+1][k][l],pieces[j+1][k][l]=t;
	}
	prefix[pn]=0;
	for(i=pn-1;i>=0;i--) prefix[i]=prefix[i+1]+pcn[i];
	/* find sweet spot for meet-in-the-middle */
	for(meet=pn,i=pn-1;;i--) {
		if(i<pn-1 && i+i<=pn+2) { meet=i+1; break; }
		z=comb*(x-pcx[i]+1.)*(y-pcy[i]+1.);
		if(z>MAXELEM) { meet=i+1; break; }
		comb=z;
	}
	for(z=1,i=0;i<meet;i++) z*=(x-pcx[i]+1.)*(y-pcy[i]+1.);
	printf("meet at %d/%d, comb (%.f | %.f)\n",meet,pn,z,comb);
	memset(board2,0,sizeof(board2));
	iter=0;
	initbitstate();
	btrback(pn-1);
	iter=0;
	fail=0;
	prune=0;
	memset(pruned,0,sizeof(pruned));
	puts("back done");
	if(!btrfront(0)) puts("not solved");
	freebitstate();
	tat=-1;
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
	targetx=targety=tat=-1;
	if(argc>5) {
		tat=strtol(argv[3],0,10);
		targetx=strtol(argv[4],0,10);
		targety=strtol(argv[5],0,10);
	}
	while(1) {
		readlevel();
		parselevel();
		solve();
		submit();
	}
	return 0;
}
