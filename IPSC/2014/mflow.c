/* solution for maximum enjoyment, easy input
   algorithm: maxflow on transformed graph where all non-source and sink nodes
   are splitted. for an arbitrary node u, let's denode the splitted nodes as
   u1 and u2. the new graph has edges from source to sink, from source to
   u1 for all eligible u, from u1 to v2 for all eligible u,v, and from u2 to
   sink for all eligible u. in addition, edges with infinite cap are added from
   u1 to u2 for each u. since flow can only go from source to sink, or from
   source to u' to v' to sink, a path can never have length longer than 3. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

int c[MAX][MAX];  /* capacities */
int N,s,t,L;      /* number of nodes, source, sink, max number of links */

#define MAXV 200
#define INF 1000000000

/* maxflow! uses adjacency matrix */

int f[MAXV][MAXV]; /* capacity, 0 means no edge */
int n;

int maxflow(int source,int sink) {
	int i,j,done,flow=0,done2,a,r;
	static char t[MAXV];
	static int parent[MAXV],min[MAXV];
	do {
		done=1;
		memset(t,0,n);
		memset(parent,-1,n*sizeof(int));
		memset(min,126,n*sizeof(int));
		t[source]=1;
		do {
			done2=1;
			for(i=0;i<n;i++) if(t[i]) for(j=0;j<n;j++) if(!t[j] && f[i][j]>0) {
				a=f[i][j];
				t[j]=1; parent[j]=i; done2=0;
				if(min[i]<a) min[j]=min[i]; else min[j]=a;
				if(j==sink) { done=0; goto out; }
			}
		} while(!done2);
		break;
	out:
		i=sink; r=min[sink];
		while(i!=-1) {
			j=parent[i]; if(j==-1) break;
			f[j][i]-=r; f[i][j]+=r;
			i=j;
		}
		flow+=r;
	} while(!done);
	return flow;
}

void solve() {
	int i,j;
	scanf("%d %d %d %d",&N,&s,&t,&L);
	if(N>MAX) printf("increase MAX to %d and recompile\n",n),exit(1);
	for(i=0;i<N;i++) for(j=0;j<N;j++) scanf("%d",&c[i][j]);
	if(L==1) {
		/* we can only connect source to sink */
		printf("%.3f\n",c[s][t]/8.);
	} else if(L==2) {
		/* we can connect source to sink, as well as having one intermediate node */
		for(i=c[s][t],j=0;j<N;j++) if(j!=s && j!=t) i+=c[s][j]<c[j][t]?c[s][j]:c[j][t];
		printf("%.3f\n",i/8.);
	} else {
		/* transform graph: split each node u, call them u' and u'' */
		n=N*2;
		for(i=0;i<n;i++) for(j=0;j<n;j++) f[i][j]=0;
		/* for each edge source->v, add edge source->v' */
		for(i=0;i<N;i++) if(c[s][i]) f[s*2][i*2]=c[s][i];
		/* for each edge v->sink, add edge v''->sink */
		for(i=0;i<N;i++) if(c[i][t]) f[i*2+1][t*2]=c[i][t];
		/* for each edge u->v where none are source or sink, add edge u'->v'' */
		for(i=0;i<N;i++) if(i!=s && i!=t) for(j=0;j<N;j++) if(j!=s && j!=t && c[i][j])
			f[i*2][j*2+1]=c[i][j];
		/* for each edge u that isn't source of sink, add edge u'->u'' with INF cap */
		for(i=0;i<N;i++) if(i!=s && i!=t) f[i*2][i*2+1]=INF;
		/* flow now returns the correct answer */
		printf("%.3f\n",maxflow(s*2,t*2)/8.);
	}
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
