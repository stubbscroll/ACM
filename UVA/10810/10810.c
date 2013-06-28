#include <stdio.h>

int a[500001],b[500001];
int n;
long long ans;
char s[100];

void printlonglong(unsigned long long l,char *st)
{
   unsigned long long m,n;
   int j,i;

   m=1e19;
   n=1e18;
   i=0;
   do {
      j=l%m/n;
      if(j>0)
         break;
      m=n;
      n/=10;
   } while(n>1);
   do {
      j=l%m/n;
      st[i++]=j+48;
      m=n;
      n/=10;
   } while(n);
   st[i]=0;
}

long long mergesort(int l,int r)
{
   int m,t,i,j,k,c,d;
   long long num;

   if(r-l==1) return 0;
   if(r-l==2) {
      if(a[l]>a[r-1]) {
         t=a[l]; a[l]=a[r-1]; a[r-1]=t;
         return 1;
      }
      return 0;
   }
   m=(r+l)/2;
   num=mergesort(l,m);
   num+=mergesort(m,r);
   memcpy(b+l,a+l,(r-l)*sizeof(int));
   i=l; j=l; k=m;
   while(i<r) {
      if(j==m) c=2000000000;
      else c=b[j];
      if(k==r) d=2000000000;
      else d=b[k];
      if(c<d) j++;
      else {
         num+=m-j;
         k++; c=d;
      }
      a[i++]=c;
   }
   return num;
}

int main()
{
   int i;

   while(1) {
      scanf("%d",&n);
      if(n==0) break;
      for(i=0;i<n;i++) scanf("%d",&a[i]);
      ans=mergesort(0,n);
      printlonglong(ans,s);
      printf("%s\n",s);
   }
	 return 0;
}
