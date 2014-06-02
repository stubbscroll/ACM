#include <stdio.h>

#define M 256

double p[M][M];
int n;
int m;
int z[M];
double p2[M][M];

void floyd(double p[M][M],int n)
{
   int i,j,k;
   for(k=0;k<n;k++) for(i=0;i<n;i++) for(j=0;j<n;j++) {
      if(p[i][j]<p[i][k]*p[k][j]) p[i][j]=p[i][k]*p[k][j];
   }
}

void floyd2(double p[M][M],int n)
{
   int i,j,k;
   for(k=0;k<n;k++) for(i=0;i<n;i++) for(j=0;j<n;j++) {
      if(p[i][j]>p[i][k]+p[k][j]) p[i][j]=p[i][k]+p[k][j];
   }
}

int main()
{
   int cases,i,j,k,size;

   scanf("%d",&cases);
   while(cases--) {
      scanf("%d",&n);
      for(i=0;i<n;i++) for(j=0;j<n;j++) {
         scanf("%d",&k);
         p[i][j]=k/100.0;
      }
      scanf("%d",&m);
      for(i=0;i<m;i++) scanf("%d",&z[i]),z[i]--;
      scanf("%d",&size);
      floyd(p,n);
      for(i=0;i<m;i++) for(j=0;j<m;j++) {
         p2[i][j]=size/p[z[i]][z[j]];
      }
      floyd2(p2,m);
      printf("%.6f\n",p2[0][1]);
   }
}
