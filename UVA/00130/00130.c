#include <stdio.h>

int circle[100];

int main()
{
   int n,k,i,p,c,j,b;

   while(1) {
      scanf("%d %d",&n,&k);
      if(n==0 && k==0) break;
      for(i=0;i<n;i++)
         circle[i]=i+1;
      p=n-1;
      if(n==1) goto end;
      c=0;
      do {
         for(i=0;i<k;i++) {
            p=(p+1)%n;
            while(circle[p]==0) p=(p+1)%n;
         }
         circle[p]=0;
         j=p;
         while(circle[p]==0) p=(p+1)%n;
         for(i=0;i<k-1;i++) {
            p=(p+1)%n;
            while(circle[p]==0) p=(p+1)%n;
         }
         circle[j]=circle[p]; circle[p]=0;
         p=j;
         c++;
      } while(c<n-1);
end:
      i=0;
      while(circle[i]==0) i++;
      c=1;
      i=circle[i];
      while(i<n+1) {
         i++; c++;
      }
      if(c>n) c-=n;
      printf("%d\n",c);
   }
}
