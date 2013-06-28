#include <stdio.h>

int main() {
	int T,no=1,v;
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&v);
		printf("Case %d:\n",no++);
		printf("%d %d\n%d %d\n%d %d\n%d %d\n",v*(-9)/4,v*3/2,v*11/4,v*3/2,v*11/4,v*(-3)/2,v*(-9)/4,v*(-3)/2);
	}
	return 0;
}
