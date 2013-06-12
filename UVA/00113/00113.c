#include <stdio.h>
#include <math.h>

int main()
{
   char s[200];
   int n;
   double pd;

   do {
      if(gets(s)==NULL) break;
      sscanf(s,"%d",&n);
      if(gets(s)==NULL) break;
      sscanf(s,"%lf",&pd);
      printf("%1.0f\n",exp(log(pd)/(double)n));
   } while(1);
}
