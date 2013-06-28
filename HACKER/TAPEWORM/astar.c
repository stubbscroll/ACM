/* a* with pattern databases!
   - for each worm and possible destination: calculate distance from every
     possible worm position to goal (including every way the worm fits the
     goal)
   - the heuristic: for each worm, look up the distance in the pattern database
     and just sum for each worm. this is admissible!
   - if there are multiple worms of the same colour: try all ways and take the
     minimum
   - use iterative deepening with regular a* (pqueue and hash table)
   - however, a* is not really a good choice for this problem, as we don't
     need an optimal solution, and 10000 moves is a lot of leeway
*/

/* how the astar is built up:
   - proper min-heap with decrease-key, with value from f() (short) and data
     (compressed worm positions, no prev pointers)
   - hashtable with key=compressed worm positions, and value=(backwards move,
     forwards move,index into heap)
   - all elements in the heap are also in the hashtable, and the hashtable keeps
     a pointer to to the heap. elements popped from the heap (closed states)
     have ptr=0 in hashtable
*/

/* for some goal positions there are worms that are impossible to move.
   this is the cause of the different number of states found! for example,
   level 9, worm of length 6: (1 3) (0 3) (1 2) (2 3) (3 2) (3 3)
*/

/* potential problem: the pattern database approach is slow for excessively
   long worms, like level 25 (9267308 states) and 41 (7480709 states)
   some levels have several long worms AND many possible goal patterns
   like level 27 (2401954 states and runs out of memory during creation)
*/

/* weakness: the heuristic function can be extremely slow when there are
   multiple worms of the same colour with lots of freedom to place them
   (the algorithm is exponential in the number of worms of the same colour).
   level 28 is the worst example so far
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

#ifdef OFFLINE

void readlevel() {
	FILE *f=fopen("filen.txt","r");
	if(!f) error("file not found blarg");
	fgets(buffer,BUF,f);
	fclose(f);
	bptr=strlen(buffer);
}

#else

void readlevel() {
  static char s[1000];
  sprintf(s,"http://www.hacker.org/tapeworm/index.php?name=%s&password=%s",name,pw);
  loadwebpage(s);
}

#endif

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

/* new fancy hash table for keys/values composed of multiple uchars */

#define HEAPPTR 4

ll TOTHASH;           /* number of bytes set aside for hash table */
ll MAXHASH;           /* capacity of hash table (number of elements) */
ll MAGICMUL=177LL;    /* magic multiplier */
ll numhash;           /* number of elements currently in hash table */
int hsize;            /* size of key in bytes */
int vsize;            /* size of value in bytes */
int tsize;            /* hsize+vsize */

uchar *hash;          /* bitfield showing taken elements */
uchar *hashdata;      /* main storage area for keys+values */

/* check if pos in hashtable is taken */
#define HASHBIT(pos) (hash[(pos)>>3]&(1<<((pos)&7)))

/* compare entry in hashtable with key pair given in q (value is not compared)
   1 if equal, 0 if different */
int HASHCOMPARE(ll ix,uchar *q) {
	int i;
	ll p=ix*(hsize+vsize);
	for(i=0;i<hsize;i++) if(hashdata[p+i]!=q[i]) return 0;
	return 1;
}

/* return hashvalue of key */
ll GETHASH(uchar *p) {
	int i;
	ll h=0;
	for(i=0;i<hsize;i++) h=(h*MAGICMUL+p[i])%MAXHASH;
	return h;
}

/* get position of key in hash table. if key doesn't exist, it will end
   up at the returned position */
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

/* put key/value in hash table, will overwrite if key exists */
void puthash(uchar *p) {
	ll pos=gethashpos(p);
	int i;
	for(i=0;i<hsize+vsize;i++) hashdata[i+pos*(hsize+vsize)]=p[i];
	hash[pos>>3]|=1<<(pos&7);
	numhash++;
	if(numhash>0.99*MAXHASH) error("out of hash space");
}

/* helper function as we want MAXHASH prime */
int isprime(ll z) {
	int i;
	if(z<4) return z>1;
	if(z%2==0) return 0;
	for(i=3;(ll)i*i<=z;i+=2) if(z%i==0) return 0;
	return 1;
}

