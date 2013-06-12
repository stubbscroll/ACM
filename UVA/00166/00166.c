#include <stdio.h>

const int z[6]={5,10,20,50,100,200};
int v[6];
int goal;

int main()
{
   int i,j,k,l,m,n,s,max,r,c,o;

   while(1) {
      for(s=i=0;i<6;i++) {
         scanf("%d",&v[i]);
         s+=v[i];
      }
      if(s==0) break;
      scanf("%d.%d",&i,&s);
      goal=i*100+s;
      max=9999;
      for(i=0;i<=v[5];i++) {
         if(i>max) continue;
         for(j=0;j<=v[4];j++) {
            if(i+j>max) continue;
            for(k=0;k<=v[3];k++) {
               if(i+j+k>max) continue;
               for(l=0;l<=v[2];l++) {
                  if(i+j+k+l>max) continue;
                  for(m=0;m<=v[1];m++) {
                     if(i+j+k+l+m>max) continue;
                     for(n=0;n<=v[0];n++) {
                        if(i+j+k+l+m+n>max) break;
                        s=i*z[5]+j*z[4]+k*z[3]+l*z[2]+m*z[1]+n*z[0];
                        if(s<goal) continue;
                        r=s-goal;
                        c=0;
                        for(o=5;o>=0;o--)
                           while(r>=z[o]) {
                              r-=z[o]; c++;
                           }
                        c+=i+j+k+l+m+n;
                        if(c<max) max=c;
                     }
                  }
               }
            }
         }
      }
      printf("%3d\n",max);
   }
}
