#include <stdio.h>

int num[20];
int temp[20];
int test[20];

int c[21][21];

/* copied from text book and stripped */
int lcslength(int *y,int n)
{
   int i,j;

   for(i=1;i<=n;i++) c[i][0]=0;
   for(j=0;j<=n;j++) c[0][j]=0;

   for(i=1;i<=n;i++)
      for(j=1;j<=n;j++)
         if(i-1==y[j-1])
            c[i][j]=c[i-1][j-1]+1;
         else if(c[i-1][j]>=c[i][j-1])
            c[i][j]=c[i-1][j];
         else
            c[i][j]=c[i][j-1];
   return c[n][n];
}

int main()
{
   int n,i;

   scanf("%d",&n);
   for(i=0;i<n;i++)
      scanf("%d",&num[i]);
   while(1) {
      for(i=0;i<n;i++) {
         if(scanf("%d",&temp[i])!=1) return 0;
         test[num[i]-1]=temp[i]-1;
      }
      printf("%d\n",lcslength(test,n));
   }
}
