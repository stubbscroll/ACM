/* solution for two covers, easy input
   algorithm: for each position, check all pairs of pieces for a well-cover */

#include <stdio.h>

int b[1111],e[1111];
int l,n,k;

void solve() {
	int i,u,v,r=0;
	scanf("%d %d %d",&l,&n,&k);
	for(i=0;i<n;i++) scanf("%d %d",&b[i],&e[i]),b[i]--,e[i]--;
	for(i=0;i<l;i++) {
		for(u=0;u<n;u++) if(b[u]<=i-k && i<=e[u]) for(v=0;v<n;v++) if(u!=v && b[v]<=i && i+k<=e[v]) goto ok;
		r++;
	ok:;
	}
	printf("%d\n",r);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
