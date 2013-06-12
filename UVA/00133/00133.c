#include <stdio.h>

int circle[20];

int increase(i,n)
{
   i=(i+1)%n;
   while(circle[i]==0)
      i=(i+1)%n;
   return i;
}

int decrease(i,n)
{
   i--; if(i==-1) i=n-1;
   while(circle[i]==0) {
      i--; if(i==-1) i=n-1;
   }
   return i;
}

int main()
{
   int n,k,m,i,j,l,first,dec;

   while(1) {
      scanf("%d %d %d",&n,&k,&m);
      if(k==0 && n==0 && m==0) break;
      for(i=0;i<n;i++)
         circle[i]=1;
      i=n-1;
      j=0;
      first=1;
      dec=n;
      do {
/*         for(l=0;l<n;l++)
            printf("(%d) ",circle[l]);*/
         l=k;
         while(l--)
            i=increase(i,n);
         l=m;
         while(l--)
            j=decrease(j,n);
         if(!first)
            printf(", ");
         else
            printf(" ");
         first=0;
         dec--;
         if(i!=j) {
            printf("%2d %2d",i+1,j+1);
            dec--;
         }
         if(i==j)
            printf("%2d",i+1);
         circle[i]=circle[j]=0;
      } while(dec);
      printf("\n");
   }
}
