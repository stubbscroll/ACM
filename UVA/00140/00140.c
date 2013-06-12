#include <stdio.h>

int g[26][26];
int gg[26];

char s[100];
char h[10];
int nodes;

int best;
char bests[10];

int compchar (char *a,char *b)
{
  return (*a>*b)-(*a<*b);
}

void visit(char *s)
{
   int i,j,k,b;

   /* check if there is a better bandwidth */
   b=1;
   for(i=2;i<nodes;i++)
      for(j=0;j<nodes-i;j++)
         if(g[s[j]-'A'][s[j+i]-'A'] && i>b)
            b=i;
   if(b<best) {
      best=b;
      strcpy(bests,s);
   }
}

void permute(char *s,void (*visit)(char *s))
{
   int n,l,j,k;
   char a[100]={0},t;

   strcpy(a+1,s);
   n=strlen(a+1);
   qsort(a+1,n,1,compchar);
   do {
      visit(a+1);
      if(best==1) break;
      j=n-1;
      while(a[j]>=a[j+1]) j--;
      if(j==0) break;
      l=n;
      while(a[j]>=a[l]) l--;
      t=a[j]; a[j]=a[l]; a[l]=t;
      k=j+1; l=n;
      while(k<l) {
         t=a[k]; a[k]=a[l]; a[l]=t;
         k++; l--;
      }
   } while(1);
}

int main()
{
   int i,j,k,l;

   while(1) {
      gets(s);
      if(s[0]=='#') break;
      for(i=0;i<26;i++) {
         for(j=0;j<26;j++)
            g[i][j]=0;
         gg[i]=0;
      }
      i=0; l=strlen(s);
      while(i<l) {
         j=s[i]-'A';
         if(s[i+1]!=':') i=1/0;
         i+=2;
         while(isalpha(s[i])) {
            k=s[i++]-'A';
            g[j][k]=g[k][j]=1;
            gg[j]=gg[k]=1;
         }
         if(s[i]==';') i++;
      }
      nodes=0;
      for(i=0;i<26;i++)
         if(gg[i]) h[nodes++]=i+'A';
      h[i]=0;
      best=nodes;
      permute(h,visit);
      for(i=0;i<nodes;i++) printf("%c ",bests[i]);
      printf("-> %d\n",best);
   }
}