/* initialize hash table - hsize and vsize must be set before */
/* remember to free hash and hashdata after use! */
void inithash(ll mem) {
	TOTHASH=mem;
	MAXHASH=(int)(TOTHASH/(hsize+vsize+0.125));
	numhash=0;
	while(!isprime(MAXHASH)) MAXHASH--;
	if(!(hash=malloc((MAXHASH+7)>>3))) error("out of memory in inithash");
	if(!(hashdata=malloc(MAXHASH*(hsize+vsize)))) error("out of memory in inithash");
	memset(hash,0,(MAXHASH+7)>>3);
}

/* generic queue stuff! size of one queue element is hsize */

uchar *q;
ll qs,qe,qn; /* qn: number of bytes in the (circular) queue q */
ll pushed;

void pullq(uchar *cur) {
	int i;
	for(i=0;i<hsize;i++) cur[i]=q[qs++];
	if(qs==qn) qs=0;
}

void insertq(uchar *cur) {
	int i;
	for(i=0;i<hsize;i++) q[qe++]=cur[i];
	if(qe/hsize%5000000==0) printf("    q %I64d, %I64d / %I64d\n",qs/hsize,qe/hsize,qn/hsize);
	if(qe==qn) error("out of memory");
	pushed++;
}

void initq(ll mem) {
	qn=mem/hsize*hsize;
	if(!(q=malloc(qn))) error("out of mem q");
	pushed=qs=qe=0;
}

int dx[]={1,0,-1,0,-1,1};
int dy[]={0,1,0,-1,0,0};

void fixd(int x1) {
	if(x1&1) dy[4]=dy[5]=1;
	else dy[4]=dy[5]=-1;
}

uchar **pattern[MAXW]; /* the pattern database! (elem, h-val)
                          [i][j]: patterns for worm i subset j. here
                          follows pcomb chunks, each of size pstatesize[i] */
int pnsub[MAXW];       /* number of subsets for worm i */
ll *pcomb[MAXW];       /* number of elements in base for worm i, subset j */
ll *psubset[MAXW];     /* mask of work i, subset j */
int pstatesize[MAXW];  /* size of each element for worm i (including distance) */
int ptofree[MAXW];     /* 1: must be freed, 0: must not */
ll patmem;             /* amount of memory used by pattern databases */

void swapwormpart(int *px,int *py,int u,int v) {
	int t=px[u]; px[u]=px[v]; px[v]=t;
	t=py[u]; py[u]=py[v]; py[v]=t;
}

void normalizeworm(int *px,int *py,int l) {
	int i;
	if(px[0]+py[0]*256>px[l-1]+py[l-1]*256) for(i=0;i+i<l;i++)
		swapwormpart(px,py,i,l-i-1);
}

void DECODE1(uchar *cur,int *px,int *py,int l) {
	int p=0,i;
//	printf("decoded:");for(i=0;i<hsize;i++)printf(" %d",cur[i]);printf(" =>");
	if(half) for(i=0;i<l;i++) px[i]=cur[p]&15,py[i]=cur[p++]>>4;
	else for(i=0;i<l;i++) px[i]=cur[p++],py[i]=cur[p++];
//	for(i=0;i<l;i++) printf(" (%d %d)",px[i],py[i]);printf("\n");
}

void ENCODE1(int *px,int *py,int l,uchar *cur) {
	int p=0,i;
//	printf("encoded:");for(i=0;i<l;i++) printf(" (%d %d)",px[i],py[i]);printf(" =>");
	if(half) for(i=0;i<l;i++) cur[p++]=px[i]+(py[i]<<4);
	else for(i=0;i<l;i++) cur[p++]=px[i],cur[p++]=py[i];
//	for(i=0;i<hsize;i++)printf(" %d",cur[i]);printf("\n");
}

char patterndest[MAXX][MAXY];

