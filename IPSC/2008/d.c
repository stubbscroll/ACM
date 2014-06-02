#include <stdio.h>

#define M1 1000000
#define M2 10

int n,m,k;
int c[M1][M2];
int got[M2];

int r;

/* set=1: must be equal at this pos */
void btr(int pos,int mask[M2],int set[M2],int num)
{
   int i,j;
   if(num==m) {
      r++;
      return;
   }
   for(i=pos;i<k;i++) {
      for(j=0;j<n;j++) if(set[j] && c[got[0]][j]!=c[i][j]) goto notok;
      else if(!set[j] && ((1<<c[i][j])&mask[j])>0) goto notok;
      for(j=0;j<n;j++) if(!set[j]) mask[j]+=(1<<c[i][j]);
      got[num]=i;
      btr(i+1,mask,set,num+1);
      for(j=0;j<n;j++) if(!set[j]) mask[j]-=(1<<c[i][j]);
   notok:;
   }
}

void startbtrack(int set[M2]) {
   int i,j;
   int mask[M2];
   for(i=0;i<k;i++) {
      got[0]=i;
      for(j=0;j<n;j++) if(!set[j]) mask[j]=1<<c[i][j];
      else mask[j]=0;
      btr(i,mask,set,1);
   }
}

void generate(int set[M2],int left,int pos)
{
   int i,j;
   for(i=0;i<(1<<n);i++) {
      for(j=0;j<n;j++) if(((1<<j)&i)>0) set[j]=1; else set[j]=0;
   startbtrack(set);
   }
}

int main()
{
   int t,i,j;
   int set[M2];
   scanf("%d",&t);
   while(t--) {
      scanf("%d %d %d",&n,&m,&k);
      for(i=0;i<k;i++) for(j=0;j<n;j++) scanf("%d",&c[i][j]);
      r=0;
      for(i=0;i<n;i++) set[i]=0;
      generate(set,n-m,0);
      printf("%d\n",r);
   }
}
