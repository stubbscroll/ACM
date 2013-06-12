#include <stdio.h>
#define EPS 0.000001

struct player_s {
   double won;       /* money won */
   int scores[4];    /* scores for each round, 999=DQ 999=round not played */
   int shots;        /* number of shots fired */
   int amateur;      /* 1=yes, 0=not */
   int total;        /* 999=DQ */
   int valid;        /* number of valid rounds */
   int place;
   int tie;          /* 1: place is tied among two or more non-amateurs */
   int cut;          /* score after 2 rounds */
   int madecut;      /* 0: didn't make it to the list */
   char name[21];
} plr[144];

double pursetotal;   /* total prize purse */
double purseper[70]; /* percentage * 10000 of total purse */

int numplr;          /* total number of players */

int compare_plr (struct player_s *a,struct player_s *b)
{
   if(a->madecut==1 && b->madecut==0) return -1;
   else if(a->madecut==0 && b->madecut==1) return 1;
   if(a->total < b->total) return -1;
   else if(a->total > b->total) return 1;

   if(a->total==999 && b->total==999) {
      if(a->valid > b->valid) return -1;
      else if(a->valid < b->valid) return 1;
      if(a->shots < b->shots) return -1;
      else if(a->shots > b->shots) return 1;
   } else {
      if(a->total==b->total) {
         if(a->amateur==1 && b->amateur==0) return 1;
         else if(a->amateur==0 && b->amateur==1) return -1;
      }
   }

   return strcmp(a->name,b->name);
}

int compare_plr2 (struct player_s *a,struct player_s *b)
{
   if(a->cut < b->cut) return -1;
   else if(a->cut > b->cut) return 1;
   return 0;
}

int main()
{
   char s[200];
   char t[11];
   int cases;
   int i,j,k,l,m,n;
   double tiepot;

   gets(s);
   sscanf(s,"%d",&cases);
   while(cases--)  {
      gets(s);
      gets(s);
      sscanf(s,"%lf",&pursetotal);
      for(i=0;i<70;i++) {
         gets(s);
         sscanf(s,"%lf",&purseper[i]);
      }
      gets(s);
      sscanf(s,"%d",&numplr);
      t[2]=0;
      for(i=0;i<numplr;i++) {
         gets(s);
         for(j=0;j<20;j++)
            plr[i].name[j]=s[j];
         j=19;
         while(j>0 && iswspace(s[j])) j--;
         plr[i].amateur=s[j]=='*';
         plr[i].won=-1.0;
         plr[i].name[20]=0;
         plr[i].total=plr[i].valid=plr[i].madecut=plr[i].shots=plr[i].place=plr[i].tie=0;
         plr[i].cut=999;
         for(j=0;j<4;j++) {
            t[0]=s[j*3+21];
            t[1]=s[j*3+22];
            if(j==2 && plr[i].total!=999)
               plr[i].cut=plr[i].total;
            if(t[0]=='D' && t[1]=='Q') {
               plr[i].scores[j]=999;
               plr[i].total=999;
            } else if(t[0]==' ' && t[1]==' ')
               plr[i].scores[j]=999;
            else {
               plr[i].scores[j]=strtol(t,NULL,10);
               plr[i].total+=plr[i].scores[j];
               plr[i].shots+=plr[i].scores[j];
               plr[i].valid++;
            }
         }
      }

      qsort(plr,numplr,sizeof(plr[0]),compare_plr2);

      /* remove players who didn't make the cut */

      for(i=0;i<70;i++)
         if(plr[i].cut!=999)
            plr[i].madecut=1;
      for(;i<numplr;i++) {
         if(plr[i].cut!=plr[69].cut) break;
         if(plr[i].cut!=999)
            plr[i].madecut=1;
      }
      for(;i<numplr;i++)
         plr[i].madecut=0;

      qsort(plr,numplr,sizeof(plr[0]),compare_plr);

      plr[0].place=1;
      for(i=1;i<numplr;i++)
         if(plr[i].total!=999) {
            if(plr[i].total==plr[i-1].total) {
               plr[i].place=plr[i-1].place;
               if(plr[i].amateur==0 && plr[i-1].amateur==0 && plr[i].total<999)
                  plr[i].tie=plr[i-1].tie=1;
            } else
               plr[i].place=i+1;
         }

      j=k=n=0;
      for(i=0;i<numplr;i++)
         if(!plr[i].amateur && plr[i].madecut && plr[i].total!=999) {
            if(plr[i].tie==0) {
               if(j<70)
                  plr[i].won=pursetotal*0.01*purseper[j];
               j++;
               k=j;
            } else {
               if(n!=plr[i].place) k=j;
               m=0;
               if(j==k) {
                  for(l=0;l<numplr;l++)
                     if(plr[l].place==plr[i].place && plr[l].tie)
                        m++;
                  tiepot=0;
                  for(l=k;l<k+m;l++) {
                     if(l<70)
                        tiepot+=purseper[l];
                  }
                  tiepot=pursetotal*0.01*tiepot/m;
               }
               plr[i].won=tiepot;
               j++;
            }
            n=plr[i].place;
         }

      printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n");
      printf("-----------------------------------------------------------------------\n");
      for(i=0;i<numplr;i++)
         if(plr[i].madecut) {
            t[10]=0;
            for(j=0;j<10;j++) t[j]=' ';
            if(plr[i].place>0) {
               sprintf(t,"%d",plr[i].place);
               j=strlen(t);
               t[j]=plr[i].tie ? 'T' : ' ';
            }
            printf("%s %s",plr[i].name,t);
            for(j=0;j<4;j++) {
               if(plr[i].scores[j]==999)
                  strcpy(t,"  ");
               else
                  sprintf(t,"%-2d",plr[i].scores[j]);
               printf("%s   ",t);
            }
            if(plr[i].total==999) 
               printf("DQ");
            else
               printf("%-3d",plr[i].total);
            if(plr[i].won-1>EPS) {
               if(plr[i].total==999) printf(" ");
               printf("       ");
               printf("$%9.2f\n",plr[i].won);
            } else
               printf("\n");
         }

      if(cases>0)
         printf("\n");
   }
}
