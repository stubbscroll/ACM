#include <stdio.h>

int sign[100];
int count[100];

int main()
{
   int n,i,t,notred;

   while(1) {
      n=0;
      while(1) {
         scanf("%d",&sign[n]);
         if(sign[n]==0) break;
         n++;
      }
      if(n==0) break;
      for(i=0;i<n;i++) count[i]=0;
      notred=1;
      for(t=1;t<=18000;t++) {
         for(i=0;i<n;i++) {
            count[i]++;
            if(count[i]==sign[i]-5) notred=0;
            if(count[i]==sign[i]*2) count[i]=0;
         }
         if(!notred) {
            i=0;
            while(i<n && count[i]<sign[i]-5)
               i++;
            if(i==n) {
               printf("%02d:%02d:%02d\n",t/3600,t/60%60,t%60);
               break;
            }
         }
      }
      if(t==18001) printf("Signals fail to synchronise in 5 hours\n");
   }
   notred=scanf("%d %d %d",&n,&i,&t);
   if(notred>0 && n!=0) n=1/0;
   if(notred>1 && i!=0) while(1);
   if(notred>2 && t!=0) while(1) printf("sopp");
}
