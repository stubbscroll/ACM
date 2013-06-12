#include <stdio.h>

const int max[10]={0,1,3,7,15,31,63,127,255,511};

char k[300];
char s[300],t[10];
int sl;
int si;

char getdigit()
{
   while(s[si]==0) {
      gets(s);
      sl=strlen(s); si=0;
   }
   return s[si++];
}

int getdigits(int n)
{
   int i,num;

   for(num=i=0;i<n;i++) num=num*2+getdigit()-'0';
   return num;
}

char calc(int b,int num)
{
   int i,j;

   for(i=j=0;i<b;i++) j+=max[i];
   return k[j+num];
}

int main()
{
   int i,n;

   while(1) {
      if(gets(k)==NULL) break;
      s[0]=0; si=0;
      while(n=getdigits(3)) while((i=getdigits(n))!=max[n]) printf("%c",calc(n,i));
      printf("\n");
   }
}
