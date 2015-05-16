/* solution for billboard, easy input
   observation: for easy, there are at most 21 crossings. for crossing 1 we can
   hardcode billboard 1, then do brute force: pick a neighbour of a crossing, then
   try the 2 possible billboards, 2^20 combinations, runtime O(2^n * e) */

#include <stdio.h>

#define MAXV 21
#define MAXE 32

int n,ne;               /* number of nodes, number of edges */
int from[MAXE],to[MAXE];/* edge i: from[i] to[i] */
int r[MAXV];

int btr(int left) {
	int i,j;
	for(i=0;i<ne;i++) if(r[from[i]] && r[from[i]]==r[to[i]]) return 0;
	if(!left) {
		for(i=0;i<n;i++) printf("%d%c",r[i],i==n-1?'\n':' ');
		return 1;
	}
	for(i=0;i<ne;i++) if((r[from[i]]>0)+(r[to[i]]>0)==1) {
		if(!r[from[i]]) {
			for(j=1;j<4;j++) if(r[to[i]]!=j) {
				r[from[i]]=j;
				if(btr(left-1)) return 1;
				r[from[i]]=0;
			}
		} else {
			for(j=1;j<4;j++) if(r[from[i]]!=j) {
				r[to[i]]=j;
				if(btr(left-1)) return 1;
				r[to[i]]=0;
			}
		}
		return 0;
	}
	return 0;
}

void solve() {
	int i,a,b;
	scanf("%d %d",&n,&ne);
	if(n>MAXV) printf("increase MAXN to %d\n",n);
	if(ne>MAXE) printf("increase MAXE to %d\n",ne);
	for(i=0;i<ne;i++) {
		scanf("%d %d",&a,&b);
		from[i]=a-1;
		to[i]=b-1;
	}
	for(i=0;i<n;i++) r[i]=0;
	r[0]=1;
	if(!btr(n-1)) puts("-1");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
