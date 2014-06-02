#include <stdio.h>

int ns,ne;
int s[4000000],e[4000000];
long long sums,sume,s1,e1;

int main()
{
   int n,i,num;

   scanf("%d",&n);
   while(n--) {
      scanf("%d %d",&ns,&ne);
      sums=sume=0;
      for(i=0;i<ns;i++) {
         scanf("%d",&s[i]);
         sums+=s[i];
      }
      for(i=0;i<ne;i++) {
         scanf("%d",&e[i]);
         sume+=e[i];
      }
      for(num=i=0;i<ns;i++) {
         s1=sums-s[i];
         e1=sume+s[i];
         if(ns*s1>(ns-1)*sums && ne*e1>(ne+1)*sume) num++;
     }
      printf("%d\n",num);
   }
}