void createbtr(int at,int len,int *ox,int *oy,int col) {
	int d,x1=ox[at-1],y1=oy[at-1],x2,y2,i;
	static int px[MAXL],py[MAXL];
	static uchar cur[MAXL*3];
	if(at==len) {
		/* push start state */
		for(i=0;i<len;i++) px[i]=ox[i],py[i]=oy[i];
		normalizeworm(px,py,len);
		/* store */
		ENCODE1(px,py,len,cur);
		if(!lookuphash(cur)) {
			cur[hsize]=0;
			puthash(cur);
			insertq(cur);
//			printf("    PUSH");for(i=0;i<len;i++) printf(" (%d %d)",px[i],py[i]);printf("\n");
		}
		return;
	}
	for(d=0;d<6;d++) {
		fixd(x1);
		x2=x1+dx[d]; y2=y1+dy[d];
		for(i=0;i<at;i++) if(x2==ox[i] && y2==oy[i]) goto fail;
		if(x2<0 || y2<0 || x2>=x || y2>=y || col+2!=patterndest[x2][y2]) continue;
		ox[at]=x2; oy[at]=y2;
		createbtr(at+1,len,ox,oy,col);
	fail:;
	}
}

/* fast algorithm for next lexicographic k-subset */
ll snoob(ll x) {
	ll s=x&-x, r=x+s, o=x^r;
	o=(o>>2)/s;
	return r|o;
}

/* slow algorithm for n choose k */
ll nck(int n,int k) {
	static ll p[65][65];
	int i,j;
	for(i=0;i<=n;i++) {
		p[i][0]=p[i][i]=1;
		for(j=1;j<i;j++) p[i][j]=p[i-1][j-1]+p[i-1][j];
	}
	return p[n][k];
}

/* move the work! alter the given ox,oy structure */
void moveworm(int *ox,int *oy,int l,int x1,int y1,int x2,int y2) {
	int i;
	if(x1==ox[0] && y1==oy[0]) {
		/* move head */
		for(i=l-1;i;i--) ox[i]=ox[i-1],oy[i]=oy[i-1];
		ox[0]=x2; oy[0]=y2;
	} else {
		/* move tail */
		for(i=1;i<l;i++) ox[i-1]=ox[i],oy[i-1]=oy[i];
		ox[l-1]=x2; oy[l-1]=y2;
	}
	normalizeworm(ox,oy,l);
}

void printpos(int *ox,int *oy,int l,int mv) {
	int i;
	for(i=0;i<l;i++) printf(" (%d %d)",ox[i],oy[i]);
	printf(": %d\n",mv);
}

/* given a head or tail, try all directions */
void ptry(int *ox,int *oy,int ix,int l,int mv) {
	uchar next[MAXL*2+1];
	int d,x1=ox[ix],y1=oy[ix],x2,y2,i,nx[MAXL],ny[MAXL];
	fixd(x1);
	for(d=0;d<6;d++) {
		x2=x1+dx[d]; y2=y1+dy[d];
		if(x2<0 || y2<0 || x2>=x || y2>=y || board[x2][y2]==1) continue;
		for(i=1;i<l-1;i++) if(x2==ox[i] && y2==oy[i]) goto fail;
		for(i=0;i<l;i++) nx[i]=ox[i],ny[i]=oy[i];
		moveworm(nx,ny,l,x1,y1,x2,y2);
		ENCODE1(nx,ny,l,next);
		/* check if state is visited already */
		if(lookuphash(next)) continue;
		next[hsize]=mv+1;
//		printf(" PUSH");printpos(nx,ny,l,mv+1);
		puthash(next);
		insertq(next);
	fail:;
	}
}

/* visit all states for this particular worm and goal subset */
void pbfs(int orm,int cptr) {
	uchar cur[MAXL*2];
	int ox[MAXL],oy[MAXL],l=wlen[orm],mv;
	ll h;
	while(qs!=qe) {
		pullq(cur);
		DECODE1(cur,ox,oy,l);
		h=gethashpos(cur);
		mv=hashdata[h*(hsize+vsize)+hsize];
//		printf(" POP ");printpos(ox,oy,l,mv);
		ptry(ox,oy,0,l,mv);
		if(l>1) ptry(ox,oy,l-1,l,mv);
	}
}

int floodvis[MAXX][MAXY];
int floodsize[MAXX*MAXY],floodn;
int placesize[MAXW],placen;

