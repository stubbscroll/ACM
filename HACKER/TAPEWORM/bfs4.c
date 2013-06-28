/* stupid algorithm for tapeworm: pure BFS followed by random moves
   from each unpopped queue element when memory is full */
/* bfs v4: store directions instead of explicit worm coordinates for
   massive memory savings */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
  sprintf(s,"http://www.hacker.org/tapeworm/index.php?name=%s&password=%s",name,pw);
  loadwebpage(s);
}

#define MAXX 20
#define MAXY 20
#define MAXW 10  /* number of worms */
#define MAXL 100 /* max worm length */

char board[MAXX][MAXY];
char vis[MAXX][MAXY];
int x,y;
int wx[MAXW][MAXL],wy[MAXW][MAXL]; /* worm pos (normalized) */
int wcol[MAXW];                    /* worm colour */
int wlen[MAXW];                    /* length of worm */
int wn;                            /* number of worms */
int level;

int half;                          /* 1:coordinates are small, pack both x,y
                                      in one byte */

void printboard() {
	int i,j;
	for(j=0;j<y;j++) {
		for(i=0;i<x;i++) printf("%d",board[i][j]);
		printf("\n");
	}
}

void printworms() {
	int i,j;
	for(i=0;i<wn;i++) if(wlen[i]) {
		printf("worm %d len %d:",i,wlen[i]);
		for(j=0;j<wlen[i];j++) printf(" (%d %d)",wx[i][j],wy[i][j]);
		printf("\n");
	}
}

void swapworm(int id,int a,int b) {
	 int t;
	 t=wx[id][a]; wx[id][a]=wx[id][b]; wx[id][b]=t;
	 t=wy[id][a]; wy[id][a]=wy[id][b]; wy[id][b]=t;
}

void canonizeworm(int id) {
	int n=wlen[id],i;
	if(wx[id][0]+wy[id][0]*1000>wx[id][n-1]+wy[id][n-1]*1000) {
		for(i=0;i+i<n;i++) swapworm(id,i,n-i-1);
	}
}

void parselevel() {
	char *p;
	int i,id,v;
	if(bptr<1000) printf("seems webpage didn't load properly"),error(buffer);
	if(!(p=strstr2(buffer,"<script>var boardString = \""))) error("vrael! no boardstring!");
	for(y=0;p[y]!=',' && p[y]!=34;y++);
	if(y>MAXY) error("increase MAXY and recompile");
	for(x=0;;) {
		if(x==MAXX) error("increase MAXX and recompile");
		for(i=0;i<y;i++) board[x][i]=p[i]-'0';
		x++;
		if(p[y]!=',') break;
		p+=y+1;
	}
	half=x<16 && y<16;
	if(!(p=strstr2(p,"var wormString = \""))) error("vrael! no wormstring!");
	wn=0;
	while(1) {
		if(p[0]!='t' || p[1]!='e' || p[2]!='a' || p[3]!='m') error("team expected");
		p+=4;
		id=*(p++)-48;
		wcol[wn]=id;
		wlen[wn]=0;
		while(1) {
			if(*p!='_') break;
			p++;
			v=0; while(isdigit(*p)) v=v*10+*(p++)-48;
			wx[wn][wlen[wn]]=v;
			p++;
			v=0; while(isdigit(*p)) v=v*10+*(p++)-48;
			wy[wn][wlen[wn]++]=v;
		}
		wn++;
		if(*p!='@') break;
		p++;
	}
	if(!(p=strstr2(buffer,"var curLevel = "))) error("vrael! no curlevel!");
	level=strtol(p,0,10);
	for(i=0;i<wn;i++) canonizeworm(i);
}

/* set dynamically based on hsize */

typedef unsigned char uchar;

#define TOTHASH 4000000000LL
#define MAGICMUL 177LL
ll MAXHASH;
ll numhash;       /* number of elements in hash table */
int hsize;
int dsize;

uchar *hash;      /* bitfield showing taken elements */
uchar *hashdata;

#define HASHBIT(pos) (hash[(pos)>>3]&(1<<((pos)&7)))
/* 1 if equal, 0 if different */
int HASHCOMPARE(ll ix,uchar *q) {
	int i;
	ll p=ix*(hsize+dsize);
	for(i=0;i<hsize;i++) if(hashdata[p+i]!=q[i]) return 0;
	return 1;
}

