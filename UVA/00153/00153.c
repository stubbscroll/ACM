#include <stdio.h>

char s[1000000];
int f[256];
int t[256];
int m2[256];
int m3[256];

int compi(int *a,int *b)
{
   return (*a > *b)-(*a < *b);
}

int main()
{
   int i,j,k,l,n,p,q;
   long long o;

   while(1) {
      scanf("%s",s);
      if(s[0]=='#') break;
      l=strlen(s);
      n=1;
      for(i=0;i<l-1;i++) {
         for(j='a';j<='z';j++) t[j]=0;
         for(j=i+1;j<l;j++)
            if(s[i]>s[j] && !t[s[j]]) {
               t[s[j]]=1;
               for(k='a';k<='z';k++) f[k]=0;
               for(k=i;k<l;k++) if(k!=j) f[s[k]]++;
               for(k=0;k<26;k++) m2[k]=f[k+'a'];
               qsort(m2,26,sizeof(int),compi);
               for(k=0;k<26;k++) if(m2[k]==0) m2[k]=1;
               for(k=0;k<26;k++) m3[k]=2;
               q=l-i-1;
               o=1; p=0;
               for(k=0;k<q;k++) {
                  o*=(k+1);
                  for(p=0;p<26;p++)
                     while(m3[p]<=m2[p] && o%m3[p]==0) o/=m3[p]++;
               }
               n+=o;
            }
      }
      printf("%10d\n",n);
   }
}
