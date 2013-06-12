#include <stdio.h>

char s[1000],t[1000],u[1000];
int f[256];
int e[256];
int p[100];
char p1[100][100];
char p2[100][100];

int main()
{
   int i,j,k,l,m,sl,sl2,done,taken;

   memset(e,0,256*sizeof(int));
   while(1) {
      memset(s,0,1000);
      gets(s);
      if(s[0]=='#' && !s[1]) break;
      memset(t,0,1000);
      gets(t); gets(u);
      if(!strcmp(s,t)) {
         printf("%s\n",u);
         continue;
      }
      sl=strlen(s);
      for(i=2;i<=sl;i++) {
         sl2=((sl+i-1)/i)*i;
         for(j=0;j<sl2;j+=i) {
            memset(f,0,256*sizeof(int));
            for(k=0;k<i;k++) {
               f[s[j+k]]++; f[t[j+k]]--;
            }
            if(memcmp(f,e,256*sizeof(int))) break;
         }
         if(j==sl2) {
            /* find a permutation */
            /* initialize all to on */
            for(j=0;j<i;j++) memset(p1[j],1,i);
            for(j=0;j<i;j++) p[j]=-1;
            for(j=0;j<sl2;j+=i) {
               for(k=0;k<i;k++) memset(p2[k],0,i);
               for(k=0;k<i;k++)
                  for(l=0;l<i;l++) {
                     if(s[j+k]==t[j+l]) {
                        p2[k][l]=1;
                     }
                  }
               /* mask */
               for(k=0;k<i;k++)
                  for(l=0;l<i;l++)
                     p1[k][l]&=p2[k][l];
            }
            /* create permutation table */
            taken=0;
            do {
               done=1;
               /* loop through each char */
               for(j=0;j<i;j++) {
                  /* check for unique mapping */
                  l=0; m=-1;
                  for(k=0;k<i;k++)
                     if(p1[j][k]) {
                        l++; m=k;
                     }
                  if(l==1) {
                     done=0;
                     taken++;
                     p[j]=m;
                     /* remove destionation character */
                     for(k=0;k<i;k++) p1[j][k]=0;
                  }
               }
            } while(!done);
            if(taken==i) break;
         }
      }
      if(i==sl+1) {
         printf("%s\n",u);
         continue;
      }
      sl=strlen(u);
      sl2=sl/i;
      if(sl%i) sl2++;
      sl2*=i;
      for(j=sl;j<sl2;j++) u[j]='?';
      u[j]=0;
      for(j=0;j<sl2;j+=i)
         for(k=0;k<i;k++)
            printf("%c",u[j+p[k]]);
      printf("\n");
   }
}