ll GETHASH(uchar *p) {
	int i;
	ll h=0;
	for(i=0;i<hsize;i++) h=(h*MAGICMUL+p[i])%MAXHASH;
//	for(i=0;i<hsize;i++) printf("%d ",p[i]); printf("=> %I64d\n",h);
	return h;
}

/* get position of key in hash table regardless of existence */
ll gethashpos(uchar *p) {
	ll pos=GETHASH(p);
	while(1) {
		if(!HASHBIT(pos)) break;
		if(HASHCOMPARE(pos,p)) break;
		pos++; if(pos==MAXHASH) pos=0;
	}
	return pos;
}

/* check if key exists */
int lookuphash(uchar *p) {
	ll pos=gethashpos(p);
	return HASHBIT(pos)?1:0;
}

/* put element in hash table, will overwrite if key exists */
void puthash(uchar *p) {
	ll pos=gethashpos(p);
	int i;
	for(i=0;i<hsize+dsize;i++) hashdata[i+pos*(hsize+dsize)]=p[i];
	hash[pos>>3]|=1<<(pos&7);
	numhash++;
}

/* clear hash table */
void inithashdata() {
	memset(hash,0,(MAXHASH+7)>>3);
}

int isprime(ll z) {
	int i;
	if(z<4) return z>1;
	if(z%2==0) return 0;
	for(i=3;(ll)i*i<=z;i+=2) if(z%i==0) return 0;
	return 1;
}

#define MAXQ 1250000000LL
ll qs,qe,qn;
uchar *q;

int dx[]={1,0,-1,0,-1,1};
int dy[]={0,1,0,-1,0,0};

void fixd(int x1) {
	if(x1&1) dy[4]=dy[5]=1;
	else dy[4]=dy[5]=-1;
}

void ENCODE(uchar *cur) {
	int i,j,cn=0,m,d;
	for(i=0;i<wn;i++) {
		if(half) cur[cn++]=wx[i][0]+(wy[i][0]<<4);
		else cur[cn++]=wx[i][0],cur[cn++]=wy[i][0];
		for(j=m=1;j<wlen[i];j++) {
			if(m==1) cur[cn]=0;
			fixd(wx[i][j-1]);
			for(d=0;d<6;d++) if(wx[i][j-1]+dx[d]==wx[i][j] && wy[i][j-1]+dy[d]==wy[i][j]) break;
			if(d==6) error("error in encode");
			cur[cn]+=d*m;
			m*=6; if(m==216) {
				m=1;
				if(j<wlen[i]-1) cn++;
			}
		}
		cn++;
	}
}

void DECODE(uchar *cur) {
	int i,j,cn=0,m,d;
	for(i=0;i<wn;i++) {
		if(half) wx[i][0]=cur[cn]&15,wy[i][0]=cur[cn++]>>4;
		else wx[i][0]=cur[cn++],wy[i][0]=cur[cn++];
		for(j=m=1;j<wlen[i];j++) {
			fixd(wx[i][j-1]);
			d=cur[cn]/m%6;
			wx[i][j]=wx[i][j-1]+dx[d];
			wy[i][j]=wy[i][j-1]+dy[d];
			m*=6; if(m==216) {
				m=1;
				if(j<wlen[i]-1) cn++;
			}
		}
		cn++;
	}
}

void PULLQ(uchar *cur) {
	int i;
	for(i=0;i<hsize;i++) cur[i]=q[qs++];
	if(qs==qn) qs=0;
}

int INSERTQ(uchar *cur) {
	int i;
	for(i=0;i<hsize;i++) q[qe++]=cur[i];
	if(qe==qn) qe=0,printf("wraparound Q\n");
	if(qe==qs-hsize || (qs==0 && qe==qn-hsize) || numhash>=MAXHASH*0.95) return 0;
	return 1;
}

