/* will time out for n=20000 */

#include <stdio.h>

int a[22222],n;

int main() {
	long long r;
	int T,i,j,k;
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(i=0;i<n;i++) scanf("%d",&a[i]);
		for(r=i=0;i<n;i++) for(j=i+1;j<n;j++) for(k=j+1;k<n;k++) if((a[i]<=a[j] && a[j]<=a[k]) || (a[i]>=a[j] && a[j]>=a[k])) r++;
		printf("%I64d\n",r);
	}
	return 0;
}
