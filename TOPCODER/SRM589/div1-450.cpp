#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ull g[64]; /* g[i] bit j is set if there is an edge between nodes i and j */
int n;
int bc[65536];
int best;
inline int bitcount(ull mask) {
	return bc[mask>>48]+bc[(mask>>32)&65535]+bc[(mask>>16)&65535]+bc[mask&65535];
}
void bronkerboschbitpivot(ull R,ull P,ull X) {
	ull Q;
	int v,u;
	if(best>=bitcount(R|P)) return;
	if(!(P|X)) best=bitcount(R);
	else {
		for(u=0;u<n;u++) if((P|X)&(1ULL<<u)) break;
		for(Q=P&~g[u],v=0;v<n;v++) if(Q&(1ULL<<v)) {
			bronkerboschbitpivot(R|(1ULL<<v),P&g[v],X&g[v]);
			P-=1ULL<<v;
			X|=1ULL<<v;
		}
	}
}
int solve(ull z) {
	int i;
	for(i=0;i<n;i++) if(z&(1ULL<<i)) g[i]^=z-(1ULL<<i);
	best=0;
	bronkerboschbitpivot(0,z,0);
	return bitcount(z)-best;
}
int colix(char c) {
	if(c=='R') return 0;
	if(c=='G') return 1;
	if(c=='B') return 2;
	return -1;
}
struct GearsDiv1 {
	int getmin(string C, vector <string> graph) {
		ull z;
		int mask,best=1231,i,j,cur;
		for(bc[0]=0,i=1;i<65536;i++) bc[i]=bc[i>>1]+(i&1);
		n=graph.size();
		for(mask=4;mask<7;mask++) {
			/* left */
			memset(g,0,sizeof(g)); z=0;
			for(i=0;i<n;i++) if(!(mask&(1<<colix(C[i])))) for(z|=1ULL<<i,j=0;j<n;j++) if(graph[i][j]=='Y' && !(mask&(1<<colix(C[j])))) g[i]|=1ULL<<j;
			cur=solve(z);
			/* right */
			memset(g,0,sizeof(g)); z=0;
			for(i=0;i<n;i++) if(mask&(1<<colix(C[i]))) for(z|=1ULL<<i,j=0;j<n;j++) if(graph[i][j]=='Y' && (mask&(1<<colix(C[j])))) g[i]|=1ULL<<j;
			cur+=solve(z);
			if(best>cur) best=cur;
		}
		return best;
	}
};