int won() {
	static char v[MAXX][MAXY];
	int i,j;
	for(i=0;i<x;i++) for(j=0;j<y;j++) v[i][j]=0;
	for(i=0;i<wn;i++) for(j=0;j<wlen[i];j++) v[wx[i][j]][wy[i][j]]=wcol[i]+2;
	for(i=0;i<x;i++) for(j=0;j<y;j++) {
		if(board[i][j]>1 && v[i][j]!=board[i][j]) return 0;
		if(board[i][j]<2 && v[i][j]) return 0;
	}
	return 1;
}

/* move the worm! alter the wx,wy structure */
void moveworm(int x1,int y1,int x2,int y2) {
	int i,l,orm;
	/* find which worm */
	for(orm=0;orm<wn;orm++) {
		if(x1==wx[orm][0] && y1==wy[orm][0]) break;
		if(x1==wx[orm][wlen[orm]-1] && y1==wy[orm][wlen[orm]-1]) break;
	}
	if(orm==wn) error("consistency error in moveworm");
	l=wlen[orm];
	if(x1==wx[orm][0] && y1==wy[orm][0]) {
		/* move head */
		for(i=l-1;i;i--) wx[orm][i]=wx[orm][i-1],wy[orm][i]=wy[orm][i-1];
		wx[orm][0]=x2; wy[orm][0]=y2;
	} else {
		/* move tail */
		for(i=1;i<l;i++) wx[orm][i-1]=wx[orm][i],wy[orm][i-1]=wy[orm][i];
		wx[orm][l-1]=x2; wy[orm][l-1]=y2;
	}
	canonizeworm(orm);
}

ll pushed;

double occup() {
	ll diff=qe-qs;
	if(diff<0) diff+=qn;
	return (double)diff/qn;
}

int try(uchar *cur,int orm,int x1,int y1) {
	static int oldwx[MAXL],oldwy[MAXL];
	static uchar next[MAXL*MAXW*4+4];
	int d,i,x2,y2,l=wlen[orm];
	for(i=0;i<l;i++) oldwx[i]=wx[orm][i],oldwy[i]=wy[orm][i];
	/* try all directions for worm head/tail */
	for(d=0;d<6;d++) {
		fixd(x1&1);
		x2=x1+dx[d]; y2=y1+dy[d];
		if(x2<0 || y2<0 || x2>=x || y2>=y || board[x2][y2]==1) continue;
		if(vis[x2][y2]) {
			if(x2==wx[orm][0] && y2==wy[orm][0]) goto ok;
			if(x2==wx[orm][l-1] && y2==wy[orm][l-1]) goto ok;
			continue;
		}
		if(vis[x2][y2]) continue;
	ok:
		/* we can move! move worm, and push the new state if unvisited */
		moveworm(x1,y1,x2,y2);
		ENCODE(next);
		if(!lookuphash(next)) {
			/* put backwards move in state (before current move) */
			if(x1==oldwx[0] && y1==oldwy[0]) {
				/* head */
				if(half) {
					next[hsize]=oldwx[l-2]+(oldwy[l-2]<<4);
					next[hsize+1]=oldwx[l-1]+(oldwy[l-1]<<4);
				} else {
					next[hsize]=oldwx[l-2];
					next[hsize+1]=oldwy[l-2];
					next[hsize+2]=oldwx[l-1];
					next[hsize+3]=oldwy[l-1];
				}
			} else {
				/* tail */
				if(half) {
					next[hsize]=oldwx[1]+(oldwy[1]<<4);
					next[hsize+1]=oldwx[0]+(oldwy[0]<<4);
				} else {
					next[hsize]=oldwx[1];
					next[hsize+1]=oldwy[1];
					next[hsize+2]=oldwx[0];
					next[hsize+3]=oldwy[0];
				}
			}
			/* insert this move */
			if(half) {
				next[hsize+2]=x1+(y1<<4);
				next[hsize+3]=x2+(y2<<4);
			} else {
				next[hsize+4]=x1;
				next[hsize+5]=y1;
				next[hsize+6]=x2;
				next[hsize+7]=y2;
			}
			puthash(next);
			if(!INSERTQ(next)) {
				for(i=0;i<wlen[orm];i++) wx[orm][i]=oldwx[i],wy[orm][i]=oldwy[i];
				return 2;
			}
			if(won()) {
				for(i=0;i<hsize+dsize;i++) cur[i]=next[i];
				return 1;
			}
			pushed++;
			if(pushed%1000000==0) printf("%I64d pushed, Q occupancy %.2f\n",pushed,occup());
		}
		/* restore worm */
		for(i=0;i<wlen[orm];i++) wx[orm][i]=oldwx[i],wy[orm][i]=oldwy[i];
	}
	return 0;
}

