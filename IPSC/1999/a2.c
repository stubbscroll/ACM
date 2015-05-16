/* solution for billboard, both inputs
   algorithm: direct implementation of the suggested solution, where lists
   are represented using bitmasks. */

#include <stdio.h>

#define MAXV 600
#define MAXE 10000
#define MAXZ 10000

int n,ne;               /* number of nodes, number of edges */
int from[MAXE],to[MAXE];/* edge i: from[i] to[i] */
int gs[MAXV+1];         /* gs[i]: start of edges from i, gs[i+1]: end */
int col[MAXV];
int bc[]={0,1,1,2,1,2,2,3};
int colno[]={0,1,2,0,3};

int z[MAXZ],zn;      /* stack of changes */

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

int btr() {
	int i,j,best=9,bestix=-1,old,q;
	/* detect failure */
	for(i=0;i<ne;i++) if(bc[col[from[i]]]==1 && col[from[i]]==col[to[i]]) return 0;
	for(i=0;i<n;i++) if(!col[i]) return 0;
	/* find a node to assign */
	for(i=0;i<n;i++) if(bc[col[i]]>1 && best>bc[col[i]]) {
		best=bc[col[i]];
		bestix=i;
		if(best==2) break;
	}
	if(bestix<0) {
		/* we solved it */
		for(i=0;i<n;i++) printf("%d%c",colno[col[i]],i==n-1?'\n':' ');
		return 1;
	}
	for(i=0;i<3;i++) if(col[bestix]&(1<<i)) {
		old=col[bestix];
		col[bestix]=1<<i;
		/* change neighbour lists */
		q=zn;
		for(j=gs[bestix];j<gs[bestix+1];j++) if(col[to[j]]&(1<<i)) {
			if(col[to[j]]==1<<i) goto restore;
			if(zn==MAXZ) puts("increase MAXZ");
			z[zn++]=to[j]; z[zn++]=col[to[j]];
			col[to[j]]&=~(1<<i);
		}
		if(btr()) return 1;
		/* restore neighbour lists */
	restore:
		while(zn>q) col[z[zn-2]]=z[zn-1],zn-=2;
		col[bestix]=old;
	}
	return 0;
}

void solve() {
	int i;
	scanf("%d %d",&n,&ne);
	if(n>MAXV) printf("increase MAXV to %d\n",n);
	if(ne>MAXE) printf("increase MAXE to %d\n",ne);
	for(i=0;i<ne;i++) scanf("%d %d",&from[i],&to[i]),from[i]--,to[i]--;
	countingsort();
	for(i=0;i<n;i++) col[i]=7;
	/* fix billboard 1 at vertex 0 and remove 1 from neighbours */
	col[0]=1;
	for(i=gs[0];i<gs[1];i++) col[to[i]]&=6;
	zn=0;
	if(!btr()) puts("-1");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
