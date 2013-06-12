#include <stdio.h>

int coins[11]={2000,1000,400,200,100,40,20,10,4,2,1};
long long ways[6001];
char num[20];

void printlonglong(long long l)
{
   long long m,n;
   int j;
   int p;

   p=0;
   m=1e19;
   n=1e18;
   do {
      j=l%m/n;
      if(j>0)
         break;
      m=n;
      n/=10;
   } while(n>1);
   do {
      j=l%m/n;
      num[p++]=j+48;
      m=n;
      n/=10;
   } while(n);
   num[p]=0;
}

int main()
{
   char s[100];
   int i,j,c;

   for(i=1;i<=6000;i++)
      ways[i]=0;
   ways[0]=1;
   for(i=0;i<11;i++) {
      c=coins[i];
      for(j=c;j<=6000;j++)
         ways[j]+=ways[j-c];
   }
   do {
      if(gets(s)==NULL) break;
      i=0;
      if(s[0]=='.')
         sscanf(s,".%d",&j);
      else
         sscanf(s,"%d.%d",&i,&j);
      c=(i*100+j)/5;
      if(c==0) break;
      printf("%3d.%02d",c*5/100,c*5%100);
      printlonglong(ways[c]);
      for(i=0;i<17-strlen(num);i++)
         printf(" ");
      printf("%s\n",num);
   } while(1);
}
