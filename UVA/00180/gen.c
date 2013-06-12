#include <stdio.h>

int res1,res2;
int t[1000000];

int next(int i,int n)
{
   do {
      i=(i+1)%n;
   } while(!t[i]);
   return i;
}

void sim(int n)
{
   int o,i,j;

   memset(t,1,n*sizeof(int));
   o=n; i=-1;
   while(o>1) {
      for(j=0;j<15;j++) i=next(i,n);
      t[i]=0; o--;
   }
   i=next(i,n);
   res1=i;
   res2=n-i-1;
}

int main()
{
   int i;

   for(i=2;i<151;i++) {
      sim(i);
      printf("%d: %d %d\n",i,res1,res2);
   }
}
