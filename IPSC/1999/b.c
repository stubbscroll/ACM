/* solution for candy, both inputs
   algorithm: find average, check if it's integer, find sum of differences from
   average, divide by 2 */

#include <stdio.h>

#define MAXN 10000
int a[MAXN];

int main() {
	int n,i,t,r;
	while(scanf("%d",&n),n>-1) {
		if(n>MAXN) { printf("increase MAXN to %d\n",n); break; }
		for(t=i=0;i<n;i++) scanf("%d",&a[i]),t+=a[i];
		if(t%n) puts("-1");
		else {
			for(t/=n,i=r=0;i<n;i++) r+=t-a[i]>0?t-a[i]:a[i]-t;
			printf("%d\n",r/2);
		}
	}
	return 0;
}
