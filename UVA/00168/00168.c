#include <stdio.h>
#define MAX 27
#define MAX2 729

char g[MAX][MAX];
int gn[MAX];
int lit[MAX];

char s[1000],t[10],u[10];

int main()
{
   int i,j,k,sl,steps;
   int the,min;

   while(1) {
      gets(s);
      if(s[0]=='#') break;
      memset(g,0,MAX2);
      for(i=0;i<MAX;i++) gn[i]=0;
      sl=strlen(s);
      i=0;
      while(1) {
         j=s[i]-'A';
         if(j<0 || j>=26) i=1/0;
         i+=2;
         while(isalpha(s[i])) {
            if(s[i]<'A' || s[i]>'Z') i=1/0;
            k=s[i++]-'A';
            g[j][gn[j]++]=k;
         }
         if(s[i]=='.') break;
         if(s[i]!=';') i=1/0;
         i++;
      }
      i++;
      sscanf(s+i,"%s %s %d",t,u,&k);
      min=t[0]-'A'; the=u[0]-'A';
      if(min<0 || min>=26) i=1/0;
      if(the<0 || the>=26) i=1/0;
      steps=0;
      for(i=0;i<MAX;i++) lit[i]=0;
      while(1) {
         if(steps%k==0 && steps>0) {
            lit[the]=1;
            printf("%c ",the+'A');
         }
         steps++;
         /* move minotaur */
         for(i=0;i<gn[min];i++) {
            if(lit[g[min][i]]) continue;
            if(g[min][i]==the) continue;
            break;
         }
         the=min;
         if(i==gn[min]) break;
         min=g[min][i];
      }
      printf("/%c\n",min+'A');
   }
}
