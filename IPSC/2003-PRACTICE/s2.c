/* solution for colorful cubes, hard input
   observation 1: 100 colours and 499 cubes means that there are a lot of
                  solutions
   observation 2: many cubes have chessboard pattern, don't search equivalent
                  patterns
   algorithm: for most of the part, greedily pick nodes that maximizes the
   sum of node "degrees", where multiple edges between two nodes increase the
   degree. at the end, run normal backtracking. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 500
#define MAXC 101
#define MAXOC 3000

char taken[MAX];
int cube[MAX][6];
int n,cols;

int path[MAX];
int col[MAX]; /* col[i]: colour of top face of cube i */
int ix[MAX];

int colno[MAXC][MAXOC];
int colix[MAXC][MAXOC];
int coln[MAXC];
char g[MAX][MAX];

int connected(int at) {
	char vis[MAX];
	int q[MAX],qs=0,qe=0,cur,next;
	int i;
	memcpy(vis,taken,n);
	for(i=0;i<n;i++) if(!taken[i]) { q[qe++]=i; vis[i]=1; break; }
	while(qs<qe) {
		cur=q[qs++];
		for(next=0;next<n;next++) if(!vis[next] && g[cur][next]) {
			q[qe++]=next;
			vis[next]=1;
		}
	}
	return qe==n-at;
}

int btr(int at,int c) {
	int i,j,k,K;
	if(at==n) return 1;
	if(at<n-20 && at%2==0 && !connected(at)) return 0;
	for(k=0;k<coln[c];k++) {
		K=k*6271%coln[c];
		i=colno[c][K];
		if(taken[i]) continue;
		j=colix[c][K]^1;
		taken[i]=1; path[at]=i; col[at]=cube[i][j]; ix[at]=j;
		if(btr(at+1,col[at])) return 1;
		taken[i]=0;
	}
	return 0;
}

int sumdeg() {
	int i,j,r=0;
	for(i=0;i<n;i++) if(!taken[i]) for(j=i+1;j<n;j++) if(!taken[j]) r+=g[i][j];
	return r;
}

int greed(int at,int c) {
	int i,j,k,besti=-1,bestj=-1,cur,max=-1;
	if(at>=n-95) {
		fprintf(stderr,"got to %d\n",at);
		return btr(at,c);
	}
	for(k=0;k<coln[c];k++) {
		i=colno[c][k];
		if(taken[i]) continue;
		j=colix[c][k]^1;
		taken[i]=1;
		if(!connected(at+1)) goto fail;
		cur=sumdeg();
		if(max<cur) max=cur,besti=i,bestj=j;
	fail:
		taken[i]=0;
	}
	if(besti<0) { fprintf(stderr,"no found at %d\n",at); return 0; }
	i=besti; j=bestj;
	taken[i]=1; path[at]=i; col[at]=cube[i][j]; ix[at]=j;
	if(greed(at+1,col[at])) return 1;
	taken[i]=0;
	return 0;
}

int perms[6][6]={
	{4,5,2,3,1,0},  /* front up */
	{5,4,2,3,0,1},  /* back up */
	{0,1,4,5,3,2},  /* right up */
	{0,1,5,4,2,3},  /* left up */
	{0,1,3,2,5,4},  /* bottom up */
	{0,1,2,3,4,5}}; /* top */

void solve() {
	int i,j;
	memset(taken,0,n);
	for(i=0;i<n;i++) {
		for(j=0;j<6;j++) {
			if(j==2 && cube[i][0]==cube[i][2] && cube[i][0]==cube[i][4] && cube[i][1]==cube[i][3] && cube[i][1]==cube[i][5]) break;
			fprintf(stderr,"try %d %d\n",i,j);
			taken[i]=1; path[0]=i; col[0]=cube[i][j]; ix[0]=j;
			if(greed(1,col[0])) goto solved;
			taken[i]=0;
		}
	}
	fprintf(stderr,"failed\n");
	return;
solved:
	for(i=0;i<n;i++) {
		printf("%d",path[i]+1);
		for(j=0;j<6;j++) printf(" %d",cube[path[i]][perms[ix[i]][j]]);
		putchar('\n');
	}
}

void preprocess() {
	int i,j,c,k,l;
	for(i=0;i<=cols;i++) coln[i]=0;
	for(i=0;i<n;i++) for(j=0;j<6;j++) {
		if(j==2 && cube[i][0]==cube[i][2] && cube[i][0]==cube[i][4] && cube[i][1]==cube[i][3] && cube[i][1]==cube[i][5]) break;
		c=cube[i][j];
		colno[c][coln[c]]=i;
		colix[c][coln[c]++]=j;
	}
	for(i=0;i<n;i++) for(j=0;j<n;j++) g[i][j]=0;
	for(i=0;i<n;i++) for(j=0;j<n;j++) if(i!=j) {
		for(k=0;k<6;k++) for(l=0;l<6;l++) if(cube[i][k]==cube[j][l]) g[i][j]++;
	}
}

int main() {
	int i,j;
	scanf("%d %d",&cols,&n);
	for(i=0;i<n;i++) for(j=0;j<6;j++) scanf("%d",&cube[i][j]);
	preprocess();
	solve();
	return 0;
}
