#include <stdio.h>
#define H 10000000
#define MAXWP 100
#define MAXP 51
#define MAXWT 250
#define MAXT 251

char h[H];
int hp=0;

int p[MAXP][MAXWP];   /* words in profiles */
int pn[MAXP];         /* number of words in each profile */
int pm[MAXP];         /* maximum distance between words */
int np=0;             /* number of profiles */
int t[MAXT][MAXWT];   /* words in titles */
int tn[MAXT];         /* number of words in each title */
int nt=0;             /* number of titles */

int on[MAXT];

char s[1000000];
char u[10000];

int main()
{
   int ul,sl,starthp,first;
   int i,j,k,l,min,m,n;

   while(1) {
      gets(u);
      if(u[0]=='T' && u[1]==':') break;
      sscanf(u,"P: %d%n",&pm[np],&i);
      ul=strlen(u);
      pn[np]=0;
      while(i<ul) {
         while(!isalpha(u[i]) && u[i]) i++;
         starthp=hp;
         while(u[i]!=' ' && u[i]) {
            if(!isalpha(u[i])) {
               i++; continue;
            }
            h[hp++]=tolower(u[i++]);
         }
         if(hp!=starthp) {
            h[hp++]=0;
            p[np][pn[np]++]=starthp;
         }
      }
      np++;
   }
   do {
      ul=strlen(u);
      i=3;
      tn[nt]=0;
   back:
      while(i<ul) {
         while(!isalpha(u[i]) && u[i]) i++;
         starthp=hp;
         while(u[i]!=' ' && u[i]) {
            if(!isalpha(u[i])) {
               i++; continue;
            }
            h[hp++]=tolower(u[i++]);
         }
         if(hp!=starthp) {
            h[hp++]=0;
            t[nt][tn[nt]++]=starthp;
         }
      }
      i=ul-1;
      while(u[i]==' ' && i>=0) i--;
      if(u[i]=='|') goto next;
      gets(u);
      i=0;
      ul=strlen(u);
      while(i<ul && u[i]==' ') i++;
      goto back;
   next:
      nt++;
      gets(u);
   } while(u[0]!='#');
   for(i=0;i<np;i++) {
      printf("%d:",i+1);
      first=1;
      for(j=0;j<nt;j++) on[j]=0;
      for(j=0;j<nt;j++) {
         for(k=0;k<tn[j]-1;k++) {
            min=k+2+pm[i];
            if(min>tn[j]) min=tn[j];
            for(l=k+1;l<min;l++) {
               for(m=0;m<pn[i];m++)
                  for(n=0;n<pn[i];n++)
                     if(n!=m)
                        if(!strcmp(h+p[i][m],h+t[j][k]) && !strcmp(h+p[i][n],h+t[j][l]))
                           on[j]=1;
            }
         }
      }
      for(j=0;j<nt;j++)
         if(on[j]) {
            if(!first) printf(",");
            else {
               printf(" ");
               first=0;
            }
            printf("%d",j+1);
         }
      if(first) putchar(' ');
      printf("\n");
   }
}
