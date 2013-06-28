#include <stdio.h>

int main() {
	int T,n,a,v,i,no=1;
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d",&n,&a);
		for(i=1;i<n;i++) {
			scanf("%d",&v);
			if(a<v) a=v;
		}
		printf("Case %d: %d\n",no++,a);
	}
	return 0;
}
