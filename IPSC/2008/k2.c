/* solution for k equal digits, hard input
   algorithm: shamelessly based on editorial, but i was too lazy to implement
   proper factorization */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAXR 100

typedef long long ll;

int k,r;
ll a[MAXR];
ll mod[MAXR];

ll findlength(int d,ll p) {
	ll mod=d%p;
	int len=1;
	while(1) {
		if(!mod) return len;
		if(len>p*3) return -1; /* no solution */
		len++;
		mod=(mod*10+d)%p;
	}
}

ll gcd(ll a,ll b) {
	if(!b) return a;
	return gcd(b,a%b);
}

int findhigh(int n,int d,ll p,ll q) {
	ll lenp=findlength(d,p),lenq=findlength(d,q),l;
	if(lenp<0 || lenq<0) return -1;
	l=lenp/gcd(lenp,lenq)*lenq;
	return n/l*l;
}

void solve() {
	int i,best=1,bestd=0,d,cur;
	ll p,q;
	scanf("%d %d",&k,&r);
	if(r>MAXR) printf("increase MAXR to %d and recompile\n",r),exit(1);
	for(i=0;i<r;i++) scanf("%I64d",&a[i]);
	for(i=0;i<r;i++) {
		/* find factorization a[i]=p*q where p is close-ish to q and gcd(p,q)=1 */
		for(p=sqrt(a[i]);a[i]%p || gcd(p,a[i]/p)>1;p--);
		q=a[i]/p;
		for(d=1;d<10;d++) {
			cur=findhigh(k,d,p,q);
			if(best<cur || (best==cur && bestd<d)) best=cur,bestd=d;
		}
	}
	printf("%d %d\n",best,bestd);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
