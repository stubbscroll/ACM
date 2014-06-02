#include <stdio.h>
#include <math.h>

#define MAXD 1000
#define EPS 1e-14
int t[MAXD],t2[MAXD];
char a[1000],b[1000];

/* multiply a with an integer, works for b<200000000 */
void bigintmuli(char *a,int b,char *r)
{
   int al,i,j;

   al=strlen(a);
   for(i=0;i<al;i++) t[al-i-1]=(a[i]-48)*b;
   for(i=al;i<al+10;i++) t[i]=0;
   for(i=0;i<al+10;i++) if(t[i]>9) {
      t[i+1]+=t[i]/10;
      t[i]%=10;
   }
   i=al+9; while(!t[i] && i) i--;
   for(j=0;j<=i;j++) r[j]=t[i-j]+'0';
   r[j]=0;
}

void bigmod(char *a,int d,char *r)
{
   int l=strlen(a);
   if(l<=d) strcpy(r,a);
   else strcpy(r,a+100-l);
}

int main()
{
   int cases,n,k,l,i;
   double f;
   char z[100],y[100];

   scanf("%d",&cases);
   while(cases--) {
      scanf("%d %d %d",&n,&k,&l);
      strcpy(a,"1");
      f=1;
      for(i=2;i<=n;i++) {
         bigintmuli(a,i,a);
         f+=log10(i);
         while(f>=1) f-=1;
      }
      strcpy(b,a);
      a[k]=0;
      printf("%s %s\n",a,b+strlen(b)-l);
   }
}
