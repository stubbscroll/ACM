#include <stdio.h>
#define MAXV 100
#define INF 1000

int g[MAXV][MAXV];
int a[MAXV+10];
int n;
int distance[MAXV];
char s[1000];

int dijkstra(int start,int block)
{
   int i,j;
   int intree[MAXV];
   int v,w,weight,dist;

   for(i=0;i<n;i++) {
      intree[i]=0;
      distance[i]=INF;
   }
   distance[start]=0;
   v=start;
   while(intree[v]==0) {
      intree[v]=1;
      for(i=0;i<n;i++) {
         if(i==block) continue;
         if(g[i][v]<INF) {
            w=i;
            weight=g[i][v];
            if(distance[w]>distance[v]+weight)
               distance[w]=distance[v]+weight;
         }
      }
      v=0;
      dist=INF;
      for(i=0;i<n;i++) {
         if(i==block) continue;
         if(intree[i]==0 && dist>distance[i]) {
            dist=distance[i];
            v=i;
         }
      }
   }
   for(i=0;i<n;i++)
      if(i!=block && distance[i]==INF) return 0;
   return 1;
}

int main()
{
   int i,j,k,p;

   while(1) {
      gets(s);
      sscanf(s,"%d",&n);
      if(n==0) break;
      for(i=0;i<n;i++)
         for(j=0;j<n;j++)
            g[i][j]=INF;
      while(1) {
         gets(s);
         j=sscanf(s,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d "
            "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d "
            "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d "
            "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d "
            "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ",
            &a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8],&a[9],
            &a[10],&a[11],&a[12],&a[13],&a[14],&a[15],&a[16],&a[17],&a[18],&a[19],
            &a[20],&a[21],&a[22],&a[23],&a[24],&a[25],&a[26],&a[27],&a[28],&a[29],
            &a[30],&a[31],&a[32],&a[33],&a[34],&a[35],&a[36],&a[37],&a[38],&a[39],
            &a[40],&a[41],&a[42],&a[43],&a[44],&a[45],&a[46],&a[47],&a[48],&a[49],
            &a[50],&a[51],&a[52],&a[53],&a[54],&a[55],&a[56],&a[57],&a[58],&a[59],
            &a[60],&a[61],&a[62],&a[63],&a[64],&a[65],&a[66],&a[67],&a[68],&a[69],
            &a[70],&a[71],&a[72],&a[73],&a[74],&a[75],&a[76],&a[77],&a[78],&a[79],
            &a[80],&a[81],&a[82],&a[83],&a[84],&a[85],&a[86],&a[87],&a[88],&a[89],
            &a[90],&a[91],&a[92],&a[93],&a[94],&a[95],&a[96],&a[97],&a[98],&a[99]);
         if(a[0]==0) break;
         for(i=1;i<j;i++) g[a[0]-1][a[i]-1]=g[a[i]-1][a[0]-1]=0;
      }
      p=0;
      for(i=0;i<n;i++) {
         for(j=0;j<n;j++)
            if(i!=j &&!dijkstra(j,i)) {
               p++; break;
            }
      }
      printf("%d\n",p);
   }
}