int floodfill(int x1,int y1,int col) {
	int r=1,d;
	if(x1<0 || y1<0 || x1>=x || y1>=y || floodvis[x1][y1] || patterndest[x1][y1] || board[x1][y1]!=col+2) return 0;
	floodvis[x1][y1]=1;
	for(d=0;d<6;d++) {
		fixd(x1);
		r+=floodfill(x1+dx[d],y1+dy[d],col);
	}
	return r;
}

int floodbtr(int place) {
	int i;
	if(place==placen) {
		for(i=0;i<floodn;i++) if(floodsize[i]) printf("error tral");
		return 1;
	}
	/* place worm with placesize[place] */
	for(i=0;i<floodn;i++) if(placesize[place]<=floodsize[i]) {
		floodsize[i]-=placesize[place];
		if(floodbtr(place+1)) return 1;
		floodsize[i]+=placesize[place];
	}
	return 0;
}

/* return 0 if puzzle is not solvable with current worm placement */
int floodok(int orm) {
	int i,j;
	/* flood fill to find size of each connected unfilled goal region */
	for(i=0;i<x;i++) for(j=0;j<y;j++) floodvis[i][j]=0;
	for(floodn=i=0;i<x;i++) for(j=0;j<y;j++) if(!patterndest[i][j] && board[i][j]==wcol[orm]+2 && !floodvis[i][j])
		floodsize[floodn++]=floodfill(i,j,wcol[orm]);
	for(i=placen=0;i<wn;i++) if(orm!=i && wcol[i]==wcol[orm]) placesize[placen++]=wlen[i];
	if(floodn>placen) return 0;
	/* find assignment of worms to free goal blobs */
	return floodbtr(0);
}

int comppattern(const void *A,const void *B) {
	const uchar *a=A,*b=B;
	return memcmp(a,b,hsize);
}

/* create pattern databases! for each worm, create a pattern database
   that contains the distance from all worm states to a goal state */