void togglevis() {
	int i,j;
	for(i=0;i<wn;i++) for(j=0;j<wlen[i];j++) vis[wx[i][j]][wy[i][j]]^=1;
}

int pathx1[20000],pathy1[20000];
int pathx2[20000],pathy2[20000];
int pn;

#define MAXR 9800
int rpathx1[MAXR],rpathy1[MAXR];
int rpathx2[MAXR],rpathy2[MAXR];
int rpn;

#define MAXTRY 100

int dorandom() {
	static uchar cur[MAXW*MAXL*4+4];
	static uchar next[MAXW*MAXL*4+4];
	int i,j,l,orm,ix,d,x1,y1,x2,y2,oldwx[MAXL],oldwy[MAXL],tries;
	ll z;
	while(qs!=qe) {
		PULLQ(cur);
		DECODE(cur);
		togglevis();
		for(rpn=j=0;j<MAXR;j++) {
			tries=0;
		again:
			if(tries++==MAXTRY) break;
			orm=rand()%wn;
			l=wlen[orm];
			ix=rand()%2?0:wlen[orm]-1;
			x1=wx[orm][ix];
			y1=wy[orm][ix];
			fixd(x1&1);
			d=rand()%6;
			x2=x1+dx[d];
			y2=y1+dy[d];
			if(x2<0 || y2<0 || x2>=x || y2>=y || board[x2][y2]==1) goto again;
			if(vis[x2][y2]) {
				if(x2==wx[orm][0] && y2==wy[orm][0]) goto ok;
				if(x2==wx[orm][l-1] && y2==wy[orm][l-1]) goto ok;
				goto again;
			}
			if(vis[x2][y2]) goto again;
		ok:
			for(i=0;i<l;i++) oldwx[i]=wx[orm][i],oldwy[i]=wy[orm][i];
			togglevis();
			moveworm(x1,y1,x2,y2);
			ENCODE(next);
			if(lookuphash(next)) {
				for(i=0;i<l;i++) wx[orm][i]=oldwx[i],wy[orm][i]=oldwy[i];
				togglevis();
				goto again;
			}
			togglevis();
			rpathx1[rpn]=x1;
			rpathy1[rpn]=y1;
			rpathx2[rpn]=x2;
			rpathy2[rpn++]=y2;
			if(won()) {
				puts("puzzle won by random moves");
				return 1;
			}
		}
		if((qs/hsize)%10000==0) {
			z=qe-qs; if(z<0) z+=qn;
			printf("%I64d of %I64d\n",z/hsize,qn/hsize);
		}
	}
	return 0;
}

