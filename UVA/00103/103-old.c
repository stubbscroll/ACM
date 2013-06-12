#include <stdio.h>

int b[30][10];
int f2[30][30]; /* list of all cubes i fits in */
int fm[30];

int sol[30];
int solbest[30];
int solm;

void findsubseq(int n,int z)
{
   int i,j;

   if(n>solm) {
      for(i=0;i<n;i++)
         solbest[i]=sol[i];
      solm=n;
   }
   for(j=0;j<fm[z];j++) {
      if(fm[f2[z][j]]+n>=solm) {
         sol[n]=f2[z][j];
         findsubseq(n+1,f2[z][j]);
      }
   }
}

int main()
{
   int n,d;
   int i,j,k,l;

   do {
      if(scanf("%d %d",&n,&d)==EOF)
         break;
      for(i=0;i<n;i++) {
         for(j=0;j<d;j++)
            scanf("%d",&b[i][j]);
         do {
            k=0;
            for(j=0;j<d-1;j++)
               if(b[i][j]<b[i][j+1]) {
                  k=b[i][j]; b[i][j]=b[i][j+1]; b[i][j+1]=k; k=1;
               }
         } while(k);
      }
      for(i=0;i<n;i++)
         fm[i]=0;
      for(i=0;i<n;i++)
         for(j=0;j<n;j++)
            if(i!=j) {
               l=1;
               for(k=0;k<d;k++)
                  if(b[i][k]>=b[j][k]) {
                     l=0;
                     break;
                  }
               if(l)
                  f2[i][fm[i]++]=j;
            }
      solm=1;
      solbest[0]=0;
      for(i=0;i<n;i++) {
         sol[0]=i;
         for(j=0;j<fm[i];j++) {
            if(fm[f2[i][j]]+1>=solm) {
               sol[1]=f2[i][j];
               findsubseq(2,f2[i][j]);
            }
         }
      }
      printf("%d\n",solm);
      for(i=0;i<solm;i++) {
         printf("%d",solbest[i]+1);
         if(i<solm-1)
            printf(" ");
      }
      printf("\n");
   } while(1);
}
