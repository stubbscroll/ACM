#include <stdio.h>

long long dp[1000001][48];
int n,s[1000001];
char t[1000];

void printlonglong(unsigned long long l,char *s)
{
   unsigned long long m=1e19,n=1e18;
   int j,i=0;

   do {
      j=l%m/n;
      if(j>0) break;
      m=n;
      n/=10;
   } while(n>1);
   do {
      j=l%m/n;
      s[i++]=j+48;
      m=n;
      n/=10;
   } while(n);
   s[i]=0;
}

int main()
{
   int cases,i,j,k;
   long long ans;


   scanf("%d",&cases);
   while(cases--) {
      ans=0;
      scanf("%d",&n);
      for(i=0;i<n;i++) scanf("%d",&s[i]);
      memset(dp,0,sizeof(dp));      
      for(i=0;i<n;i++) if(s[i]<48) {
         k=s[i];
         dp[i][k]=1;
         if(i) for(j=0;j<48;j++) if(dp[i-1][j] && j+k<48) {
            dp[i][j+k]+=dp[i-1][j];
         }
         ans+=dp[i][47];
      }
      printlonglong(ans,t);
      puts(t);
   }
}
