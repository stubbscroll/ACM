#include <stdio.h>

int main()
{
   int hi1,hi2,n1,n2,n,x;
   scanf("%d",&n);
   while(n--) {
      scanf("%d %d",&n1,&n2);
      hi1=hi2=0;
      while(n1--) { scanf("%d",&x); if(hi1<x) hi1=x; }
      while(n2--) { scanf("%d",&x); if(hi2<x) hi2=x; }
      if(hi1>=hi2) puts("Godzilla");
      else puts("MechaGodzilla");
   }
}
