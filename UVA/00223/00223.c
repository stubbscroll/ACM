#include <stdio.h>
#include <math.h>
#define MAX 401

struct p_s {
   int x,y;
} p[MAX*2];
int pn;

int g[MAX][MAX];
int gn[MAX];
int b[MAX][MAX];
int bn[MAX];
int bnn;
int cur[MAX],cur2[MAX];
int curn;
int res[MAX];

int findpoint(int x,int y)
{
   int i;

   for(i=0;i<pn;i++) if(p[i].x==x && p[i].y==y) return i;
   p[pn].x=x; p[pn].y=y; gn[pn]=0;
   return pn++;
}
/*
int ccw(int a,int b,int c)
{
   return p[a].x * p[b].y - p[a].y * p[b].x + p[a].y * p[c].x
      -p[a].x * p[c].y + p[b].x * p[c].y - p[c].x * p[b].y;
}*/

int main()
{
   int n,i,j,k,x1,y1,x2,y2,q,r,x,y;
   int minx,miny,maxx,maxy,maxa,maxi,cura,curi,p1,p2;
   int caseno=1,first=1;
   int dx,dy;
   double aln,abest,acur,pi=2*acos(0);

   while(1) {
      scanf("%d",&n);
      if(n==0) break;
      pn=0;
      for(i=0;i<n;i++) {
         scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
         q=findpoint(x1,y1); r=findpoint(x2,y2);
         g[q][gn[q]++]=r;
         g[r][gn[r]++]=q;
      }
/*      for(i=0;i<pn;i++) printf("%d: <%d %d>\n",i,p[i].x,p[i].y);*/
      minx=miny=10000; maxx=maxy=0;
      for(i=0;i<pn;i++) {
         if(p[i].x<minx) minx=p[i].x;
         if(p[i].x>maxx) maxx=p[i].x;
         if(p[i].y<miny) miny=p[i].y;
         if(p[i].y>maxy) maxy=p[i].y;
      }
      memset(res,0,MAX*sizeof(int));
      bnn=0;
      if(!first) printf("\n");
      else first=0;
      printf("Case %d\n",caseno++);
      for(i=0;i<pn;i++) {
         if(p[i].x!=minx && p[i].x!=maxx && p[i].y!=miny && p[i].y!=maxy) continue;
         /* find previous point in line segment */
         maxi=-123;
         x=p[i].x; y=p[i].y;
         /* check upper line, find rightmost point to the left of i */
         if(y==maxy && x>minx) {
/*            printf("upper ");*/
            maxa=-1;
            for(j=0;j<gn[i];j++) {
               k=g[i][j];
               if(p[k].x>maxa && p[k].x<x && p[k].y==y) {
                  maxi=k; maxa=p[k].x;
               }
            }
         /* check left line, find uppermost point below i */
         } else if(x==minx && y>miny) {
/*            printf("left  ");*/
            maxa=-1;
            for(j=0;j<gn[i];j++) {
               k=g[i][j];
               if(p[k].y>maxa && p[k].y<y && p[k].x==x) {
                  maxi=k; maxa=p[k].y;
               }
            }
         /* check lower line, find leftmost point to the right of i */
         } else if(y==miny && x<maxx) {
/*            printf("lower ");*/
            maxa=100000;
            for(j=0;j<gn[i];j++) {
               k=g[i][j];
               if(p[k].x<maxa && p[k].x>x && p[k].y==y) {
                  maxi=k; maxa=p[k].x;
               }
            }
         /* check right line, find lowermost point above i */
         } else if(x==maxx && y<maxy) {
/*            printf("right ");*/
            maxa=100000;
            for(j=0;j<gn[i];j++) {
               k=g[i][j];
               if(p[k].y<maxa && p[k].y>y && p[k].x==x) {
                  maxi=k; maxa=p[k].y;
               }
            }
         }
/*         printf("(%d %d) (%d %d)\n",p[maxi].x,p[maxi].y,x,y);*/
/*         if(maxi<0) i=1/0;*/ /* maxi is never negative here */
         cur[0]=maxi; cur[1]=i; curn=2;
/*            printf("for point: %d (%d %d)\n",i,p[i].x,p[i].y);*/
         while(1) {
            p1=cur[curn-2]; p2=cur[curn-1];
            maxa=-100000; curi=-123;
            /* this routine is wrong! find a way to measure angle */
            dx=p[p1].x-p[p2].x; dy=p[p1].y-p[p2].y;
            /* prefer degrees... */
            aln=atan2(dy,dx)*(180/pi);
            if(aln<0) aln+=360;
/*            if(curn==2) printf("%f\n",aln);*/
            abest=999;
            for(j=0;j<gn[p2];j++) {
               k=g[p2][j];
               if(k==p1 || k==p2) continue;
               dx=p[p2].x-p[k].x; dy=p[p2].y-p[k].y;
               acur=atan2(dy,dx)*(180/pi);
               while(acur>aln-180) acur-=360;
/*               if(curn==2) printf("(%d %d):%f\n",p[k].x,p[k].y,acur);*/
               if(acur<abest) {
                  abest=acur; curi=k;
               }
/*               cura=-ccw(p1,p2,k);
               if(curn==2) printf("(%d %d):%d\n",p[k].x,p[k].y,cura);*/
/*               if(cura>maxa) {
                  maxa=cura; curi=k;
               }*/
            }
/*            if(curn==2) printf("(%d %d) (%d %d) (%d %d)\n",p[p1].x,p[p1].y,p[p2].x,p[p2].y,p[curi].x,p[curi].y);
            if(curn==2) printf("%d\n",p2);*/
/*            if(curi<0) i=1/0;*/  /* is never negative */
            if(curi==cur[0]) break;
            cur[curn++]=curi;
            /* culprit! */
            if(curn>MAX) {
               while(1) printf("overflow");
            }
         }
         maxa=99999; maxi=0;
         for(k=0;k<curn;k++)
            if(cur[k]<maxa) {
               maxa=cur[k]; maxi=k;
            }
         for(k=0;k<curn;k++) cur2[k]=cur[(k+maxi)%curn];
/*         printf("%d:",curn);
         for(k=0;k<curn;k++) printf(" %d",cur2[k]);
         printf("\n");*/
         for(k=0;k<bnn;k++)
            if(bn[k]==curn) {
               for(j=0;j<curn;j++) if(b[k][j]!=cur2[j]) break;
               if(j==curn) goto found;
            }
         for(k=0;k<curn;k++) b[bnn][k]=cur2[k];
         bn[bnn++]=curn;
         res[curn]++;
      found:
         ;
      }
      for(i=0;i<MAX;i++) if(res[i])
         printf("Number of lots with perimeter consisting of %d surveyor's lines = %d\n",i,res[i]);
      printf("Total number of lots = %d\n",bnn);
   }
}
