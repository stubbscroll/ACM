#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef long long ll;

int n;
int factor[32000];

#define MAXP 32000
#define MOD 1000000007

char sieve[MAXP];
int prime[32000];
int primes;

int faktor[100000];
int fn;

int compi(const void *A,const void *B) {
	const int *a=A,*b=B;
	if(*a<*b) return -1;
	if(*a>*b) return 1;
	return 0;
}

void createsieve() {
	int i,j,q;
	memset(sieve,1,sizeof(sieve));
	q=sqrt(MAXP);
	for(sieve[0]=sieve[1]=0,i=2;i<=q;i++) if(sieve[i]) for(j=i*i;j<MAXP;j+=i) sieve[j]=0;
}

void genprimes() {
	int i;
	for(primes=i=0;i<MAXP;i++) if(sieve[i]) prime[primes++]=i;
}

#define MAXL 17000
#define MAXR 600
int p[MAXL][MAXR];

void pascal() {
	int i,j;
	for(i=0;i<MAXL;i++) {
		p[i][0]=1;
		if(i<MAXR) p[i][i]=1;
		for(j=1;j<MAXR && j<i;j++) {
			p[i][j]=p[i-1][j]+p[i-1][j-1];
			if(p[i][j]>=MOD) p[i][j]-=MOD;
		}
	}
}

void factorize(int a) {
	int i;
	for(i=0;i<primes;i++) {
		while(a%prime[i]==0) {
			a/=prime[i];
			factor[i]++;
		}
	}
	if(a>1) {
		if(a<MAXP) {
			for(i=0;i<primes;i++) if(a==prime[i]) { factor[i]++; break; }
		}
		else faktor[fn++]=a;
	}
}

void readinput() {
	int i,a;
	fn=0;
	if(scanf("%d",&n)!=1) exit(0);
	memset(factor,0,sizeof(factor));
	for(i=0;i<n;i++) {
		scanf("%d",&a);
		factorize(a);
	}
}

void calc() {
	int res=1,i,z,ff;
	int K=n,N;
	for(i=0;i<primes;i++) if(factor[i]) {
		N=factor[i];
/*		printf("%d: put %d balls in %d boxes: (%d choose %d) = %d\n",prime[i],N,K,N+K-1,K-1,p[N+K-1][K-1]);*/
		if(p[N+K-1][K-1]==0) while(1);
		res=(ll)res*p[N+K-1][K-1]%MOD;
	}
	if(fn) {
		if(fn>1) qsort(faktor,fn,sizeof(int),compi);
/*		for(i=0;i<fn;i++) printf("%d ",faktor[i]);*/
		for(i=0;i<fn;) {
			z=0;
			ff=faktor[i];
			while(i<fn && faktor[i]==ff) i++,z++;
			N=z;
/*			printf("%d: put %d balls in %d boxes: (%d choose %d) = %d\n",ff,N,K,N+K-1,K-1,p[N+K-1][K-1]);*/
			if(p[N+K-1][K-1]==0) while(1);
			res=(ll)res*p[N+K-1][K-1]%MOD;
		}
	}
	printf("%d\n",res);
}

int main() {
	createsieve();
	genprimes();
	pascal();
	while(1) {
		readinput();
		calc();
	}
	return 0;
}
