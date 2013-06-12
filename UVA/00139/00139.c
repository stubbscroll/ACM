#include <stdio.h>
#define MAXC 100000

struct c_s {
   char c[20];
   int cl;
   char l[30];
   int p;
} c[MAXC];
int nc;

char s[1000000],t[1000000],u[1000000];
int v;

int main()
{
   int i,cost,m,ul;

   nc=0;
   while(1) {
      gets(s);
      sscanf(s,"%s",t);
      if(!strcmp(t,"000000")) break;
      if(nc==MAXC) nc=1/0;
      sscanf(s,"%s %[^$]$%d",c[nc].c,c[nc].l,&c[nc].p);
      c[nc].cl=strlen(c[nc].c);
      nc++;
   }
   while(1) {
      scanf("%s %d",s,&v);
      if(!strcmp(s,"#")) break;
      if(s[0]!='0') {
         strcpy(t,"Local");
         strcpy(u,s);
         cost=0;
         m=0.0;
      } else {
         for(i=0;i<nc;i++)
            if(!strncmp(c[i].c,s,c[i].cl)) {
               strcpy(u,s+c[i].cl);
               ul=strlen(u);
               if(s[1]=='0') {
                  if(ul<4 || ul>10) continue;
               } else {
                  if(ul<4 || ul>7) continue;
               }
               strcpy(t,c[i].l);
               cost=c[i].p;
               m=c[i].p*v;
               goto out;
            }
         strcpy(t,"Unknown");
         strcpy(u,"");
         m=-100;
      }
   out:
      printf("%-16s%-25s%10s%5d",s,t,u,v);
      if(m==-100) printf("      ");
      else printf("%3d.%02d",cost/100,cost%100);
      printf("%4d.%02d\n",m/100,abs(m)%100);
   }
}
