/* solution for colorful cubes, easy input
   algorithm: totally unoptimized backtracking */

#include <stdio.h>
#include <string.h>

#define MAX 500

char taken[MAX];
int cube[MAX][6];
int n,cols;

int path[MAX];
int col[MAX]; /* col[i]: colour of top face of cube i */
int ix[MAX];

int btr(int at,int c) {
	int i,j;
	if(at==n) return 1;
	for(i=0;i<n;i++) if(!taken[i]) for(j=0;j<6;j++) if(c==cube[i][j^1]) {
		taken[i]=1; path[at]=i; col[at]=cube[i][j]; ix[at]=j;
		if(btr(at+1,col[at])) return 1;
		taken[i]=0;
	}
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
	for(i=0;i<n;i++) for(j=0;j<6;j++) {
		taken[i]=1; path[0]=i; col[0]=cube[i][j]; ix[0]=j;
		if(btr(1,col[0])) goto solved;
		taken[i]=0;
	}
	puts("failed");
	return;
solved:
	for(i=0;i<n;i++) {
		printf("%d",path[i]+1);
		for(j=0;j<6;j++) printf(" %d",cube[path[i]][perms[ix[i]][j]]);
		putchar('\n');
	}
}

int main() {
	int i,j;
	scanf("%d %d",&cols,&n);
	for(i=0;i<n;i++) for(j=0;j<6;j++) scanf("%d",&cube[i][j]);
	solve();
	return 0;
}
