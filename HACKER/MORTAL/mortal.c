#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <curl/easy.h>

#define MAX 100
#define MAXP 1000000
#define BUF 1000000
#define Q 2000000

char *name,*pw;
int restartx=0,restarty=0,startx,starty;
char buffer[BUF];
int bptr;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
char dir[]="RDLU";

/*  level variables, not changed during solving */
int level;
int x,y;
char g[MAX][MAX];
char sol[MAXP];

/*  changed during solving */
char h[MAX][MAX];
char path[MAXP];
int pathlen;
int qs,qe,q[Q];
char t[MAX][MAX];

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

void readlevel() {
	static char s[1000];
	sprintf(s,"http://www.hacker.org/coil/index.php?name=%s&password=%s",name,pw);
	loadwebpage(s);
}

void submit() {
	static char s[1100000];
	sprintf(s,"http://www.hacker.org/coil/index.php?name=%s&password=%s&path=%s&x=%d&y=%d",name,pw,sol,startx,starty);
	loadwebpage(s);
	if(bptr<1000) {
		puts("it seems the solution wasn't submitted successfully.");
		error(buffer);
	}
}

size_t ignore(void *ptr,size_t size,size_t n,void *userdata) {
	return n;
}

void submitPOST() {
	static char s[1100000];
	sprintf(s,"name=%s&password=%s&path=%s&x=%d&y=%d",name,pw,sol,startx,starty);
	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl=curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl,CURLOPT_URL,"http://www.hacker.org/coil/index.php");
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,s);
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,ignore);
		res=curl_easy_perform(curl);
		if(CURLE_OK!=res) printf("failed post %s\n",curl_easy_strerror(res)),exit(1);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

void parselevel() {
	char *p;
	int i,j;
	if(bptr<1000) {
		puts("it seems the page didn't load successfully.");
		error(buffer);
	}
	if(!(p=strstr(buffer,"Level:"))) error("couldn't find level number.\n");
	level=strtol(p+6,0,10);
	if(!(p=strstr(buffer,"=\"x="))) error("couldn't find x-coordinate.\n");
	x=strtol(p+4,0,10);
	if(!(p=strstr(buffer,"&y="))) error("couldn't find y-coordinate.\n");
	y=strtol(p+3,0,10);
	if(!(p=strstr(buffer,"&board="))) error("couldn't find board.\n");
	p+=7;
	for(j=0;j<y;j++) for(i=0;i<x;i++) g[i][j]=p[i+j*x];
}

void printlevel(char g[MAX][MAX]) {
	int i,j;
	printf("size %dx%d\n",x,y);
	for(j=0;j<y;j++) {
		for(i=0;i<x;i++) putchar(g[i][j]);
		putchar('\n');
	}
	putchar('\n');
}

/* 1: solved, 0: not solved, -1: unsolvable state */
int solvestatus(int u,int v,int pathptr) {
	/* check degree 1 */
	int deg=0,degat=0,i,j,count,at,d,x2,y2,found=0,cx,cy;
	for(j=0;j<y;j++) for(i=0;i<x;i++) if(h[i][j]=='.') {
		count=at=0;
		for(d=0;d<4;d++) {
			x2=i+dx[d],y2=j+dy[d];
			if(x2>-1 && x2<x && y2>-1 && y2<y) {
				if(h[x2][y2]=='.') count++;
				if(x2==u && y2==v) at=1;
			}
		}
		if(count==1) {
			if(!at) deg++; else degat++;
		}
		if(deg>1 && deg+degat>2) return -1;
	}
	/* check disjoint */
	for(i=0;i<x;i++) memset(t[i],0,y);
	for(qs=qe=j=0;j<y;j++) for(i=0;i<x;i++) if(h[i][j]=='.') {
		found=1;
		q[qe++]=u; q[qe++]=v;
		while(qs<qe) {
			cx=q[qs++],cy=q[qs++];
			for(d=0;d<4;d++) {
				x2=cx+dx[d],y2=cy+dy[d];
				if(x2<0 || x2>=x || y2<0 || y2>=y || h[x2][y2]!='.' || t[x2][y2]) continue;
				t[x2][y2]=1;
				q[qe++]=x2,q[qe++]=y2;
			}
		}
		goto done;
	}
done:
	if(!found) {
		/* solved */
		path[pathlen=pathptr]=0;
		strcpy(sol,path);
		return 1;
	}
	for(j=0;j<y;j++) for(i=0;i<x;i++) if(h[i][j]=='.' && !t[i][j]) return -1;
	return 0;
}

int move(int,int,int,int);

int solve(int u,int v,int pathptr) {
	int res=solvestatus(u,v,pathptr),d,x2,y2;
	if(res) return res>0;
	for(d=0;d<4;d++) {
		x2=u+dx[d],y2=v+dy[d];
		if(x2<0 || y2<0 || x2>=x || y2>=y || h[x2][y2]!='.') continue;
		path[pathptr]=dir[d];
		if(move(x2,y2,d,pathptr+1)) return 1;
	}
	return 0;
}

int move(int uu,int vv,int d,int pathptr) {
	int u=uu,v=vv,x2,y2;
	while(1) {
		h[u][v]='*';
		x2=u+dx[d]; y2=v+dy[d];
		if(x2<0 || y2<0 || x2>=x || y2>=y || h[x2][y2]!='.') break;
		u=x2; v=y2;
	}
	if(solve(u,v,pathptr)) return 1;
	while(u!=uu || v!=vv) {
		h[u][v]='.';
		u-=dx[d]; v-=dy[d];
		if(u<0 || u>=x || v<0 || v>=y) break;
	}
	if(u>-1 && u<x && v>-1 && v<y) h[u][v]='.';
	return 0;
}

void runsolver() {
	int i=restartx,j=restarty,d,x2,y2;
	restartx=restarty=0;
	memcpy(h,g,sizeof(g));
	while(i<x) {
		if(h[i][j]=='.') for(d=0;d<4;d++) {
			x2=i+dx[d]; y2=j+dy[d];
			if(x2<0 || y2<0 || x2>=x || y2>=y || h[x2][y2]!='.') continue;
			printf("[%d %d %d] ",i,j,d);
			path[0]=dir[d];
			if(move(i,j,d,1)) {
				startx=i; starty=j;
				return;
			}
		}
		j++;
		if(j==y) j=0,i++;
//		if(i==60 && j==5) exit(0);
	}
}

void go() {
	while(1) {
		readlevel();
		parselevel();
		printf("attempt to solve level %d\n",level);
		printlevel(g);
		runsolver();
		printf("\nlevel solved, submitting %d %d %s\n",startx,starty,sol);
		submitPOST();
	}
}

int main(int argc,char**argv) {
	if(argc<3) {
		puts("mortal coil solver v1.0, usage: mortal user pw [x y]");
		return 0;
	}
	name=argv[1];
	pw=argv[2];
	if(argc>4) restartx=strtol(argv[3],0,10),restarty=strtol(argv[4],0,10);
	go();
	return 0;
}
