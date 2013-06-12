#include <stdio.h>
#include <math.h>
#define MAXB 30
#define MAXL 21
#define EPS 1e-7
/*#define DEBUG*/

char bs[MAXB][MAXL];
double bx[MAXB],by[MAXB];
int n,m;
double pi,d2r;

char s[2][MAXL];
double ang,speed,bear[2],beara;
int min[2];

double bdx[2],bdy[2];
double dx,dy;

double lx1[2],ly1[2],lx2[2],ly2[2];
double hx,hy,t1,t2,t3,diff;
int res;

int find(char *s)
{
   int i;

   for(i=0;i<n;i++) if(!strcmp(s,bs[i])) return i;
   return 1/0;
}

int equal(double a,double b)
{
   return fabs(a-b)<EPS;
}

/* 0: lines don't intersect, 1:lines intersect, 2:lines are colinear */
int linesintersect(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,
   double *x,double *y)
{
   double a1,a2,b1,b2,c1,c2;
   double denom,num;

   a1=y2-y1; b1=x1-x2; c1=x2*y1-x1*y2;
   a2=y4-y3; b2=x3-x4; c2=x4*y3-x3*y4;
   denom=a1*b2-a2*b1;
   if(equal(denom,0)) return 2;
   num=b1*c2-b2*c1;
   *x=num/denom;
   num=a2*c1-a1*c2;
   *y=num/denom;
   return 1;
}

int main()
{
   int caseno=1,i,j;
   double x1,y1,x2,y2;
   double a,b;

   pi=2*acos(0); d2r=pi/180;
   while(scanf("%d",&n)==01) {
      for(i=0;i<n;i++) scanf("%s %lf %lf",bs[i],&bx[i],&by[i]);
      scanf("%d",&m);
      while(m--) {
         scanf("%lf %lf",&ang,&speed);
         ang*=d2r;
         for(i=0;i<2;i++) {
            scanf("%d %s %lf",&min[i],s[i],&bear[i]);
            bear[i]=(bear[i]-floor(bear[i]/180)*180)*d2r;
            bdx[i]=sin(bear[i]+ang);
            bdy[i]=cos(bear[i]+ang);
            /* create line segments for beacons */
            j=find(s[i]);
            lx1[i]=bx[j]-bdx[i];
            ly1[i]=by[j]-bdy[i];
            lx2[i]=bx[j]+bdx[i];
            ly2[i]=by[j]+bdy[i];
         }
         printf("Scenario %d: ",caseno++);
         if(equal(bear[0],bear[1])) {
            printf("Position cannot be determined\n");
            continue;
         }
         dx=sin(ang)*(min[1]-min[0])*speed;
         dy=cos(ang)*(min[1]-min[0])*speed;
         res=linesintersect(lx1[0]+dx,ly1[0]+dy,lx2[0]+dx,ly2[0]+dy,
            lx1[1],ly1[1],lx2[1],ly2[1],&hx,&hy);
         if(res!=1) {
            printf("Should never happen...\n");
            return 1/0;
         }
#ifdef DEBUG
         /* check if answer is correct */
         j=find(s[1]);
         a=fmod(10*pi+pi/2-atan2(by[j]-hy,bx[j]-hx)-ang,pi);
         b=fmod(bear[1],pi);
         if(!equal(a,b)) {
            printf("[ERROR %.2f %.2f] ",a,b);
            return 1/0;
         }
         j=find(s[0]);
         a=fmod(10*pi+pi/2-atan2(by[j]-hy+dy,bx[j]-hx+dx)-ang,pi);
         b=fmod(bear[0],pi);
         if(!equal(a,b)) {
            printf("[ERROR %.2f %.2f] ",a,b);
            return 1/0;
         }
         /* end of check */
#endif
         printf("Position is (%.2f, %.2f)\n",hx,hy);
      }
   }
}
