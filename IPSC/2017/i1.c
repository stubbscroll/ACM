/* algorithm: for each node, remove it and test if there is no path.
   run scc and don't include nodes that are part of a cycle (such nodes
   are in components with >1 nodes).
   to sort nodes in order, find any path and use the order from the path */

#include <stdio.h>
#include <string.h>

#define MAXV 500000
#define MAXE 1000000

int n,ne;               /* number of nodes, number of edges */
int from[MAXE],to[MAXE];/* edge i: from[i] to[i] */
int gs[MAXV+1];         /* gs[i]: start of edges from i, gs[i+1]: end */

char vis[MAXV];         /* during dfs: 0:unvisited 1:under progress 2:done */
int res[MAXV];          /* order of finalising in dfs */
int resn;               /* counter */
char cycle;             /* 1: graph has cycle and no toposort exists */

int con[MAXV];          /* id of connected component for vertex i */
int r;

/* subroutine: sort from[],to[] on increasing from[] */
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

/* start dfs from node u */
/* before calling, set vis[] to 0, res[] to 0, resn to 0 */
/* when calling from scc, c is component id, otherwise it's negative */
void dfsvisit(int u,int c) {
	static int stack[2*MAXV];
	int sp=0,at,v;
	stack[sp++]=u; stack[sp++]=gs[u];
	vis[u]=1;
	if(c>=0) con[u]=c;      /* set component id */
	while(sp) {
		at=stack[--sp]; u=stack[--sp];
		while(1) {
			if(at==gs[u+1]) {
				vis[u]=2;
				res[resn++]=u;
				break;
			} else {
				v=to[at];
				if(vis[v]==1) { cycle=1; at++; } /* may want to return if cycle */
				else if(!vis[v]) {
					vis[v]=1;
					if(c>=0) con[v]=c;  /* set component id */
					stack[sp++]=u;
					stack[sp++]=at+1;
					at=gs[v]; u=v;
				} else at++;
			}
		}
	}
}

/* return the number of connected components */
/* for vertex i, id of component is in con[i] */
/* OK UVa 11504 0.146 seconds, n<=100000, ne<=100000 2013-06-13 */
/* OK UVa 11709 0.860 seconds, n<=1000, ne<=999000 2011-08-09 */
/* OK UVa-live 4287 (NWERC 2008 problem B), n<=20000, ne<=50000, 0.088 seconds, 2011-08-09 */
/* OK NWERC 2012 I "Idol" n<=2000 e<=4000 2012-11-25 */
/* OK IPSC 2014-practice U "urban planning" n<=300 e<=90000 2014-06-14 */
int scc() {
	static int dfsres[MAXV];
	int i,t,c=0;
	memset(vis,0,n);
	for(resn=i=0;i<n;i++) if(!vis[i]) dfsvisit(i,-1);
	/* transpose graph */
	memcpy(dfsres,res,n*sizeof(int));
	for(i=0;i<ne;i++) t=from[i],from[i]=to[i],to[i]=t;
	countingsort();
	memset(vis,0,n);
	for(resn=0,i=n-1;i>=0;i--) if(!vis[dfsres[i]]) dfsvisit(dfsres[i],c++);
	return c;
}

char hacked[MAXV];
char incycle[MAXV];

int qs,qe,q[MAXV];
char visited[MAXV];
int prev[MAXV];

/* return 1 if there is a path from 0 to n-1 that avoids forbidden node */
int ispath(int forbidden) {
	int i,u,v;
	for(i=0;i<n;i++) visited[i]=0;
	qs=qe=0;
	if(0!=forbidden) {
		visited[0]=1;
		q[qe++]=0;
	}
	while(qs<qe) {
		u=q[qs++];
		for(i=gs[u];i<gs[u+1];i++) {
			v=to[i];
			if(visited[v] || v==forbidden) continue;
			if(v==n-1) return 1;
			q[qe++]=v;
			visited[v]=1;
		}
	}
	return 0;
}

int path[MAXV],pn;

int findpath() {
	int i,u,v;
	for(i=0;i<n;i++) visited[i]=0;
	for(i=0;i<n;i++) prev[i]=-1;
	qs=qe=0;
	q[qe++]=0;
	visited[0]=1;
	while(qs<qe) {
		u=q[qs++];
		for(i=gs[u];i<gs[u+1];i++) {
			v=to[i];
			if(visited[v]) continue;
			q[qe++]=v;
			visited[v]=1;
			prev[v]=u;
			if(v==n-1) goto won;
		}
	}
	return 0;
won:
	/* find path */
	u=n-1;
	pn=0;
	while(u) {
		path[pn++]=u;
		u=prev[u];
	}
	path[pn++]=u;
	return 1;
}

int concnt[MAXV];

void solve() {
	int i,cnt=0,t;
	scanf("%d %d",&n,&ne);
	for(i=0;i<ne;i++) scanf("%d %d",&from[i],&to[i]),from[i]--,to[i]--;
	countingsort();
	r=scc();
	/* scc transposed graph, revert */
	for(i=0;i<ne;i++) t=from[i],from[i]=to[i],to[i]=t;
	countingsort();
	for(i=0;i<r;i++) concnt[i]=0;
	for(i=0;i<n;i++) concnt[con[i]]++;
	for(i=0;i<n;i++) incycle[i]=concnt[con[i]]>1;
	for(i=0;i<ne;i++) if(from[i]==to[i]) incycle[from[i]]=1;
	for(i=0;i<n;i++) hacked[i]=0;
	for(i=0;i<n;i++) hacked[i]=!ispath(i);
	if(!findpath()) { puts("0\n"); return; }
	for(i=pn-1;i>=0;i--) if(hacked[path[i]] && !incycle[path[i]]) cnt++;
	printf("%d\n",cnt);
	for(i=pn-1;i>=0;i--) if(hacked[path[i]] && !incycle[path[i]]) printf("%d ",path[i]+1);
	putchar('\n');
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
