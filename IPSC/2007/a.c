#include <stdio.h>

char s[100],t[100],u[100];

int isnum(char *s)
{
   int i;
   for(i=0;s[i];i++) if(!isdigit(s[i])) return 0;
   return 1;
}

int main()
{
   int n,a,b,c;

   scanf("%d",&n);
   while(n--) {
      scanf("%s + %s = %s",s,t,u);
      a=strtol(s,NULL,10);
      b=strtol(t,NULL,10);
      c=strtol(u,NULL,10);
      if(!isnum(s)) printf("%d + %d = %d\n",c-b,b,c);
      else if(!isnum(t)) printf("%d + %d = %d\n",a,c-a,c);
      else if(!isnum(u)) printf("%d + %d = %d\n",a,b,a+b);
   }
}
