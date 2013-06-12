#include <stdio.h>

#define MAXV 26
#define INF 2000000000

int g[MAXV][MAXV];  /* weighted adjacency matrix, INF: no edge */
int distance[MAXV][MAXV];
int e;
int num;
int path[MAXV];
int taken[MAXV];
int maxv;

void btrack(int start,int p)
{
   int i,j;

   if(start==e) {
      printf("1");
      for(i=0;i<p;i++) printf(" %d",path[i]+1);
      printf("\n");
      num++;
      return;
   }
   for(i=1;i<maxv;i++) {
      /* for all available street corners, check if there is a route from start
       * via i to end */
      if(taken[i] || g[start][i]==INF) continue;
      for(j=1;j<maxv;j++)
         if(!taken[j] && distance[start][i]<INF && distance[i][e]<INF)
            goto goon;
      continue;
   goon:
/*      if(distance[i][e]==INF) continue;*/
      taken[i]=1;
      path[p]=i;
      btrack(i,p+1);
      taken[i]=0;
   }
}

int dijkstra(int start)
{
   int i,j;
   int intree[maxv];
   int v,w,weight,dist;

   for(i=0;i<maxv;i++) {
      intree[i]=0;
      distance[start][i]=INF;
   }

   distance[start][start]=0;
   v=start;

   while(intree[v]==0) {
      intree[v]=1;
      for(i=0;i<maxv;i++)
         if(g[i][v]<INF) {
            w=i;
            weight=g[i][v];
            if(distance[start][w]>distance[start][v]+weight)
               distance[start][w]=distance[start][v]+weight;
         }
      v=0;
      dist=INF;
      for(i=0;i<maxv;i++)
         if(intree[i]==0 && dist>distance[start][i]) {
            dist=distance[start][i];
            v=i;
         }
   }
}

int main()
{
   int i,j,cases=1;

   while(1) {
      if(scanf("%d",&e)!=1) break;
      e--;
      for(i=0;i<MAXV;i++)
         for(j=0;j<MAXV;j++)
            g[i][j]=INF;
      maxv=0;
      while(1) {
         scanf("%d %d",&i,&j);
         if(i==0 && j==0) break;
         if(i>maxv) maxv=i;
         if(j>maxv) maxv=j;
         i--; j--;
         g[i][j]=1; g[j][i]=1;
      }
      printf("CASE %d:\n",cases++);
      num=0;
      for(i=0;i<maxv;i++) taken[i]=0;
      for(i=0;i<maxv;i++) dijkstra(i);
      taken[0]=1;
      btrack(0,0);
      printf("There are %d routes from the firestation to streetcorner %d.\n",num,e+1);
   }
}