void createpatterndatabase(int orm) {
	int l=wlen[orm],i,j,col=wcol[orm];
	int ox[MAXL],oy[MAXL],cx[MAXX*MAXY],cy[MAXX*MAXY],cn,cptr=0;
	ll mask,endmask,combn,h,prev;
	pstatesize[orm]=l*(2-half)+1;
	/* check if same kind of worm has occurred earlier */
	for(i=0;i<orm;i++) if(wcol[i]==wcol[orm] && wlen[i]==wlen[orm]) {
		pattern[orm]=pattern[i];
		pcomb[orm]=pcomb[i];
		psubset[orm]=psubset[i];
		pnsub[orm]=pnsub[i];
		ptofree[orm]=0;
		return;
	}
	hsize=l*(2-half);
	vsize=1;             /* for distance, assume < 256 */
	printf("create pattern database for worm %d col %d size %d\n",orm,col+2,l);
	/* loop over each bitmask */
	for(cn=i=0;i<x;i++) for(j=0;j<y;j++) if(board[i][j]==col+2) cx[cn]=i,cy[cn++]=j;
	if(cn>62) error("too many bits for one colour");
	endmask=1LL<<cn;
	mask=(1LL<<l)-1;
	/* allocate memory for all subsets */
	combn=nck(cn,l);
	printf("goal cells %d, worm length %d, %I64d subsets, mask %I64d endmask %I64d\n",cn,l,combn,mask,endmask);
	combn=1000;
	/* TODO the memory allocation here is a bit excessive */
	if(!(pattern[orm]=malloc(combn*sizeof(void *)))) error("out of memory allocating pattern database stuff");
	if(!(pcomb[orm]=malloc(combn*sizeof(ll)))) error("out of memory allocating pattern database stuff");
	if(!(psubset[orm]=malloc(combn*sizeof(ll)))) error("out of memory allocating pattern database stuff");
	patmem+=combn*(sizeof(void *)+2*sizeof(ll));
	do {
		/* create goal state corresponding to bitmask */
		memset(patterndest,0,sizeof(patterndest));
//		printf("  check mask ");for(i=0;i<cn;i++) printf("%d",(mask&(1LL<<i))?1:0);printf("\n");
		for(i=0;i<cn;i++) if(mask&(1LL<<i)) patterndest[cx[i]][cy[i]]=col+2;
		if(cn>l && !floodok(orm)) goto next;
		/* find all starting positions */
		inithash(1100000000LL);
		initq(1000000000LL);
		for(i=0;i<x;i++) for(j=0;j<y;j++) if(col+2==patterndest[i][j]) {
			ox[0]=i; oy[0]=j;
			prev=qe;
			if(wlen[orm]>=12) printf("  search from (%d %d):",i,j);
			createbtr(1,l,ox,oy,col);
			if(wlen[orm]>=12) printf("  found %I64d\n",(qe-prev)/hsize);
		}
		if(qe) {
			/* do actual bfs here! */
//			printf("mask %I64d: found %I64d goal states\n",mask,pushed);
			psubset[orm][cptr]=mask;
			pbfs(orm,cptr);
			/* bfs is done! copy visited states to pattern database storage */
			/* but first, check if we exceeded array */
			if(combn==cptr) {
				combn*=2;
				if(!(pattern[orm]=realloc(pattern[orm],combn*sizeof(void *)))) error("out of memory reallocating pattern database stuff");
				if(!(pcomb[orm]=realloc(pcomb[orm],combn*sizeof(ll)))) error("out of memory reallocating pattern database stuff");
				if(!(psubset[orm]=realloc(psubset[orm],combn*sizeof(ll)))) error("out of memory reallocating pattern database stuff");
			}
			if(!(pattern[orm][cptr]=malloc(pushed*(hsize+vsize)))) error("out of memory pattern database");
			patmem+=pushed*(hsize+vsize);
			for(i=0;i<pushed;i++) {
				h=gethashpos(q+i*hsize);
				memcpy(pattern[orm][cptr]+i*(hsize+vsize),hashdata+h*(hsize+vsize),hsize+vsize);
			}
			qsort(pattern[orm][cptr],pushed,hsize+vsize,comppattern);
			printf("mask ");for(i=cn-1;i>=0;i--) printf("%d",(mask&(1LL<<i))?1:0);printf(" found %I64d states in total\n",pushed);
//			for(i=0;i<pushed;i++) {DECODE1(pattern[orm][cptr]+i*(hsize+vsize),ox,oy,l);printf("  ");for(j=0;j<l;j++) printf(" (%d %d)",ox[j],oy[j]);printf(": %d\n",pattern[orm][cptr][i*(hsize+vsize)+hsize]);}
			pcomb[orm][cptr++]=pushed;
		}
		free(q);
		free(hash);
		free(hashdata);
	next:
		mask=snoob(mask);
	} while(mask<endmask);
	/* realloc again */
	if(combn!=cptr) {
		if(!(pattern[orm]=realloc(pattern[orm],combn*sizeof(void *)))) error("out of memory reallocating pattern database stuff");
		if(!(pcomb[orm]=realloc(pcomb[orm],combn*sizeof(ll)))) error("out of memory reallocating pattern database stuff");
		if(!(psubset[orm]=realloc(psubset[orm],combn*sizeof(ll)))) error("out of memory reallocating pattern database stuff");
	}
	pnsub[orm]=cptr;
	ptofree[orm]=1;
	printf("worm %d has %d legal subsets\n",orm,cptr);
}

void freepatterndatabase(int orm) {
	int i;
	if(!ptofree[orm]) return;
	for(i=0;i<pnsub[orm];i++) free(pattern[orm][i]);
	free(pattern[orm]);
	free(pcomb[orm]);
	free(psubset[orm]);
}

/* look up wx[orm],wy[orm] in pattern database for goal pattern ix */
int hsearch(int orm,int ix) {
	uchar cur[MAXL*2];
	ll lo=0,hi=pcomb[orm][ix],mid;
	ENCODE1(wx[orm],wy[orm],wlen[orm],cur);
	while(lo<hi) {
		mid=(lo+hi)>>1;
		if(memcmp(pattern[orm][ix]+mid*pstatesize[orm],cur,pstatesize[orm]-1)>=0) hi=mid;
		else lo=mid+1;
	}
	return pattern[orm][ix][(lo+1)*pstatesize[orm]-1];
}

