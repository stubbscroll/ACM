/* solution for large party, small input
   algorithm: try all combinations of male/female at every seat and only count
   assignments that are equal to its lexicographically smallest rotation */

#include <stdio.h>

int n,k;

int least(int mask) {
	int least=mask,i;
	for(i=0;i<n;i++) {
		mask=(mask>>1)+(mask&1?1<<(n-1):0);
		if(least>mask) least=mask;
	}
	return least;
}

int women(int mask) {
	int row=0,i;
	for(i=0;i<n;i++) {
		if(mask&(1<<i)) {
			if(++row>k) return 1;
		}
		else row=0;
	}
	return 0;
}

void solve() {
	int mask,r=0;
	scanf("%d %d",&n,&k);
	for(mask=0;mask<(1<<n);mask++) if(mask==least(mask) && !women(mask)) r++;
	printf("%d\n",r);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
