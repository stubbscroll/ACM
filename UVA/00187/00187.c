#include <stdio.h>

char a[1000][31];
char s[1000];
int tr[1000];
int ta[1000];
int t;

int get3(char *s,int i)
{
   return s[i]*100+s[i+1]*10+s[i+2]-5328;
}

int main()
{
   int i,n,o;

   for(i=0;i<1000;i++) strcpy(a[i],"");
   while(1) {
      gets(s);
      i=get3(s,0);
      if(i==0) break;
      strcpy(a[i],s+3);
   }
   gets(s);
   n=get3(s,0);
   do {
      i=t=0;
      do {
         tr[i]=get3(s,3);
         ta[i]=strtol(s+6,NULL,10);
         t+=ta[i++];
         gets(s);
         o=get3(s,0);
      } while(o==n);
      if(t) {
         printf("*** Transaction %d is out of balance ***\n",n);
         for(n=0;n<i;n++)
            printf("%03d %-30s %10.2f\n",tr[n],a[tr[n]],(double)ta[n]/100);
         printf("999 Out of Balance                 %10.2f\n\n",(double)abs(t)/100);
      }
      n=o;
   } while(n);
}
