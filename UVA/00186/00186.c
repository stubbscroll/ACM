#include <stdio.h>
#define INF 1e9

int f[100][100];        /* floyd-warshall */
int d[100][100];        /* initial distances */
char h[100][100][10];   /* name of highway */

char c[100][50];
int cn;

char s[1000],t[6][100];
int tn[6];
int nt;

void parse()
{
   int sl,i;

   sl=strlen(s); nt=0; tn[nt]=0;
   for(i=0;i<=sl;i++)
      if(s[i]==',' || !s[i]) {
         t[nt][tn[nt]]=0;
         nt++; tn[nt]=0;
      } else t[nt][tn[nt]++]=s[i];
}

int findcity(char *s)
{
   int i;

   for(i=0;i<cn;i++) if(!strcmp(c[i],s)) return i;
   strcpy(c[cn],s);
   return cn++;
}

void printline(int a,int b)
{
   printf("%-21s%-21s%-11s%5d\n",c[a],c[b],h[a][b],d[a][b]);
}

int main()
{
   int i,sl,j,k,l,dist;

   for(i=0;i<100;i++)
      for(j=0;j<100;j++) d[i][j]=INF;
   while(1) {
      gets(s);
      if(!s[0]) break;
      parse();
      i=findcity(t[0]);
      j=findcity(t[1]);
      k=strtol(t[3],NULL,10);
      if(d[i][j]<INF && k>d[i][j]) continue;
      strcpy(h[i][j],t[2]);
      strcpy(h[j][i],t[2]);
      d[i][j]=d[j][i]=k;
   }
   memcpy(f,d,40000);
   for(k=0;k<cn;k++)
      for(i=0;i<cn;i++)
         for(j=0;j<cn;j++)
            if(f[i][j]>f[i][k]+f[k][j])
               f[i][j]=f[i][k]+f[k][j];
   while(gets(s)!=NULL) {
      parse();
      i=findcity(t[0]);
      j=findcity(t[1]);
      printf("\n\n");
      printf("From                 To                   Route      Miles\n");
      printf("-------------------- -------------------- ---------- -----\n");
      k=i; dist=f[i][j];
   more:
      for(l=0;l<cn;l++) {
         if(d[l][j]<INF && f[l][j]==dist) {
            goto out;
         }
         if(d[k][l]<INF && f[k][l]+f[l][j]==dist) {
            dist-=f[k][l];
            printline(k,l);
            k=l;
            goto more;
         }
      }
   out:
      printline(l,j);
      printf("                                                     -----\n");
      printf("                                          Total      %5d\n",f[i][j]);
   }
}
