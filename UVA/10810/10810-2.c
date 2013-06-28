#include <stdio.h>
#include <stdlib.h>

int n;
int a[500000];
int b[500000];

long long mergesort(int l,int r)
{
   long long num;
   int m,i,j,k,c,d,t;

   if(r-l==0) return 0;
   else if(r-l==1) return 0;
   else if(r-l==2) {
      if(a[l]>a[l+1]) {
         t=a[l]; a[l]=a[l+1]; a[l+1]=t;
         return 1;
      }
      return 0;
   } else if(r-l>2) {
      m=(l+r)/2;
      num=mergesort(l,m);
      num+=mergesort(m,r);
      memcpy(b+l,a+l,(r-l)*sizeof(int));
      i=l; j=l; k=m;
      while(i<r) {
         if(j==m) c=2e9;
         else c=b[j];
         if(k==r) d=2e9;
         else d=b[k];
         if(c<=d) j++;
         else {
            num+=m-j;
            k++; c=d;
         }
         a[i++]=c;
      }
   }
   return num;
}

void printlonglong(long long l)
{
   long long m,n;
   int j,i;
   m=1e19;
   n=1e18;
   i=0;
   do {
      j=l%m/n;
      if(j>0) break;
      m=n;
      n/=10;
   } while(n>1);
   do {
      j=l%m/n;
      putchar(j+48);
      m=n;
      n/=10;
   } while(n);
}

int main()
{
   int i;
   long long ans;

   while(scanf("%d",&n),n) {
      for(i=0;i<n;i++) scanf("%d",&a[i]);
      ans=mergesort(0,n);
      printlonglong(ans);
      putchar('\n');
   }
	 return 0;
}
