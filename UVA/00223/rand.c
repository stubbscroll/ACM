#include <stdio.h>

int main()
{
   int i;
   printf("200\n");
   for(i=0;i<50;i++) printf("%d %d %d %d\n",0,i,0,i+1);
   for(i=0;i<50;i++) printf("%d %d %d %d\n",i,50,i+1,50);
   for(i=50;i;i--) printf("%d %d %d %d\n",50,i,50,i-1);
   for(i=50;i;i--) printf("%d %d %d %d\n",i,0,i-1,0);
}
