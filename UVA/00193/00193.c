#include <stdio.h>
#define MAX 101

char g[MAX][MAX];
int gn[MAX];
int t[MAX];
int n;
int best[MAX];
int bestc;

void btrack(int s,int p)
{
   int i,j;

   if(p>bestc) {
      bestc=p;
      for(j=i=0;i<n;i++)
         if(t[i])
            best[j++]=i+1;
   }
   for(i=s;i<n;i++) {
      for(j=0;j<gn[i];j++)
         if(t[g[i][j]]) goto next;
      if(n-i+p<bestc) return;
      t[i]=1;
      btrack(i+1,p+1);
      t[i]=0;
   next:
      ;
   }
}

int main()
{
   int cases,i,j,k,e;

   scanf("%d",&cases);
   while(cases--) {
      scanf("%d %d",&n,&e);
      for(i=0;i<n;i++)
         gn[i]=0;
      for(i=0;i<e;i++) {
         scanf("%d %d",&j,&k);
         j--; k--;
         g[j][gn[j]++]=k;
         g[k][gn[k]++]=j;
      }
      bestc=0;
      for(i=0;i<n;i++) t[i]=0;
      btrack(0,0);
      printf("%d\n%d",bestc,best[0]);
      for(i=1;i<bestc;i++) printf(" %d",best[i]);
      printf("\n");
   }
}
