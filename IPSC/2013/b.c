#include <stdio.h>
#include <math.h>
typedef long long ll;
ll split(int a) {
	int x,y;
	if(a==1) return 0;
	if(a%3==0) return (a/3LL)*(2*a/3LL)+split(a/3)+split(2*a/3);
	else if(a%2==0) return (a/2LL)*(a/2LL)+2*split(a/2);
	else return (a-1)+split(a-1);
}
int main() {
	int T,a,lo,hi,i,x,y;
	ll best;
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&a);
		printf("%I64d\n",split(a));
		continue;
		
		lo=a/2-1000;
		hi=a/2+1000;
		if(lo<1) lo=1;
		if(hi>a) hi=a;
		best=0;
		for(i=lo;i<=hi;i++) {
			
		}
	}
	return 0;
}
