/* solution for urban planning, hard input
   algorithm: find strongly connected components and find component tree.
   for each component, output any cycle consisting of all nodes in it.
   output all edges in the component tree. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* find strongly connected components with edge lists! */

#define MAXV 300
#define MAXE (MAXV*MAXV)
int n,ne;               /* number of nodes, number of edges */
int from[MAXE],to[MAXE];/* edge i: from[i] to[i] */
int gs[MAXV+1];         /* gs[i]: start of edges from i, gs[i+1]: end */

char vis[MAXV];         /* during dfs: 0:unvisited 1:under progress 2:done */
int res[MAXV];          /* order of finalising in dfs */
int resn;               /* counter */
char cycle;             /* 1: graph has cycle and no toposort exists */

int con[MAXV];          /* id of connected component for vertex i */

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

char g2[MAXV][MAXV];
int rep[MAXV];        /* for each component, keep a representative */
int n2;
int sykkel[MAXV],cn;
int outa[MAXE],outb[MAXE],on;

void solve() {
	int i,j,k,change;
	char s[MAXV+1];
	scanf("%d",&n);
	if(n>MAXV) printf("increase MAXV to %d and recompile\n",n),exit(1);
	for(ne=i=0;i<n;i++) {
		scanf("%s",s);
		for(j=0;j<n;j++) if(j!=i && s[j]=='1') from[ne]=i,to[ne++]=j;
	}
	countingsort();
	n2=scc();
	/* find component graph */
	for(i=0;i<n;i++) for(j=0;j<n;j++) g2[i][j]=0;
	for(i=0;i<ne;i++) g2[con[to[i]]][con[from[i]]]=1;
	/* turn it into a tree by un-transitivizing it */
	do {
		change=0;
		for(k=0;k<n2;k++) for(i=0;i<n2;i++) if(k!=i && g2[i][k]) for(j=0;j<n2;j++) if(k!=j && i!=j) {
			if(g2[i][j] && g2[i][k] && g2[k][j]) g2[i][j]=0,change=1;
		}
	} while(change);
	/* find representative */
	for(i=0;i<n;i++) rep[con[i]]=i;
	/* output tree edges */
	for(on=i=0;i<n2;i++) for(j=0;j<n2;j++) if(i!=j && g2[i][j]) outa[on]=rep[i]+1,outb[on++]=rep[j]+1;
	/* output cycle in each component */
	for(i=0;i<n2;i++) {
		for(cn=j=0;j<n;j++) if(i==con[j]) sykkel[cn++]=j;
		if(cn>1) for(j=0;j<cn;j++) outa[on]=sykkel[j]+1,outb[on++]=sykkel[(j+1)%cn]+1;
	}
	printf("%d\n",on);
	for(i=0;i<on;i++) printf("%d %d\n",outa[i],outb[i]);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
