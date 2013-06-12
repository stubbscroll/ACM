#include <stdio.h>

const char crd[15]="  23456789TJQKA";

struct c_s {
   int v;
   char s;
} d[52],plr[5][10],pld[5]; /* plr[4]=dealer */

char trump,curs;
int pl;
char s[100];
int score[5];

int card(char c)
{
   if(c>='2' && c<='9') return c-'0';
   else if(c=='T') return 10;
   else if(c=='J') return 11;
   else if(c=='Q') return 12;
   else if(c=='K') return 13;
   else if(c=='A') return 14;
}

int higher(struct c_s *a,struct c_s *b)
{
   if(a->v > b->v) return -1;
   if(a->v < b->v) return 1;
   return (a->s < b->s)-(a->s > b->s);
}

int main()
{
   int i,j,k,max,bestp,bestv;
   char bests;

   while(1) {
      for(i=0;i<4;i++) {
         gets(s);
         if(s[0]=='#' && i==0) return;
         for(j=0;j<13;j++) {
            d[j+i*13].v=card(s[j*3]);
            d[j+i*13].s=s[j*3+1];
         }
      }
      if(higher(&d[50],&d[51])==-1) trump=d[50].s;
      else trump=d[51].s;
      for(i=0;i<50;i++) plr[i%5][i/5]=d[i];
      for(i=0;i<5;i++) score[i]=0;
      pl=0;
/*      printf("P1  P2  P3  P4  P5\n");*/
      for(i=0;i<10;i++) {
         max=0;
         for(j=1;j<10;j++)
            if(higher(&plr[pl][j],&plr[pl][max])==-1) max=j;
         pld[pl]=plr[pl][max]; curs=pld[pl].s; plr[pl][max].s=0; plr[pl][max].v=0;
         for(j=0;j<5;j++) {
            if(j==pl) continue;
            /* first, find highest card of same suit */
            max=-1;
            for(k=0;k<10;k++)
               if(plr[j][k].s==curs) {
                  if(max==-1) max=k;
                  else if(plr[j][k].v>plr[j][max].v) max=k;
               }
            /* same suit not found, find highest trump */
            if(max==-1) {
               for(k=0;k<10;k++)
                  if(plr[j][k].s==trump) {
                     if(max==-1) max=k;
                     else if(plr[j][k].v>plr[j][max].v) max=k;
                  }
            }
            /* trump not found, start to despair */
            if(max==-1) {
               for(k=0;k<10;k++)
                  if(plr[j][k].s) {
                     if(max==-1) max=k;
                     else if(higher(&plr[j][k],&plr[j][max])==-1) max=k;
                  }
            }
            pld[j]=plr[j][max]; plr[j][max].s=0; plr[j][max].v=0;
         }
         bestv=-1;
         bests=curs;
         for(j=0;j<5;j++) {
            if(pld[j].s==trump && bests==curs && curs!=trump) {
               bests=trump; bestv=pld[j].v; bestp=j;
            } else if(pld[j].s==bests && pld[j].v>bestv) {
               bestv=pld[j].v; bestp=j;
            }
         }
/*         for(j=0;j<5;j++) {
            printf("%c%c",crd[pld[j].v],pld[j].s);
            if(j==bestp) printf("* ");
            else printf("  ");
         }
         printf("\n");*/
         for(j=0;j<5;j++)
            if(pld[j].s=='H') score[bestp]+=pld[j].v;
         pl=bestp;
      }
      for(i=4;i<9;i++) printf("%3d",score[i%5]);
      printf("\n");
   }
}
