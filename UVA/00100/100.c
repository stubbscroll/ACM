#include <stdio.h>
#define M 1000001

int z[M];

int main()
{
   int a,b,c,d,i,x,y;

   memset(z,0,sizeof(z));
   z[1]=1;
   while(scanf("%d %d",&a,&b)==2) {
      if(a<b) c=a,d=b;
      else c=b,d=a;
      for(i=0;c<=d;c++) {
         if(!z[c]) {
            x=c; y=1;
            while(1) {
               if(x&1) x=x*3+1;
               else x>>=1;
               if(x<M && z[x]) break;
               y++;
            }
            z[c]=y+z[x];
         }
         if(i<z[c]) i=z[c];
      }
      printf("%d %d %d\n",a,b,i);
   }
}
