#include <stdio.h>

int main()
{
   int n=0,i=0;
   int j,k;

   do {
      i++;
      k=i;
      while(k%2==0) k/=2;
      while(k%3==0) k/=3;
      while(k%5==0) k/=5;
      if(k==1) n++;
   } while(n<1500);
   printf("The 1500'th ugly number is %d.\n",i); /* 859963392 */
}
