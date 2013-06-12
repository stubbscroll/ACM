#include <stdio.h>
#define MAX 150

struct p_s {
   char s[21];        /* name */
   int p[4];          /* score for all 4 holes, 999=dq, 0=no score */
   char a;            /* 1:amateur */
   int tot2,tot4;     /* scores after 2 and 4 rounds */
   int shots;         /* total shots */
   int r;             /* rounds played */
   int f;             /* 1: made the cut */
   int place;
   double m;
} p[MAX];
int n;
double purse;
double m[71];

char s[10000];
char t[100];
char u[4][100];
int places[71];

int compp1(struct p_s *a,struct p_s *b)
{
   if(a->tot2<b->tot2) return -1;
   if(a->tot2>b->tot2) return 1;
   return 0;
}

int compp2(struct p_s *a,struct p_s *b)
{
   if(a->f>b->f) return -1;
   if(a->f<b->f) return 1;
   if(a->tot4<b->tot4) return -1;
   if(a->tot4>b->tot4) return 1;
   if(a->r>b->r) return -1;
   if(a->r<b->r) return 1;
   if(a->shots<b->shots) return -1;
   if(a->shots>b->shots) return 1;
   return strcmp(a->s,b->s);
}

int main()
{
   int cases,i,j,k,place;
   double cash;

   gets(s);
   sscanf(s,"%d",&cases);
   while(cases--) {
      do {
         gets(s);
      } while(!s[0]);
      sscanf(s,"%lf",&purse);
      for(i=0;i<70;i++) {
         gets(s);
         sscanf(s,"%lf",&m[i]);
         m[i]*=(purse/100.0);
      }
      gets(s);
      sscanf(s,"%d",&n);
      for(i=0;i<n;i++) {
         memset(s,0,50);
         gets(s);
         for(j=0;j<20;j++) p[i].s[j]=s[j];
         p[i].s[j]=0;
         for(j=19;j>=0;j--)
            if(s[j]!=' ') {
               p[i].a=s[j]=='*'; break;
            }
         p[i].r=0;
         k=sscanf(s+20,"%s %s %s %s",u[0],u[1],u[2],u[3]);
         for(j=0;j<k;j++) {
            if(u[j][0]=='D') p[i].p[j]=999;
            else if(isdigit(u[j][0])) {
               p[i].p[j]=strtol(u[j],NULL,10);
               p[i].r++;
            } else {
               printf("score garbage");
               return 1/0;
            }
         }
         for(;j<4;j++) p[i].p[j]=0;
         for(j=1;j<4;j++)
            if(!p[i].p[j] && p[i].p[j-1]!=999 && p[i].p[j-1]) {
               printf("ERROR no score, not dq %s\n",p[i].s);
               for(j=0;j<4;j++) printf("%d ",p[i].p[j]);
               return 1/0;
            }
         p[i].tot2=p[i].p[0]+p[i].p[1];
         p[i].tot4=p[i].tot2+p[i].p[2]+p[i].p[3];
         p[i].f=0;
         p[i].place=0;
         if(p[i].tot4>400) p[i].tot4=1000;
         if(p[i].tot2>400) p[i].tot2=1000;
         p[i].shots=0;
         for(j=0;j<4;j++) {
            if(p[i].p[j]==999) break;
            p[i].shots+=p[i].p[j];
         }
      }
      qsort(p,n,sizeof(p[0]),compp1);
      for(i=0;i<70;i++) p[i].f=1;
      for(i=70;i<n;i++)
         if(p[i].tot2==p[69].tot2) p[i].f=1;
      qsort(p,n,sizeof(p[0]),compp2);
      j=1;
      for(i=0;i<71;i++) places[i]=0;
      for(i=0;i<n;i++) {
         if(p[i].a) continue;
         if(p[i].tot4>999) continue;
         if(j==1) {
            k=i;
            p[i].place=j++; continue;
         }
         if(p[i].tot4==p[k].tot4) {
            p[i].place=p[k].place;
            j++;
            k=i;
         } else {
            p[i].place=j++;
            k=i;
         }
      }
      for(i=0;i<n;i++) {
         if(p[i].place>70) p[i].place=0;
         else places[p[i].place]++;
      }
      for(i=0;i<n;i++)
         if(p[i].place) {
            k=p[i].place;
            if(k>70) continue;
            cash=0;
            for(j=0;j<places[k];j++)
               if(j+k<71) cash+=m[j+k-1];
            p[i].m=cash/places[k];
         }
      printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n");
      printf("-----------------------------------------------------------------------\n");
      j=0;
      for(i=0;i<n;i++) {
         if(!p[i].f) break;
         if(!i || p[i].tot4!=p[i-1].tot4) place=i+1;
         if(p[i].tot4>400) strcpy(t,"  ");
         else {
            sprintf(t,"%d",place);
            if(p[i].place && p[i].place<71 && !p[i].a && places[p[i].place]>1) strcat(t,"T");
         }
         printf("%s %-10s",p[i].s,t);
         for(k=0;k<4;k++) {
            if(p[i].p[k]==0 || p[i].p[k]>=100) printf("     ");
            else printf("%02d   ",p[i].p[k]);
         }
         if(p[i].tot4<400) printf("%d",p[i].tot4);
         else printf("DQ");
         if(p[i].place) {
            if(p[i].tot4>400) printf(" ");
            else if(p[i].tot4<10) printf("  ");
            else if(p[i].tot4<100) printf(" ");
            printf("       $%9.2f",p[i].m);
         }
         printf("\n");
      }
      if(cases) printf("\n");
   }
}
