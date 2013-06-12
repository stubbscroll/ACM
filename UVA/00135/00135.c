#include <stdio.h>

int main()
{
   int k,i,j,l,m;
   int first=1;

   while(scanf("%d",&k)==1) {
      if(!first) printf("\n");
      first=0;
      for(i=0;i<k;i++) {
         printf("1");
         for(j=1;j<k;j++) printf(" %d",i*(k-1)+j+1);
         printf("\n");
      }
      for(i=0;i<k-1;i++) {
         for(j=0;j<k-1;j++) {
            printf("%d",i+2);
            /* create a k*k grid of k*k identity matrices */
            for(m=0;m<k-1;m++)
               printf(" %d",k+1+(m*(k-i-1)+j)%(k-1)+m*(k-1));
            printf("\n");
         }
      }
   }
}
