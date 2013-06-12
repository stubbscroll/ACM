#include <stdio.h>

int main()
{
   char s[100],t;
   int j,k,l,n;

   s[0]=0;
   do {
      gets(s+1);
      if(s[1]=='#')
         break;
      n=strlen(s+1);
      j=n-1;
      while(s[j]>=s[j+1])
         j--;
      if(j==0) {
         printf("No Successor\n");
         continue;
      }
      l=n;
      while(s[j]>=s[l])
         l--;
      t=s[j]; s[j]=s[l]; s[l]=t;
      k=j+1;
      l=n;
      while(k<l) {
         t=s[k]; s[k]=s[l]; s[l]=t;
         k++; l--;
      }
      printf("%s\n",s+1);
   } while(1);
}