int hbtr(int col,int at,ll mask) {
	int i,r=1000000,cur;
	while(at<wn && wcol[at]!=col) at++;
	if(at==wn) return 0;
	for(i=0;i<pnsub[at];i++) if(!(mask&psubset[at][i])) {
		cur=hbtr(col,at+1,mask|psubset[at][i])+hsearch(at,i);
		if(r>cur) r=cur;
	}
	return r;
}

/* given current position in wx,wy, calculate heuristic */
int h() {
	int r=0,col,z;
	/* for each colour, find the lowest distance sum */
	for(col=0;col<8;col++) {
		z=hbtr(col,0,0);
//		printf("contribution from col %d: h=%d\n",col,z);
		r+=z;
	}
	return r;
}

ll MAXH;

short *heap;     /* value we sort on (f-value) */
uchar *heapid;   /* the key */
ll heapn;        /* number of elements in heap + 1 */

void setheapptr(uchar *cur,ll ptr) {
//	printf("set ptr to %I64d\n",ptr);
	cur[hsize+4*(2-half)  ]=(ptr>>24)&255;
	cur[hsize+4*(2-half)+1]=(ptr>>16)&255;
	cur[hsize+4*(2-half)+2]=(ptr>>8)&255;
	cur[hsize+4*(2-half)+3]=ptr&255;
}

/* slow and super-safe solution, assumes that element from is already
   in hashtable! */
void moveheapelement(ll to,ll from) {
	uchar *cur=hashdata+gethashpos(heapid+from*hsize)*tsize;
	setheapptr(cur,to);
	memcpy(heapid+to*hsize,cur,hsize);
}

/* assume that id has value for hashtable as well!
   don't assume that id is in hash table, this routine is responsible for
   creating the entry in the hash table! */
void heapinsert(short val,uchar *id) {
	int pos=heapn++;
	if(heapn==MAXH) error("heap full");
	while(pos>1 && val<heap[pos>>1]) {
		heap[pos]=heap[pos>>1];
		/* element moves from pos>>1 to pos */
		moveheapelement(pos,pos>>1);
		pos>>=1;
	}
	heap[pos]=val;
	setheapptr(id,pos);
	puthash(id);
	memcpy(heapid+pos*hsize,id,hsize);
}

/* decrease value at pos with key *id */
void heapdecreasekey(short newkey,ll pos,uchar *id) {
	if(newkey>=heap[pos]) error("key was not decreased");
	while(pos>1 && heap[pos>>1]>newkey) {
		heap[pos]=heap[pos>>1];
		moveheapelement(pos,pos>>1);
		pos>>=1;
	}
	heap[pos]=newkey;
	setheapptr(id,pos);
	memcpy(heapid+pos*hsize,id,hsize);
}

/* remove a value from the heap and put it in *val,*id */
/* don't call if heap is empty! */
void heapremove(short *val,uchar *id) {
	int pos=1,next=1;
	short newval;
	static uchar newid[MAXL*MAXW*2+12],*cur;
	if(heapn<2) error("heap is empty");
	*val=heap[1];
	memcpy(id,heapid+hsize,hsize);
	cur=gethashpos(id)*tsize+hashdata;
	setheapptr(cur,0);
	newval=heap[--heapn];
	memcpy(newid,heapid+heapn*hsize,hsize);
	while((pos<<1)<=heapn) {
		/* take lowest of left and right children */
		if((pos<<1)==heapn) next=pos<<1;
		/* change to <heap[...] for maxheap */
		else next=(pos<<1)+(heap[pos<<1]>heap[(pos<<1)+1]);
		/* change to <=newval for maxheap */
		if(heap[next]>=newval) break;
		heap[pos]=heap[next];
		moveheapelement(pos,next);
		pos=next;
	}
	heap[pos]=newval;
	cur=gethashpos(newid)*tsize+hashdata;
	setheapptr(cur,pos);
	memcpy(heapid+pos*hsize,newid,hsize);
}

void initheap(ll mem) {
	MAXH=mem/(sizeof(short)+hsize+vsize);
	if(MAXH>=(1LL<<32)) puts("error, increase heapptr");
	if(!(heap=malloc(MAXH*sizeof(short)))) error("out of memory in heap");
	if(!(heapid=malloc(MAXH*hsize))) error("out of memory in heap");
	heapn=1;
}