int bfs() {
	static uchar cur[MAXW*MAXL*4+4];
	ll h;
	int orm,r=0,i,x1,y1,x2,y2,t;
	qn=MAXQ/hsize*hsize;
	if(!(q=malloc(qn))) error("out of mem Q");
	printf("hashmap has %I64d elements, queue has %I64d elements\n",MAXHASH,qn/hsize);
	qs=qe=0;
	ENCODE(cur);
	INSERTQ(cur);
	for(i=hsize;i<hsize+dsize;i++) cur[i]=255;
	puthash(cur);
	memset(vis,0,sizeof(vis));
	while(qs!=qe) {
		PULLQ(cur);
		DECODE(cur);
/*		h=gethashpos(cur);
		for(i=hsize;i<hsize+dsize;i++) cur[i]=hashdata[h*(hsize+dsize)+i];
		printf("pop state (hash %I64d):\n",GETHASH(cur));printworms();
		printf("move used to get here: (%d %d)-(%d %d)\n",cur[hsize+2]&15,cur[hsize+2]>>4,cur[hsize+3]&15,cur[hsize+3]>>4);
		printf("back move:             (%d %d)-(%d %d)\n",cur[hsize]&15,cur[hsize]>>4,cur[hsize+1]&15,cur[hsize+1]>>4);*/
		togglevis();
		for(orm=0;orm<wn;orm++) if(wlen[orm]) {
			t=try(cur,orm,wx[orm][0],wy[orm][0]);
			if(t==1) { r=1; goto end; }
			else if(t==2) goto monte;
			if(wlen[orm]>1) {
				t=try(cur,orm,wx[orm][wlen[orm]-1],wy[orm][wlen[orm]-1]);
				if(t==1) { r=1; goto end; }
				else if(t==2) goto monte;
			}
		}
		togglevis();
	}
	goto lose;
monte:
	togglevis();
	/* from each state in queue, move randomly */
	puts("out of memory, trying random moves");
	if(!dorandom()) error("solution not found");
	qs-=hsize;
	if(qs<0) qs+=qn;
	PULLQ(cur);
	h=gethashpos(cur);
	for(i=0;i<hsize+dsize;i++) cur[i]=hashdata[h*(hsize+dsize)+i];
	r=1;
	goto end2;
end:
	/* extract path (backwards) */
	printf("puzzle won after checking %I64d (of %I64d) states\n",qe/hsize,qn/hsize);
end2:
	pn=0;
	while(1) {
		for(i=hsize;i<hsize+dsize;i++) if(cur[i]!=255) goto ok;
		break;
	ok:
		if(half) {
			pathx1[pn]=cur[hsize+2]&15;
			pathy1[pn]=cur[hsize+2]>>4;
			pathx2[pn]=cur[hsize+3]&15;
			pathy2[pn++]=cur[hsize+3]>>4;
			x1=cur[hsize]&15;
			y1=cur[hsize]>>4;
			x2=cur[hsize+1]&15;
			y2=cur[hsize+1]>>4;
		} else {
			pathx1[pn]=cur[hsize+4];
			pathy1[pn]=cur[hsize+5];
			pathx2[pn]=cur[hsize+6];
			pathy2[pn++]=cur[hsize+7];
			x1=cur[hsize]&15;
			y1=cur[hsize]>>4;
			x2=cur[hsize+1]&15;
			y2=cur[hsize+1]>>4;
		}
		DECODE(cur);
		moveworm(x1,y1,x2,y2);
		ENCODE(cur);
		h=gethashpos(cur);
		for(i=0;i<hsize+dsize;i++) cur[i]=hashdata[h*(hsize+dsize)+i];
	}
lose:
	free(q);
	return r;
}

void initbfs() {
	int i;
	hsize=0;
	pushed=0;
	rpn=0;
	for(i=0;i<wn;i++) hsize+=2-half+(1+wlen[i])/3;
	dsize=8/(half+1);
	MAXHASH=TOTHASH/(hsize+dsize);
	numhash=0;
	while(!isprime(MAXHASH)) MAXHASH--;
	if(!(hash=malloc((MAXHASH+7)>>3))) error("out of mem h1");
	if(!(hashdata=malloc(MAXHASH*(hsize+dsize)))) error("out of mem h2");
	inithashdata();
	if(!bfs()) error("not solved");
	free(hashdata);
	free(hash);
}

void solve() {
	printf("solve level %d\n",level);
	printboard();
	printworms();
	initbfs();
}

void submit() {
	static char s[10000000];
	int p,q,i;
	CURL *curl;
	CURLcode res;
	sprintf(s,"name=%s&password=%s&lvl=%d&sol=",name,pw,level);
	q=p=strlen(s);
	/* path consists of multiple commands "mx1.y1-x2.y2" */
	for(i=pn-1;i>=0;i--) {
		sprintf(s+p,"m%d.%d-%d.%d",pathx1[i],pathy1[i],pathx2[i],pathy2[i]);
		p+=strlen(s+p);
	}
	/* append random moves */
	for(i=0;i<rpn;i++) {
		sprintf(s+p,"m%d.%d-%d.%d",rpathx1[i],rpathy1[i],rpathx2[i],rpathy2[i]);
		p+=strlen(s+p);
	}
	printf("\nfound solution, submitting [%s]\n",s+q);
	curl_global_init(CURL_GLOBAL_ALL);
	curl=curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl,CURLOPT_URL,"http://www.hacker.org/tapeworm/index.php");
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
	while(1) {
		readlevel();
		parselevel();
		solve();
		submit();
	}
	return 0;
}
