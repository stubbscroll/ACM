#include <stdio.h>

char s[10000];
char t[20][10];
int w[20];
int n;

int compint(int *a,int *b)
{
   return (*a>*b)-(*a<*b);
}

int main()
{
   int i,j;
   int min,c,cand1,cand2;

   while(gets(s)!=NULL) {
      n=sscanf(s,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s",t[0],t[1],t[2],t[3],
         t[4],t[5],t[6],t[7],t[8],t[9],t[10],t[11],t[12],t[13]);
      for(i=0;i<n;i++) {
         w[i]=0;
         for(j=0;j<strlen(t[i]);j++)
            w[i]=(w[i] << 5)+t[i][j]-'a'+1;
      }
      qsort(w,n,sizeof(int),compint);
      min=w[0];
      do {
         c=min;
         min=-1;
         for(i=0;i<n-1;i++)
            for(j=i+1;j<n;j++) {
               if((c/w[i])%n==(c/w[j])%n) {
                  cand1=((c/w[i])+1)*w[i];
                  cand2=((c/w[j])+1)*w[j];
                  if(cand1>cand2) cand1=cand2;
                  if(min<cand1) min=cand1;
               }
            }
      } while(min>-1);
      printf("%s\n%d\n\n",s,c);
   }
}
