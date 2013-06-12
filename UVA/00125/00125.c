#include <stdio.h>
#define MAX 25

int g[MAX][MAX];
int c[MAX][MAX];
int gvar[MAX][MAX];
int gn[MAX];
int pa[MAX][MAX][MAX];

int x;

int path[MAX];
int cycle[MAX];

void backtrack(int p,int n)
{
   int i,j,not;

   path[n]=p;
   for(i=0;i<=n;i++)
      pa[path[0]][p][path[i]]=1;
   for(i=0;i<n;i++)
      if(path[i]==p) {
         for(j=0;j<n;j++) {
            c[path[j]][p]=-1;
            if(j>=i) cycle[path[j]]=1;
         }
         return;
      }
   for(i=0;i<gn[p];i++) {
      if(c[path[0]][gvar[p][i]]>-1)
         c[path[0]][gvar[p][i]]++;
      backtrack(gvar[p][i],n+1);
   }
}

int main()
{
   int n,i,j,k,cy,city=0;

   while(scanf("%d",&n)==1) {
      for(i=0;i<MAX;i++)
         for(j=0;j<MAX;j++) {
            c[i][j]=g[i][j]=0;
            for(k=0;k<MAX;k++)
               pa[i][j][k]=0;
         }
      for(i=0;i<100;i++)
         gn[i]=0;
      x=0;
      for(i=0;i<n;i++) {
         scanf("%d %d",&j,&k);
         if(j>x) x=j;
         if(k>x) x=k;
         if(j>=MAX || k>=MAX) i=1/0;
         g[j][k]=1;
         gvar[j][gn[j]++]=k;
      }
      x++;
      for(i=0;i<x;i++) cycle[i]=0;
      for(i=0;i<x;i++)
         backtrack(i,0);
      printf("matrix for city %d\n",city++);
      for(j=0;j<x;j++) {
         for(i=0;i<x;i++) {
            cy=0;
            for(k=0;k<x;k++)
               if(pa[j][i][k]==1 && cycle[k]) {
                  c[j][i]=-1;
                  break;
               }
            printf("%d%c",c[j][i],i==x-1?'\n':' ');
         }
      }
   }
}
