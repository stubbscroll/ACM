/* algorithm: output n-1 parallel lines for n regions */

#include <stdio.h>

void solve() {
	int i,n;
	scanf("%d",&n);
	printf("%d\n",n-1);
	for(i=0;i<n-1;i++) printf("0 %d\n",i);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