void freeheap() {
	free(heapid);
	free(heap);
}

/* given compressed state, find pointer into heap */
ll gethashptr(uchar *cur) {
	return (cur[hsize+4*(2-half)]<<24)+(cur[hsize+4*(2-half)+1]<<16)+
	       (cur[hsize+4*(2-half)+2]<<8)+cur[hsize+4*(2-half)+3];
}

void printheap() {
	uchar *cur;
	int i,j;
	for(i=1;i<heapn;i++) {
		printf("element %d: val %d data:\n  ",i,heap[i]);
		cur=gethashpos(heapid+i*hsize)*tsize+hashdata;
		for(j=0;j<hsize;j++) printf("(%d %d) ",heapid[i*hsize+j]&15,heapid[i*hsize+j]>>4);
		for(j=0;j<4;j++) printf("[%d %d] ",cur[j+hsize]&15,cur[j+hsize]>>4);
		printf("%I64d\n",gethashptr(cur));
	}
	puts("---------");
}

int astarmaxiter;

void ENCODE(uchar *cur) {
	int i,j,cn=0;
	if(half) for(i=0;i<wn;i++) for(j=0;j<wlen[i];j++) cur[cn++]=wx[i][j]+(wy[i][j]<<4);
	else for(i=0;i<wn;i++) for(j=0;j<wlen[i];j++) cur[cn++]=wx[i][j],cur[cn++]=wy[i][j];
}

void DECODE(uchar *cur) {
	int i,j,cn=0;
	if(half) for(i=0;i<wn;i++) for(j=0;j<wlen[i];j++) wx[i][j]=cur[cn]&15,wy[i][j]=cur[cn++]>>4;
	else for(i=0;i<wn;i++) for(j=0;j<wlen[i];j++) wx[i][j]=cur[cn++],wy[i][j]=cur[cn++];
}

#define MAXMEM 5000000000LL

void togglevis() {
	int i,j;
	for(i=0;i<wn;i++) for(j=0;j<wlen[i];j++) vis[wx[i][j]][wy[i][j]]^=1;
}

void updatebackfrom(uchar *next,int l,int *oldwx,int *oldwy,int x1,int y1,int x2,int y2) {
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
}

/* try all moves from x1,y1 using orm */
int try(uchar *cur,int orm,int x1,int y1,short g) {
	static int oldwx[MAXL],oldwy[MAXL];
	static uchar next[MAXL*MAXW*4+4];
	short hval;
	int d,i,x2,y2,l=wlen[orm];
	ll ptr;
	for(i=0;i<l;i++) oldwx[i]=wx[orm][i],oldwy[i]=wy[orm][i];
	/* try all directions for worm head/tail */
	fixd(x1);
	for(d=0;d<6;d++) {
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
		moveworm(wx[orm],wy[orm],l,x1,y1,x2,y2);
		if(g+h()>astarmaxiter) goto restore;
		ENCODE(next);
		if(!lookuphash(next)) {
			printf("move from %d %d to %d %d: new position!\n",x1,y1,x2,y2);
			/* create new entry */
			hval=h();
			updatebackfrom(next,l,oldwx,oldwy,x1,y1,x2,y2);
			if(!hval) {
				for(i=0;i<tsize;i++) cur[i]=next[i];
				return 1;
			}
			heapinsert(g+hval,next);
//			printheap();
		} else {
			/* check if node is closed! if this is the case, ignore */
			ptr=gethashptr(hashdata+tsize*gethashpos(next));
			if(!ptr) goto restore;
			/* don't do anything either if f-value isn't lower */
			hval=h();
			if(heap[ptr]<=g+hval) goto restore;
			/* decrease-key! update back and forward moves */
			printf("move from %d %d to %d %d: lower f!\n",x1,y1,x2,y2);
//			{ll pos=gethashpos(next);pos=gethashptr(hashdata+pos*tsize);printf("  pos %I64d\n",pos);}
			updatebackfrom(next,l,oldwx,oldwy,x1,y1,x2,y2);
			heapdecreasekey(g+hval,ptr,next);
//			printheap();
		}
	restore:
		/* restore worm */
		for(i=0;i<wlen[orm];i++) wx[orm][i]=oldwx[i],wy[orm][i]=oldwy[i];
	}
	return 0;
}

