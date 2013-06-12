#include <stdio.h>

int r1[1000001];
int r2[1000001];
int s[500001];

int main()
{
   int i,j,k,l,m;

   r1[1]=0; r2[1]=0;
   for(i=2;i<=1000000;i++) {
      r1[i]=(r1[i-1]+15)%i;
      r2[i]=(i-r1[i])%i;
   }
   while(1) {
      scanf("%d %d",&i,&j);
      if(i==0 && j==0) break;
      if(i>j) {
         k=i; i=j; j=k;
      }
      m=l=i/2;
      memset(s,0,(l+1)*sizeof(int));
      s[0]=1;
      for(k=i;k<=j;k++) {
         if(r1[k]<=l && !s[r1[k]]) {
            m--; s[r1[k]]=1;
         }
         if(r2[k]<=l && !s[r2[k]]) {
            m--; s[r2[k]]=1;
         }
      }
      for(k=1;k<=l;k++) if(!s[k]) break;
      if(k<=l) printf("%d\n",k);
      else printf("Better estimate needed\n");
   }
}
