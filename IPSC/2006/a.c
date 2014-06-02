#include <stdio.h>

#define MAXD 1000
int t[MAXD],t2[MAXD];
int n;
char a[1000],b[1000];

void bigintadd(char *a,char *b,char *c)
{
   int a1,a2,p,q,i;

   a1=strlen(a)-1;
   a2=strlen(b)-1;
   if(a1<a2) p=a2; else p=a1;
   for(i=0;i<=p+1;i++) t[i]=0;
   p=0;
   do {
      if(a1<0 && a2<0) break;
      q=0;
      if(a1>=0) q=a[a1]-'0';
      if(a2>=0) q+=b[a2]-'0';
      t[p++]+=q;
      a1--; a2--;
   } while(1);
   for(i=0;i<p;i++)
      if(t[i]>9) {
         t[i]-=10;
         t[i+1]++;
         if(i==p-1) p++;
      }
   for(i=0;i<p;i++)
      c[p-i-1]=t[i]+'0';
   c[p]=0;
}

/* divide a with an integer, works bad if d>600000000,
   change to long long to get bigger numbers */
void bigintdivi(char *a,int d,char *b)
{
   int al,i,carry,x;

   al=strlen(a);
   b[al]=0;
   carry=0;
   for(i=0;i<al;i++) {
      x=a[i]-'0';
      b[i]=(x+carry)/d+'0';
      carry=(x+carry)%d*10;
   }
   x=0;
   while(b[x]=='0') x++;
   if(x==al) x-=1;
   if(x)
      for(i=x;i<=al;i++)
         b[i-x]=b[i];   
}

int bigintmodi(char *a,int d)
{
   int res=0,i;
   for(i=0;a[i];i++) res=(res*10+a[i]-'0')%d;
   return res;
}

int main()
{
   int cases,i;

   scanf("%d",&cases);
   while(cases--) {
      strcpy(a,"0");
      scanf("%d",&n);
      for(i=0;i<n;i++) {
         scanf("%s",b);
         bigintadd(a,b,a);
      }
      puts(bigintmodi(a,n)==0?"YES":"NO");
   }
}
