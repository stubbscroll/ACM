#include <stdio.h>

int main()
{
   long long i=3,n=0,p=2,s1,s2;
   int i2,p2;

   do {
      s1=(p-1)*p/2;
      s2=(i*(i+1)-(p*(p+1)))/2;
      i2=i;
      p2=p;
      if(s2==s1) {
         printf("%10d%10d\n",p2,i2);
         n++;
      }
      i++;
      if(s2>s1)
         p++;
   } while(n<10);
}
