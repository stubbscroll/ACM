/* solution to electrical circuits, easy input.
   algorithm: bitmask-dp with memoization on small cases,
   brute force without dp on the one large easy case.
   c++ because i wanted to use map */

#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define MAXV 1000
char g[MAXV][MAXV];
int n,m;

map<ull,ull> dp;

char taken[MAXV];

ull btr2() {
	int ix,j;
	ull r=0;
	/* find first 0 non-taken */
	for(ix=0;ix<n;ix++) if(!taken[ix]) break;
	if(ix==n) return 1;
	/* try all ways to match it */
	for(j=ix+1;j<n;j++) if(g[ix][j]) taken[ix]=taken[j]=1,r+=btr2(),taken[ix]=taken[j]=0;
	return r;
}

void largesolve() {
	memset(taken,0,n);
	printf("%lld\n",btr2());
}

/* 1-bits in mask correspond to matched nodes */
ull btr(ull mask) {
	int ix,j;
	ull r=0;
	if(dp.find(mask)!=dp.end()) return dp[mask];
	/* find first 0-bit */
	for(ix=0;ix<n;ix++) if(!(mask&(1ULL<<ix))) break;
	if(ix==n) return dp[mask]=1;
	/* try all ways to match it */
	for(j=ix+1;j<n;j++) if(g[ix][j] && !(mask&(1ULL<<j))) r+=btr(mask+(1ULL<<ix)+(1ULL<<j));
	return dp[mask]=r;
}

void solve() {
	int a,b,i;
	scanf("%d %d",&n,&m);
	/* coordinates don't matter, throw them */
	for(i=0;i<n;i++) scanf("%d %d",&a,&a);
	memset(g,0,sizeof(g));
	for(i=0;i<m;i++) {
		scanf("%d %d",&a,&b);
		g[--a][--b]=1;
		g[b][a]=1;
	}
	if(n>63) return largesolve();
	dp.clear();
	printf("%llu\n",btr(0));
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
