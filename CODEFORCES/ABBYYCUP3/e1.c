/* solution to E1 */
#include <stdio.h>
#define MOD 1000000000
typedef long long ll;

int a[100100];
int n,m;

void op1() {
	int x,v;
	scanf("%d %d",&x,&v);
	a[x]=v;
}

ll f[100100];

void op2() {
	int l,r,L;
	ll ans=0;
	scanf("%d %d",&l,&r);
	L=l;
	while(l<=r) {
		ans=(ans+f[l-L]*a[l])%MOD;
		l++;
	}
	printf("%d\n",(int)ans);
}

void op3() {
	puts("lol");
}

int main() {
	int i,t;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	f[0]=f[1]=1;
	for(i=2;i<100100;i++) f[i]=(f[i-1]+f[i-2])%MOD;
	while(m--) {
		scanf("%d",&t);
		if(t==1) op1();
		else if(t==2) op2();
		else op3();
	}
	
	return 0;
}
