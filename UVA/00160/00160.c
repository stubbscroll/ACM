#include <stdio.h>

int primes[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,
   89,97,9999};
int f[26];

void factor(int n)
{
   int i;

   for(i=0;primes[i]<=n;i++) {
      if(n==1) break;
      while(n%primes[i]==0) {
         f[i]++;
         n/=primes[i];
      }
   }
}

int main()
{
   int n,i;

   do {
      scanf("%d",&n);
      if(n==0) break;
      for(i=0;i<26;i++) f[i]=0;
      for(i=2;i<=n;i++) {
         factor(i);
      }
      printf("%3d! =",n);
      for(i=0;f[i];i++) {
         if(i>0 && i%15==0) printf("\n      ");
         printf("%3d",f[i]);
      }
      printf("\n");
   } while(1);
}
