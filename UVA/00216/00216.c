#include <stdio.h>
#include <math.h>

int coord[8][2];
int n;
double dist[8][8];
int bestpath[8];
int path[8];
int taken[8];
double plen[9];
double minlen;

void backtrack(int p)
{
   int i;

   if(p==n) {
      if(plen[p-1]<minlen) {
         minlen=plen[p-1];
         for(i=0;i<n;i++)
            bestpath[i]=path[i];
      }
      return;
   }
   for(i=0;i<n;i++)
      if(taken[i]==0) {
         plen[p]=plen[p-1]+dist[path[p-1]][i];
         if(plen[p]>minlen) continue;
         path[p]=i;
         taken[i]=1;
         backtrack(p+1);
         taken[i]=0;
      }
}

int main()
{
   int i,j,a,b,cases=1;

   while(1) {
      scanf("%d",&n);
      if(n==0) break;
      for(i=0;i<n;i++)
         scanf("%d %d",&coord[i][0],&coord[i][1]);
      for(i=0;i<n;i++)
         for(j=0;j<n;j++) {
            a=coord[i][0]-coord[j][0];
            b=coord[i][1]-coord[j][1];
            dist[i][j]=sqrt(a*a+b*b)+16.0;
         }
      minlen=9999999.9;
      for(i=0;i<n;i++) taken[i]=0;
      plen[0]=0.0;
      for(i=0;i<n-1;i++) {
         path[0]=i;
         taken[i]=1;
         backtrack(1);
         taken[i]=0;
      }
      printf("**********************************************************\n");
      printf("Network #%d\n",cases++);
      for(i=0;i<n-1;i++)
         printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n",
            coord[bestpath[i]][0],coord[bestpath[i]][1],
            coord[bestpath[i+1]][0],coord[bestpath[i+1]][1],
            dist[bestpath[i]][bestpath[i+1]]);
      printf("Number of feet of cable required is %.2f.\n",minlen);
   }
}
