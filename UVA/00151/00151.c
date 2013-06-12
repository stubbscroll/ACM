#include <stdio.h>

int toff[100];

int main()
{
   int n,m,i,j,rem;

   do {
      scanf("%d",&n);
      if(n==0) break;
      for(m=1;m<n;m++) {
         for(i=0;i<n;i++) toff[i]=0;
         i=0; rem=1;
         toff[0]=1;
         do {
            for(j=0;j<m;j++) {
               i=(i+1)%n;
               while(toff[i]==1) i=(i+1)%n;
            }
/*            printf("%d: ",m);
            for(j=0;j<n;j++) printf("%d ",toff[j]);
            printf("\n");*/
            toff[i]=1;
            rem++;
            if(rem<n && i==12) goto next;
         } while(rem<n);
         printf("%d\n",m);
         break;
next:
         ;     
      }
   } while(1);
}
