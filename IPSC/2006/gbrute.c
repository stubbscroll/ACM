#include <stdio.h>
#define N 100000

char t[N];
int n;

int best,num;

void btr(int pos,int taken)
{
   int i,j,k;

   if(pos==n) {
      if(best==taken) num++;
      else if(best<taken) {
         best=taken;
         num=1;
      }
   }
   for(i=pos;i<n;i++) {
      t[i]=1;
      for(j=0;j<=i;j++) if(t[j]) for(k=0;k<j;k++) if(t[k] && t[k+j+1]) goto failed;
      btr(i+1,taken+1);
   failed:
      t[i]=0;
   }
}

int main()
{
   int i;
   for(i=1;i<N;i++) {
      n=i;
      memset(t,0,N);
      best=num=0;
      btr(0,0);
      printf("%d: %d (%d)\n",i,best,num);
   }
}
