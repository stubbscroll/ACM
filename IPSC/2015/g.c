/* solution for generating synergy, both inputs
   algorithm: use dfs with depth limitation for colouring nodes, and just
   read off node colour for each query. this actually works for the hard input,
   but it takes around 2800 seconds on an i7-2600k.
   needs to be compiled with increased stack size for hard input.
*/

#include <stdio.h>
#include <string.h>

#define MAXV 1000001
#define MAXE 1000002
int n,ne;               /* number of nodes, number of edges */
int from[MAXE],to[MAXE];/* edge i: from[i] to[i] */
int gs[MAXV+1];         /* gs[i]: start of edges from i, gs[i+1]: end */

char vis[MAXV];         /* during dfs: 0:unvisited 1:under progress 2:done */

void countingsort() {
	static int newto[MAXE];
	int i,j;
	for(i=0;i<=n;i++) gs[i]=0;
	for(i=0;i<ne;i++) gs[from[i]]++;
	for(i=1;i<n;i++) gs[i]+=gs[i-1];
	gs[n]=ne;
	for(i=0;i<ne;i++) {
		j=--gs[from[i]];
		newto[j]=to[i];
	}
	for(i=0;i<ne;i++) to[i]=newto[i];
	for(i=0;i<n;i++) for(j=gs[i];j<gs[i+1];j++) from[j]=i;
}

int c,q;
int col[MAXV];

void dfs(int at,int left,int nc) {
	int i;
	col[at]=nc;
	if(left) for(i=gs[at];i<gs[at+1];i++) dfs(to[i],left-1,nc);
}

void solve() {
	int i,it,a,l,nc;
	int r=0;
	fprintf(stderr,"new case\n");fflush(stderr);
	scanf("%d %d %d",&n,&c,&q);
	for(i=0;i<n;i++) col[i]=1;
	ne=0;
	for(i=0;i<n-1;i++) {
		scanf("%d",&from[ne]); from[ne]--;
		to[ne++]=i+1;
	}
	countingsort();
	for(it=1;it<=q;it++) {
		scanf("%d %d %d",&a,&l,&nc);
		if(nc==0) r=(r+(long long)it*col[a-1])%1000000007;
		else dfs(a-1,l,nc);
		if(it%10000==0) fprintf(stderr,"  q %d/%d\n",it,q),fflush(stderr);
	}
	printf("%d\n",r);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
