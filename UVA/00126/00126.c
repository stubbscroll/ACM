#include <stdio.h>

int fa[2][50][3];
int fai[2];
int pr[250][3];

int comp(x1,x2,y1,y2)
{
   if(x1<x2)
      return 1;
   if(x1>x2)
      return 0;
   if(y1>y2)
      return 1;
   return 0;
}

int main()
{
   char s[81],t[100],u1[100],u2[100];
   int i,j,p,l,xy=0;

   gets(s);
   do {
      if(s[0]=='#')
         break;
      for(i=0;i<2;i++) {
         fai[i]=0;
         p=0;
         l=strlen(s);
         do {
            if(p==l) break;
            if(s[p]=='-') {
               fa[i][fai[i]][0]=-1; p++;
            } else if(s[p]=='+') {
               fa[i][fai[i]][0]=1; p++;
            } else 
               fa[i][fai[i]][0]=1;
            fa[i][fai[i]][1]=fa[i][fai[i]][2]=0;
            if(p==l) break;
            if(isdigit(s[p])) {
               fa[i][fai[i]][0]*=strtol(s+p,NULL,10);
               while(isdigit(s[p])) p++;
            }
            if(p==l) {
               fai[i]++; break;
            }
            if(s[p]=='x' || s[p]=='y') {
               xy=s[p]-'w';
               p++;
               fa[i][fai[i]][xy]=1;
               if(p==l) {
                  fai[i]++; break;
               }
               if(isdigit(s[p])) {
                  fa[i][fai[i]][xy]=strtol(s+p,NULL,10);
                  while(isdigit(s[p])) p++;
               }
            }
            if(p==l) {
               fai[i]++; break;
            }
            if(s[p]=='x' || s[p]=='y') {
               xy=s[p]-'w';
               p++;
               fa[i][fai[i]][xy]=1;
               if(p==l) {
                  fai[i]++; break;
               }
               if(isdigit(s[p])) {
                  fa[i][fai[i]][xy]=strtol(s+p,NULL,10);
                  while(isdigit(s[p])) p++;
               }
            }
            fai[i]++;
         } while(1);
         gets(s);
      }
      p=0;
      for(i=0;i<fai[0];i++)
         for(j=0;j<fai[1];j++) {
            pr[p][0]=fa[0][i][0]*fa[1][j][0];
            pr[p][1]=fa[0][i][1]+fa[1][j][1];
            pr[p++][2]=fa[0][i][2]+fa[1][j][2];
         }
      for(i=0;i<p-1;i++)
         for(j=i+1;j<p;j++)
            if(pr[i][1]==pr[j][1] && pr[i][2]==pr[j][2]) {
               pr[i][0]+=pr[j][0];
               pr[j][0]=pr[j][1]=pr[j][2]=0;
            }
      do {
         j=0;
         for(i=0;i<p-1;i++)
            if(comp(pr[i][1],pr[i+1][1],pr[i][2],pr[i+1][2])) {
               l=pr[i][0]; pr[i][0]=pr[i+1][0]; pr[i+1][0]=l;
               l=pr[i][1]; pr[i][1]=pr[i+1][1]; pr[i+1][1]=l;
               l=pr[i][2]; pr[i][2]=pr[i+1][2]; pr[i+1][2]=l; j=1;
            }
      } while(j);
      j=0;
      for(i=0;i<p;i++)
         if(pr[i][0]) {
            pr[j][0]=pr[i][0];
            pr[j][1]=pr[i][1];
            pr[j++][2]=pr[i][2];
         }
      p=j;
      u1[0]=u2[0]=0;
      for(i=0;i<p;i++) {
         if(i==0 && pr[i][0]<0)
            strcat(u1,"-");
         if(abs(pr[i][0])!=1 || (pr[i][1]==0 && pr[i][2]==0)) {
            sprintf(t,"%d",abs(pr[i][0]));
            strcat(u1,t);
         }
         if(pr[i][1])
            strcat(u1,"x");
         if(pr[i][1]>1) {
            for(j=strlen(u2);j<strlen(u1);j++)
               strcat(u2," ");
            sprintf(t,"%d",pr[i][1]);
            strcat(u2,t);
            for(j=strlen(u1);j<strlen(u2);j++)
               strcat(u1," ");
         }
         if(pr[i][2])
            strcat(u1,"y");
         if(pr[i][2]>1) {
            for(j=strlen(u2);j<strlen(u1);j++)
               strcat(u2," ");
            sprintf(t,"%d",pr[i][2]);
            strcat(u2,t);
            for(j=strlen(u1);j<strlen(u2);j++)
               strcat(u1," ");
         }
         if(i<p-1) {
            if(pr[i+1][0]>0)
               strcat(u1," + ");
            else
               strcat(u1," - ");
         }
      }
      while(strlen(u1)<strlen(u2)) strcat(u1," ");
      while(strlen(u2)<strlen(u1)) strcat(u2," ");
      printf("%s\n%s\n",u2,u1);
   } while(1);
}
