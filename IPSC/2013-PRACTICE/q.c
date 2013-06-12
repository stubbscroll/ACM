#include <stdio.h>
#include <math.h>

typedef long long ll;

int a[1000];

int main() {
	int T,mu,V,i,q;
	ll v;
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d",&mu,&V);
		v=V*1000LL;
		for(i=0;i<500;i++) {
			q=sqrt(v/2);
			a[i*2]=mu-q;
			a[i*2+1]=mu+q;
			v-=2LL*q*q;
		}
		if(v) printf("ERROR %I64d left\n",v);
		puts("1000");
		for(i=0;i<1000;i++) printf("%d%c",a[i],i==999?'\n':' ');
	}
	return 0;
}
