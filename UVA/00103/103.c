#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXV 30
#define MAXE 900
int n,ne;               /*  number of nodes, number of edges */
int from[MAXE],to[MAXE];/*  edge i: from[i] to[i] */
int gs[MAXV+1];         /*  gs[i]: start of edges from i, gs[i+1]: end */

char vis[MAXV];         /*  during dfs: 0:unvisited 1:under progress 2:done */
int res[MAXV];          /*  order of finalising in dfs */
int resn;               /*  counter */
char cycle;             /*  1: graph has cycle and no toposort exists */

/*  subroutine: sort from[],to[] on increasing from[] */
/*  (see maxflow-edge-general for a full radix sort which also sorts to[]) */
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

/*  start dfs from node u */
/*  before calling, set vis[] to 0, res[] to 0, resn to 0 */
/*  when calling from scc, c is component id, otherwise it's negative */
void dfsvisit(int u) {
  static int stack[2*MAXV];
  int sp=0,at,v;
  stack[sp++]=u; stack[sp++]=gs[u];
  vis[u]=1;
  while(sp) {
    at=stack[--sp]; u=stack[--sp];
    while(1) {
      if(at==gs[u+1]) {
        vis[u]=2;
        res[resn++]=u;
        break;
      } else {
        v=to[at];
        if(vis[v]==1) { cycle=1; at++; } /*  may want to return if cycle */
        else if(!vis[v]) {
          vis[v]=1;
          stack[sp++]=u;
          stack[sp++]=at+1;
          at=gs[v]; u=v;
        } else at++;
      }
    }
  }
}

/*  topological sort! res[] contains the nodes in backwards order */
/*  ?? UVa 11686, ?.??? seconds, n,ne<=1000000 09.08.2011 */
void toposort() {
  int i;
  memset(vis,0,n);
  /*  may want to quit early if cycle */
  for(resn=cycle=i=0;i<n;i++) if(!vis[i]) dfsvisit(i); 
}

/*  how to use:
    read n,ne (graph size)    }
    read graph in from[],to[] } <- init stage
    run counting sort         }

    for toposort: run toposort()
    for scc: run scc()

    the graph over the components have r nodes (return value from scc())
    and there is an edge from con[from[i]] to con[to[i]] whenever these
    values are different.
*/

int box[30][10];
int k;

/*	check if box a fits in box b */
int fit(int a,int b) {
	int i;
	for(i=0;i<k;i++) if(box[a][i]>=box[b][i]) return 0;
	return 1;
}

int compi(const void *A,const void *B) {
	const int *a=A,*b=B;
	if(*a<*b) return -1;
	if(*a>*b) return 1;
	return 0;
}

int main() {
	int i,j,r,v,best;
	int dp[30];
	int parent[30];
	int path[30];
	while(scanf("%d %d",&n,&k)==2) {
		for(i=0;i<n;i++) {
			for(j=0;j<k;j++) scanf("%d",&box[i][j]);
			qsort(box[i],j,sizeof(int),compi);
		}
		ne=0;
		/*	create graph */
		for(i=0;i<n;i++) for(j=0;j<n;j++) if(i!=j && fit(i,j)) from[ne]=i,to[ne++]=j;
		countingsort();
		toposort();
		for(i=0;i<n;i++) dp[i]=1,parent[i]=-1;
		for(i=0;i<n;i++) {
			r=res[n-i-1];
			for(j=gs[r];j<gs[r+1];j++) {
				v=to[j];
				if(dp[v]<dp[r]+1) dp[v]=dp[r]+1,parent[v]=r;
			}
		}
		r=best=0;
		for(i=0;i<n;i++) if(r<dp[i]) r=dp[i],best=i;
		j=0;
		while(best>-1) path[j++]=best,best=parent[best];
		printf("%d\n",r);
		for(j--;j>=0;j--) printf("%d%c",path[j]+1,j?' ':'\n');
	}
	return 0;
}
