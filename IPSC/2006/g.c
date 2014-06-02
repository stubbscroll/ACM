#include <stdio.h>

int main()
{
   int cases,i;
   scanf("%d",&cases);
   while(cases--) {
      scanf("%d",&i);
      if(i==1) puts("1");
      else if(i==2) puts("2");
      else printf("%d\n",(i+2)/2);
   }
}
