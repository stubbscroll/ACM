#include <stdio.h>
#include <string.h>
#define MAXW 2001

char w[MAXW][21];
int  wl[MAXW];
int  wn;

char s[200];
int sl,sl2;
char t[10][21];
int tl;
int f[256];
int block[10];
int bn;

int bf[256];
int ws[10];

void btrack(int n,int o,int l)
{
   int i,j;

   if(l==sl2) {
      printf("%s =",s);
      for(i=0;i<n;i++)
         printf(" %s",w[ws[i]]);
      printf("\n");
      return;
   }
   for(i=o;i<wn;i++) {
      if(l+wl[i]>sl2) goto next;
      for(j=0;j<bn;j++)
         if(i==block[j]) goto next;
      for(j=0;j<wl[i];j++)
         bf[w[i][j]]++;
      for(j='A';j<='Z';j++)
         if(bf[j]>f[j]) goto decfreq;
      ws[n]=i;
      btrack(n+1,i,l+wl[i]);
   decfreq:
      for(j=0;j<wl[i];j++)
         bf[w[i][j]]--;      
   next:
      ;
   }
}

int main()
{
   int i;
   char *bs;

   wn=0;
   while(1) {
      gets(w[wn]);
      if(w[wn][0]=='#') break;
      if(wn==MAXW) i=1/0;
      wl[wn]=strlen(w[wn]);
      wn++;
   }
   while(1) {
      gets(s);
      if(s[0]=='#') break;
      sl=strlen(s);
      for(i='A';i<='Z';i++) bf[i]=f[i]=0;
      for(i=sl2=0;i<sl;i++) {
         f[s[i]]++;
         if(s[i]!=' ') sl2++;
      }
      tl=sscanf(s,"%s %s %s %s %s %s %s %s %s %s",t[0],t[1],t[2],t[3],t[4],t[5]
         ,t[6],t[7],t[8],t[9]);
      bn=0;
      for(i=0;i<tl;i++) {
         bs=(char *)bsearch(t[i],w,wn,21,strcmp);
         if(bs!=NULL) block[bn++]=(bs-&w[0][0])/21;
      }
      btrack(0,0,0);
   }
}
