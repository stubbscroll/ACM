#include <stdio.h>

int a[32768],n;

int compi(int *a,int *b)
{
   return (*a>*b)-(*a<*b);
}

void btr5(int v)
{
   if(v<429496730) {
      a[n++]=v*5;
      btr5(v*5);
   }
}

void btr3(int v)
{
   if(v<715827883) {
      a[n++]=v*3;
      btr3(v*3);
   }
   btr5(v);
}

void btr2(int v)
{
   if(v<(1<<30)) {
      a[n++]=v<<1;
      btr2(v<<1);
   }
   btr3(v);
}

int main()
{
   a[0]=n=1;
   btr2(1);
   qsort(a,n,sizeof(a[0]),compi);
   printf("The 1500'th ugly number is %d.\n",a[1499]); /* 859963392 */
}
