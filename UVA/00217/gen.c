#include <stdio.h>
#include <math.h>
#define MANY 10000
#define PRE 44
#define RANGE 50
#define R 100
#define DEC 10000
#define SP 5
#define EPS 1e-7

const char x[PRE][21]={"First","Second","Third","Fourth","Fifth","Sixth",
   "Seventh","Eighth","Ninth","Tenth","Eleventh","Twelfth","Thirteenth",
   "Zeroeth","Goth","Hoth","BeaconX","Aldimere","Sturmtebergh","Bluecher",
   "Ownship","Commodore","Amiga","Bluetooth","Yellowbeard","Alexandria",
   "Indiana","Jones","Slechtvalk","Antestor","Arvinger","Tourniquet",
   "BigHand","Camel","Crimson","Moonlight","Seven","Angels","Deliverance",
   "Narnia","Vaakevandring","Kekal","Sanctifica","twentyletternameblah"};
char t[PRE];

char bs[30][21];
double bx[30],by[30];

double pi,d2r;
double dangle,rangle,speed,bear[2],rbear[2];
double bdx[2],bdy[2];
double dx,dy;

double lx1[2],ly1[2],lx2[2],ly2[2];
double hx,hy;
int res;

int min[2];
int je[2];

int equal(double a,double b)
{
   return fabs(a-b)<EPS;
}

int samesigns(double a,double b)
{
   if(fabs(a)<EPS && fabs(b)<EPS) return 1;
   if(a<0 && b<0) return 1;
   if(a>0 && b>0) return 1;
   return 0;
}

/* 0: lines don't intersect, 1:lines intersect, 2:lines are colinear */
int linesintersect(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,
   double *x,double *y)
{
   double a1,a2,b1,b2,c1,c2;
   double denom,num;

   a1=y2-y1; b1=x1-x2; c1=x2*y1-x1*y2;
   a2=y4-y3;
   b2=x3-x4;
   c2=x4*y3-x3*y4;
   denom=a1*b2-a2*b1;
   if(equal(denom,0)) return 2;
   num=b1*c2-b2*c1;
   *x=(double)num/denom;
   num=a2*c1-a1*c2;
   *y=(double)num/denom;
   return 1;
}

int main()
{
   int cases=20,n,m,i,j,k,l,a1,a2,b1,b2;
   double a,b,c;

   pi=2*acos(0); d2r=pi/180;
   printf("4\n");
   printf("First 2.0 4.0\n");
   printf("Second 6.0 2.0\n");
   printf("Third 6.0 7.0\n");
   printf("Fourth 10.0 5.0\n");
   printf("2\n");
   printf("0.0 1.0\n");
   printf("1 First 270.0\n");
   printf("2 Fourth 90.0\n");
   printf("116.5651 2.2361\n");
   printf("4 Third 126.8699\n");
   printf("5 First 319.3987\n");
   printf("4\n");
   printf("First 2.0 4.0\n");
   printf("Second 6.0 2.0\n");
   printf("Third 6.0 7.0\n");
   printf("Fourth 10.0 5.0\n");
   printf("1\n");
   printf("0.0 1.0\n");
   printf("1 First 270.0\n");
   printf("2 Fourth 90.0\n");
   printf("2\n");
   printf("First 1 1\n");
   printf("Second 10 10\n");
   printf("5\n");
   printf("0.0 1.0\n");
   printf("1 First 90.0\n");
   printf("2 First 100.0\n");
   printf("0.0 1.0\n");
   printf("1 First 90.0\n");
   printf("2 First 90.0\n");
   printf("0.0 1.0\n");
   printf("1 First 90.0\n");
   printf("1 First 90.0\n");
   printf("0.0 0.0\n");
   printf("1 First 90.0\n");
   printf("1 First 90.0\n");
   printf("0.0 0.0\n");
   printf("1 First 90.0\n");
   printf("2 Second 80.0\n");

   while(cases--) {
      n=rand()%30+1;
      m=rand()%50;
      if(!cases) { m=MANY; n=30; }
      printf("%d\n",n);
      memset(t,0,PRE);
      for(i=0;i<n;i++) {
      again:
         if(rand()&1) {
            k=rand()%20+1;
            for(j=0;j<k;j++) bs[i][j]=rand()%26+65+(rand()&1)*32;
            bs[i][j]=0;
         } else {
            do j=rand()%PRE; while(t[j]);
            t[j]=1;
            strcpy(bs[i],x[j]);
         }
         for(j=0;j<i;j++) if(!strcmp(bs[j],bs[i])) goto again;
         bx[i]=rand()%R-RANGE+(rand()%DEC)/(double)DEC;
         by[i]=rand()%R-RANGE+(rand()%DEC)/(double)DEC;
         printf("%s %.4f %.4f\n",bs[i],bx[i],by[i]);
      }
      printf("%d\n",m);
      while(m--) {
      agains:
         do {
            min[0]=rand()%1440; min[1]=rand()%1440;
         } while(min[0]>min[1]);
         k=rand()%n; l=rand()%n;
         do {
            a1=rand()%360; a2=rand()%DEC;
            b1=rand()%360; b2=rand()%DEC;
            a=a1+a2/(double)DEC;
            b=b1+b2/(double)DEC;
            if(a1==b1 && a2==b2) break;
            c=fabs(a-b);
            if(c>180) c=360-c;
         } while(0);
         if(rand()%32==0) b=a;
         bear[0]=a; bear[1]=b;
         dangle=rand()%360+(rand()%DEC)/(double)DEC;
         speed=rand()%SP+(rand()%DEC)/(double)DEC;

         /* solve */

         rangle=dangle*d2r;
         je[0]=k; je[1]=l;
         for(i=0;i<2;i++) {
            rbear[i]=(bear[i]-floor(bear[i]/180)*180)*d2r;
            bdx[i]=sin(rbear[i]+rangle);
            bdy[i]=cos(rbear[i]+rangle);
            /* create line segments for beacons */
            j=je[i];
            lx1[i]=bx[j]-bdx[i];
            ly1[i]=by[j]-bdy[i];
            lx2[i]=bx[j]+bdx[i];
            ly2[i]=by[j]+bdy[i];
         }

         if(equal(rbear[0],rbear[1])) goto okay;
         dx=sin(rangle)*(min[1]-min[0])*speed;
         dy=cos(rangle)*(min[1]-min[0])*speed;
         res=linesintersect(lx1[0]+dx,ly1[0]+dy,lx2[0]+dx,ly2[0]+dy,
            lx1[1],ly1[1],lx2[1],ly2[1],&hx,&hy);
         if(res!=1) { printf(",."); return 1/0; goto agains; }
         /* remove large coordinates */
         if(fabs(hx)>10000 || fabs(hy)>10000) goto agains;
         /* remove potential rounding errors */
         if(fabs(hx*1e2-floor(hx*1e2)-0.5)>1e2) goto agains;
         if(fabs(hy*1e2-floor(hy*1e2)-0.5)>1e2) goto agains;
         /* remove illegal coordinates */
         if(min[1]==min[0] && k==l && bear[0]!=bear[1]) goto agains;
okay:
         printf("%.4f %.4f\n",dangle,speed);
         printf("%d %s %.4f\n",min[0],bs[l],bear[1]);
         printf("%d %s %.4f\n",min[1],bs[k],bear[0]);
      }
   }
}

