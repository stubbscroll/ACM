/* solution for romeo, both inputs
   algorithm: floyd-warshall to find all pairwise shortest distances, then
   check all nodes if they can be an intermediate node for a shortest path.
   take the minimum of times that are equal for both paths */

#include <stdio.h>

#define MAX 100

int n,ne;
int s1,t1,s2,t2;
int g[MAX][MAX];
int tid[2][MAX];

void check(int ix,int s,int t) {
	int i;
	for(i=0;i<n;i++) tid[ix][i]=-1;
	for(i=0;i<n;i++) if(g[s][i]+g[i][t]==g[s][t]) tid[ix][i]=g[s][i];
}

int main() {
	int i,j,k,a,b,c,r;
	while(scanf("%d",&n),n>-1) {
		scanf("%d",&ne);
		scanf("%d %d %d %d",&s1,&t1,&s2,&t2);
		s1--; t1--; s2--; t2--;
		for(i=0;i<n;i++) for(j=0;j<n;j++) g[i][j]=i==j?0:100000000;
		for(i=0;i<ne;i++) {
			scanf("%d %d %d",&a,&b,&c);
			a--; b--;
			g[a][b]=g[b][a]=c;
		}
		for(k=0;k<n;k++) for(i=0;i<n;i++) for(j=0;j<n;j++) if(g[i][j]>g[i][k]+g[k][j]) g[i][j]=g[i][k]+g[k][j];
		check(0,s1,t1);
		check(1,s2,t2);
		for(r=123123123,i=0;i<n;i++) if(tid[0][i]>-1 && tid[0][i]==tid[1][i] && r>tid[0][i]) r=tid[0][i];
		printf("%d\n",r==123123123?-1:r);
	}
	return 0;
}
