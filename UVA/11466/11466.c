#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAXP 10000001
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;

char sieve[MAXP];
int prime[6664579];
int primes;

void createsieve() {
	int i,j,q;
	memset(sieve,1,sizeof(sieve));
	q=sqrt(MAXP);
	for(sieve[0]=sieve[1]=0,i=2;i<=q;i++) if(sieve[i])
		for(j=i*i;j<MAXP;j+=i) sieve[j]=0;
}

void genprimes() {
	int i;
	for(primes=i=0;i<MAXP;i++) if(sieve[i]) prime[primes++]=i;
}

void factor(ull n,ull *f,int *fc,int *fn) {
	int i;
	for(*fn=i=0;i<primes && (ull)prime[i]*prime[i]<=n;i++) if(n%prime[i]<1) {
		f[*fn]=prime[i];
		fc[*fn]=1;
		n/=prime[i];
		while(n%prime[i]<1) n/=prime[i],fc[*fn]++;
		(*fn)++;
	}
	if(n>1) f[*fn]=n,fc[(*fn)++]=1;
}

int main() {
	ull f[100];
	int fc[100],fn;
	ll n;
	createsieve();
	genprimes();
	while(scanf("%lld",&n),n) {
		if(n<0) n=-n;
		factor((ull)n,f,fc,&fn);
		if(fn<2) puts("-1");
		else printf("%llu\n",f[fn-1]);
	}
	return 0;
}
