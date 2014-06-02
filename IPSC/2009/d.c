/* anti-solution for don't worry about wrong answers, easy input
   observation: foo() is a really, really slow gcd implementation
   observation: Bar(x) is true iff x is prime
   for the first 9 submissions, pick any 9 lines
   for the final submission, submit a non-number */

#include <stdio.h>
#include <string.h>

#define MAXP 1000001
#define MAXSQ 1001

/* MAXP      65536  1000000  10000000  30000000
   MAXSQ       257     1001      3163      5477
   n-primes   6542    78498    664579   1857859
*/

char sieve[MAXP];
int prime[78498];
int primes;

void createsieve() {
	int i,j;
	memset(sieve,1,MAXP);
	for(primes=sieve[0]=sieve[1]=0,i=2;i<MAXP;i++) if(sieve[i]) {
		prime[primes++]=i;
		if(i<=MAXSQ) for(j=i*i;j<MAXP;j+=i) sieve[j]=0;
	}
}

int isprime(int n) {
	int i;
	if(n<MAXP) return sieve[n];
	for(i=0;i<primes && prime[i]*prime[i]<=n;i++) if(n%prime[i]==0) return 0;
	return 1;
}

int main() {
	int n,q=0;
	createsieve();
	for(n=100000003;n<198765432;n+=2) {
		q++;
		if(n%4==1 || !isprime(n) || !isprime(n+18) ||!isprime(n+36) || !isprime(n+138)
		   || !isprime(n+198) || !isprime(n+240) || !isprime(n+258)) continue;
		printf("%d\n",n);
	}
	return 0;
}
