#include <stdio.h>
#define MAX 1000

char g[MAX][MAX];
char type[MAX];
int delay[MAX];
char t[MAX];
int n;
int clock,best;
char s[100];

int btrack(int v,int cur,int p)
{
   int i;

   if(type[v]=='o' || (type[v]=='i' && p)) {
      if(cur>best) best=cur;
      return 0;
   }
   if(t[v] && type[v]=='a') {
      best=-1;
      return 1;
   } else if(t[v]) return 0;
   t[v]=1;
   for(i=0;i<n;i++)
      if(g[v][i]) if(btrack(i,cur+delay[i],p+1)==1) return 1;
   t[v]=0;
   return 0;
}

int main()
{
   int cases,i,j,k;
   char c;

   scanf("%d",&cases);
   while(cases--) {
      scanf("%d %d",&clock,&n);
      if(n>=MAX) i=1/0;
      for(i=0;i<n;i++) {
         scanf("%s %d",s,&delay[i]);
         type[i]=s[0];
      }
      for(i=0;i<n;i++) memset(g[i],0,n);
      scanf("%d",&i);
      while(i--) {
         scanf("%d %d",&j,&k);
         g[j][k]=1;
      }
      memset(t,0,n);
      best=0;
      for(i=0;i<n;i++)
         if(type[i]=='i')
            if(btrack(i,0,0)==1) break;
      if(best==-1) printf("Circuit contains cycle.\n");
      else if(best>clock) printf("Clock period exceeded.\n");
      else printf("Synchronous design. Maximum delay: %d.\n",best);
   }
}
