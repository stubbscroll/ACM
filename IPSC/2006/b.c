#include <stdio.h>

int n;

typedef struct {
   int pl;
   char s[100];
} e;

e g[500000];

int compe(e *a,e *b)
{
   return (a->pl>b->pl)-(a->pl<b->pl);
}

void printlonglong(unsigned long long l,char *s)
{
   unsigned long long m=1e19,n=1e18;
   int j,i=0;

   do {
      j=l%m/n;
      if(j>0) break;
      m=n;
      n/=10;
   } while(n>1);
   do {
      j=l%m/n;
      s[i++]=j+48;
      m=n;
      n/=10;
   } while(n);
   s[i]=0;
}

char s[100];

int main()
{
   int cases,i;
   long long z;
   scanf("%d",&cases);
   while(cases--) {
      scanf("%d",&n);
      for(i=0;i<n;i++) scanf("%s %d",g[i].s,&g[i].pl);
      qsort(g,n,sizeof(e),compe);
      z=0;
      for(i=0;i<n;i++) z+=abs(i+1-g[i].pl);
      printlonglong(z,s);
      puts(s);
   }
}
