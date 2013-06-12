#include <stdio.h>

int g[26][26];
int deg[26];

char s[10000];

int dijkstra(int start,int end)
{
   int i,j;
   int intree[26];
   int distance[26];
   int v,w,weight,dist;

   for(i=0;i<26;i++) {
      intree[i]=0;
      distance[i]=2000000000;
   }

   distance[start]=0;
   v=start;

   while(intree[v]==0) {
      intree[v]=1;
      for(i=0;i<26;i++)
         if(g[i][v]<2000000000) {
            w=i;
            weight=g[i][v];
            if(distance[w]>distance[v]+weight)
               distance[w]=distance[v]+weight;
         }
      v=1;
      dist=2000000000;
      for(i=0;i<26;i++)
         if(intree[i]==0 && dist>distance[i]) {
            dist=distance[i];
            v=i;
         }
   }
   return distance[end];
}

int main()
{
   int l,i,j,odd,tot,odds[2];

   while(1) {
      for(i=0;i<26;i++) {
         for(j=0;j<26;j++)
            g[i][j]=2000000000;
         deg[i]=0;
      }
      while(1) {
         if(gets(s)==NULL) return;
         if(strcmp(s,"deadend")==0) break;
         l=strlen(s);
         g[s[0]-'a'][s[l-1]-'a']=l;
         g[s[l-1]-'a'][s[0]-'a']=l;
         deg[s[l-1]-'a']++;
         deg[s[0]-'a']++;
      }
      odd=0;
      for(i=0;i<26;i++)
         if(deg[i]&1) odds[odd++]=i;
      tot=0;
      for(i=0;i<26;i++)
         for(j=i+1;j<26;j++)
            if(g[i][j]<2000000000) tot+=g[i][j];
      if(odd==2)
         tot+=dijkstra(odds[0],odds[1]);
      printf("%d\n",tot);
   }
}
