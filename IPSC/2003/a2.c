/* solution to arranging flowers, hard input
   algorithm: bipartite matching */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXV 300

int grid[MAXV][MAXV];    /* [i][j]: i row j column */
char taken[MAXV][MAXV];  /* taken[i][j]: column i number j is taken */
int N,M;

/* maximum matching in bipartite graph!
   n nodes on left side, m nodes on right side
   g[i][j]=1 if edge, 0<=i<n, 0<=j<m
   returns number of edges
   runtime: O(nm)
*/
char g[MAXV][MAXV];         /* [i][j]: edge between i on the left and j on the right */
int n,m;                    /* left, right */
int mate[MAXV];             /* mate for right node (or -1 if unmatched) */
int parent[2*MAXV];

int bipartite() {
	int i,j,r=0,cur,qs,qe=0;
	static int q[2*MAXV];
	memset(mate,-1,m*sizeof(int));
	memset(parent,-1,(n+m)*sizeof(int));
	for(i=0;i<n;i++) {
		qs=0;
		q[qe++]=i;
		while(qs<qe) {
			cur=q[qs++];
			if(cur<n) {
				for(j=n;j<m+n;j++) if(g[cur][j-n] && parent[j]<0) {
					parent[j]=cur;
					q[qe++]=j;
					if(mate[j-n]<0) {
						while(j>-1) {
							mate[j-n]=parent[j];
							j=parent[parent[j]];
						}
						r++;
						goto ok;
					}
				}
			} else {
				q[qe++]=mate[cur-n];
				parent[mate[cur-n]]=cur;
			}
		}
		break;
	ok:
		while(qe) parent[q[--qe]]=-1;
	}
	return r;
}

void solve() {
	int i,j,k;
	scanf("%d %d",&N,&M);
	if(N>MAXV) printf("increase MAXV to %d and recompile\n",N),exit(1);
	for(i=0;i<N;i++) for(j=0;j<N;j++) taken[i][j]=0;
	for(i=0;i<M;i++) {
		for(j=0;j<N;j++) {
			scanf("%d",&grid[i][j]);
			grid[i][j]--;
			taken[j][grid[i][j]]=1;
		}
	}
	n=m=N;
	for(i=M;i<N;i++) {
		/* if number i hasn't been placed on column j, create edge g[j][k] */
		for(j=0;j<n;j++) for(k=0;k<n;k++) g[j][k]=!taken[k][j];
		if(n!=bipartite()) printf("error");
		/* insert numbers */
		for(j=0;j<n;j++) grid[i][j]=mate[j],taken[j][mate[j]]=1;
	}
	printf("%d\n",N-M);
	for(i=M;i<N;i++) {
		for(j=0;j<N;j++) printf("%d ",grid[i][j]+1);
		printf("\n");
	}
	printf("\n");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
