#include <stdio.h>
#define MAXM 1000

const int mx[10]={1,7,12,28,32,29,18,8};
int a[15];
int v[15];
int tr[15];
int mem[100][100];
char made[MAXM];

void printtr(int k)
{
   int i;
   for(i=0;i<k;i++) printf("%d ",tr[i]);
}

void printv(int k)
{
   int i;
   for(i=0;i<k;i++) printf("%d ",v[i]);
}

/* stamp function n(h,k)
 * h: number of stamps that may be attached to a document
 * k: number of denominations of stamps available
 * a[]: array of stamp denominations
 * n (return value): maximum value such that all 1..n can be made from a[] */
int n(int h,int k,int *a)
{
   int i,j,max,val,maxw,l;

   if(h==0) return 0;
   if(h==1) {
      for(i=1;i<k;i++) a[i]=i+1;
      return k;
   }
   if(k==1) return h;
   if(mem[h][k]) return mem[h][k];
   max=0;
   maxw=h*3+5;
   for(i=1;i<k;i++) v[i]=i+1;
   while(1) {
      memset(made,0,MAXM);
      for(l=1;l<=h;l++) {
         for(i=0;i<k;i++) tr[i]=0;
         tr[k-1]=l;
         while(1) {
            val=0;
            for(i=0;i<k;i++) val+=tr[i]*v[i];
            if(val<MAXM) made[val]=1;
            i=k-1;
            if(tr[i]) {
               tr[i]--; tr[i-1]++;
               goto next;
            }
            while(tr[i]==0 && i>0) i--;
            if(i==0) break;
            tr[i-1]++;
            for(j=i;j<k;j++) tr[i]=0;
            val=0;
            for(j=0;j<k;j++) val+=tr[j];
            tr[k-1]=l-val;
         next:
            ;
         }
      }
      i=1;
      while(i<1000 && made[i]) i++;
      i--;
      if(i>=max) {
         max=i;
         for(i=0;i<k;i++) a[i]=v[i];
      }
      i=k-1;
      while(1) {
         v[i]++;
         if(v[i]>mx[i]) {
            i--;
            if(i==0) goto out;
         } else break;
      }
      for(j=i+1;j<k;j++) v[j]=v[j-1]+1;
   }
out:
   mem[h][k]=max;
   return max;
}

int main()
{
   int h,k,val,i;

   memset(mem,0,40000);
   a[0]=v[0]=1;
   while(1) {
      scanf("%d %d",&h,&k);
      if(h==0 && k==0) break;
      val=n(h,k,a);
      for(i=0;i<k;i++) printf("%3d",a[i]);
      printf(" ->%3d\n",val);
   }
}
