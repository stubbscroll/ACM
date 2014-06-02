#include <stdio.h>

typedef long long ll;

#define MAXP 10000001
#define MAXSQ 3163

/* MAXP      65536  1000000  10000000  30000000
   MAXSQ       257     1001      3163      5477
   n-primes   6542    78498    664579   1857859
*/

char sieve[MAXP];
int prime[664579];
int primes;

int createsieve()
{
   int i,j;

   memset(sieve,1,MAXP);
   for(primes=sieve[0]=sieve[1]=0,i=2;i<MAXP;i++) if(sieve[i]) {
      prime[primes++]=i;
      if(i<=MAXSQ) for(j=i*i;j<MAXP;j+=i) sieve[j]=0;
   }
}

int isprime(int n)
{
   int i,q;

   if(n<MAXP) return sieve[n];
   q=sqrt(n);
   for(i=0;i<primes && prime[i]<=q;i++) if(n%prime[i]==0) return 0;
   return 1;
}

int phid(int n)
{
   double a=n;
   int j;

   if(sieve[n]) return n-1;
   for(j=0;prime[j]<n;j++) if(n%prime[j]==0) a*=(1-1.0/prime[j]);
   return (int)a;
}

/* needs at least one element of prime[]>sqrt(n) */
ll phi(ll n)
{
   int i,q;
   ll res=1;

   i=0;
   while((ll)prime[i]*prime[i]<=n) {
      if(n%prime[i]==0) {
         res*=prime[i]-1;
         n/=prime[i];
         while(n%prime[i]==0) {
            res*=prime[i];
            n/=prime[i];
         }
      }
      i++;
   }
   if(n>1) res*=n-1;   
   return res;
}

int fc[100];
ll f[100];
int fn;

void factor(ll n)
{
   int i=0;

   fn=0;
   for(i=0;(ll)prime[i]*prime[i]<=n;++i) if(n%prime[i]==0) {
      fc[fn]=0;
      f[fn]=prime[i];
      f[fn]=prime[i];
      while(n%prime[i]==0) {
         fc[fn]++;
         n/=prime[i];
      }
      fn++;
   }
   if(n>1) {
      fc[fn]=1;
      f[fn++]=n;
   }
}

/* find all divisors of n, needs prime[]<=sqrt(n) */
ll divs[1024];
int nd;

void divbtr(int p,ll v)
{
   int i;

   if(p==fn) {
      divs[nd++]=v;
      return;
   }
   for(i=0;i<=fc[p];i++) {
      divbtr(p+1,v);
      v*=f[p];
   }
}

void divisors(ll n)
{
   factor(n);
   nd=0;
   divbtr(0,1);
}

int main()
{
   int n,i,j;
   ll v,ans;

   createsieve();
   scanf("%d",&n);
   while(n--) {
      scanf("%I64d",&v);
      divisors(v);
      ans=0;
      for(i=0;i<nd;i++) ans+=phi(divs[i]+1);
      printf("%I64d\n",ans);
   }
}