int pathx1[20000],pathy1[20000];
int pathx2[20000],pathy2[20000];
int pn;

void movewormlaunch(int x1,int y1,int x2,int y2) {
	int l,orm;
	/* find which worm */
	for(orm=0;orm<wn;orm++) {
		if(x1==wx[orm][0] && y1==wy[orm][0]) break;
		if(x1==wx[orm][wlen[orm]-1] && y1==wy[orm][wlen[orm]-1]) break;
	}
	if(orm==wn) error("consistency error in moveworm");
	l=wlen[orm];
	moveworm(wx[orm],wy[orm],l,x1,y1,x2,y2);
}

int astarsearch() {
	static uchar cur[MAXL*MAXW*2+2];
	short f,g;
	ll popped=0,pos;
	int orm,x1,y1,x2,y2,i;
	memset(vis,0,sizeof(vis));
//	printheap();
	while(heapn>1) {
		heapremove(&f,cur);
		popped++;
		if(popped%1000000==0) printf("%I64d / %I64d\n",popped,heapn);
		DECODE(cur);
		g=f-h()+1;
		printf("popped position with g=%d h=%d:\n",g,h());printworms();
		togglevis();
		/* do all moves */
		for(orm=0;orm<wn;orm++) {
			if(try(cur,orm,wx[orm][0],wy[orm][0],g)) goto found;
			if(wlen[orm]>1 && try(cur,orm,wx[orm][wlen[orm]-1],wy[orm][wlen[orm]-1],g)) goto found;
		}
		togglevis();
	}
	printf("  visited %I64d states, no solution found\n",popped);
	return 0;
found:
	/* last state is in cur: nest back */
	pn=0;
	printf("  solution found after visiting %I64d states\n",popped+heapn-1);
	while(1) {
		if(cur[hsize]==255 && cur[hsize+1]==255 && cur[hsize+2]==255 && cur[hsize+3]==255) break;
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
		movewormlaunch(x1,y1,x2,y2);
		ENCODE(cur);
		pos=gethashpos(cur);
		for(i=0;i<tsize;i++) cur[i]=hashdata[pos*tsize+i];
	}
	return 1;
}

/* a*! depth is limited to astarmaxiter. store reverse move in hash table,
   and store both f and g values in pqueue */
int astar() {
	int i,r;
	static uchar cur[MAXL*MAXW*2+12];
	for(hsize=i=0;i<wn;i++) hsize+=wlen[i]*(2-half);
	/* vsize: store back move, forward move and ptr */
	vsize=4*(2-half)+HEAPPTR;
	tsize=hsize+vsize;
	initheap((MAXMEM-patmem)*2/5);
	inithash((MAXMEM-patmem)*3/5);
	printf("search with depth %d\n",astarmaxiter);
	ENCODE(cur);
	for(i=hsize;i<tsize;i++) cur[i]=255;
	heapinsert(h(),cur);
	r=astarsearch();
	DECODE(cur);
	free(hashdata);
	free(hash);
	freeheap();
	return r;
}

void solve() {
	int orm;
	printf("solve level %d\n",level);
	printboard();
	printworms();
	patmem=0;
	for(orm=0;orm<wn;orm++) createpatterndatabase(orm);
	for(astarmaxiter=h();!astar();astarmaxiter++);
	for(orm=0;orm<wn;orm++) freepatterndatabase(orm);
}

void submit() {
	static char s[10000000];
	int p,q,i;
	CURL *curl;
	CURLcode res;
	sprintf(s,"name=%s&password=%s&lvl=%d&sol=",name,pw,level);
	q=p=strlen(s);
	/* path consists of multiple commands "mx1.y1-x2.y2" */
//	for(i=pn-1;i>=0;i--) printf("move (%d %d) - (%d %d)\n",pathx1[i],pathy1[i],pathx2[i],pathy2[i]);
	for(i=pn-1;i>=0;i--) {
		sprintf(s+p,"m%d.%d-%d.%d",pathx1[i],pathy1[i],pathx2[i],pathy2[i]);
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
		break;
		submit();
	}
	return 0;
}
