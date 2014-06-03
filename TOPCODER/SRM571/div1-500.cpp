#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
vector<int> val;
int bc[65536],best;
inline int bitcount(ull mask) {
	return bc[mask>>48]+bc[(mask>>32)&65535]+bc[(mask>>16)&65535]+bc[mask&65535];
}
ull g[64]; /* g[i] bit j is set if there is an edge between nodes i and j */
int n;
void process(ull mask) {
	int i,cur=0;
	for(i=0;i<n;i++) if(mask&(1ULL<<i)) cur+=val[i];
	if(best<cur) best=cur;
}
/* without pivoting, times out */
void bronkerboschbitbasic(ull R,ull P,ull X) {
	int v;
	if(bitcount(R|P)*3<2*n) return;
	if(!(P|X)) process(R);
	else for(v=0;v<n;v++) if(P&(1ULL<<v)) {
		bronkerboschbitbasic(R|(1ULL<<v),P&g[v],X&g[v]);
		P-=1ULL<<v;
		X|=1ULL<<v;
	}
}
/* with pivoting */
void bronkerboschbitpivot(ull R,ull P,ull X) {
	ull Q;
	int v,u;
	if(bitcount(R|P)*3<2*n) return;
	if(!(P|X)) process(R);
	else {
		for(u=0;u<n;u++) if((P|X)&(1ULL<<u)) break;
		for(Q=P&~g[u],v=0;v<n;v++) if(Q&(1ULL<<v)) {
			bronkerboschbitpivot(R|(1ULL<<v),P&g[v],X&g[v]);
			P-=1ULL<<v;
			X|=1ULL<<v;
		}
	}
}

struct MagicMolecule {
	int maxMagicPower(vector <int> magicPower, vector <string> magicBond) {
		int i,j;
		for(bc[0]=0,i=1;i<65536;i++) bc[i]=bc[i>>1]+(i&1);
		val=magicPower;
		n=val.size();
		memset(g,0,sizeof(g));
		for(i=0;i<n;i++) for(j=0;j<n;j++) if(magicBond[i][j]=='Y') g[i]|=1ULL<<j;
		best=-1;
		bronkerboschbitpivot(0,(1ULL<<n)-1,0);
		return best;
	}
};
