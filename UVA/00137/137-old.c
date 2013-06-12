#include <stdio.h>

struct p_s {
   double x,y;
};

struct pi_s {
   int x,y;
} s[4],t;

int compp(struct p_s *a,struct p_s *b)
{
   if(a->x < b->x) return -1;
   if(a->x > b->x) return 1;
   return (a->y > b->y)-(a->y < b->y);
}

int comppi(struct pi_s *a,struct pi_s *b)
{
   if(a->x < b->x) return -1;
   if(a->x > b->x) return 1;
   return (a->y > b->y)-(a->y < b->y);
}

#define SAME_SIGNS(a,b) (((int) ((unsigned) a^(unsigned)b))>=0)

/* 0: lines don't intersect, 1:lines intersect, 2:lines are colinear */
int linesintersect(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,
   double *x,double *y)
{
   int a1,a2,b1,b2,c1,c2;
   int r1,r2,r3,r4;
   int denom,num;

   a1=y2-y1; b1=x1-x2; c1=x2*y1-x1*y2;
   r3=a1*x3+b1*y3+c1;
   r4=a1*x4+b1*y4+c1;
   if(r3!=0 && r4!=0 && SAME_SIGNS(r3,r4)) return 0;
   a2=y4-y3;
   b2=x3-x4;
   c2=x4*y3-x3*y4;
   r1=a2*x1+b2*y1+c2;
   r2=a2*x2+b2*y2+c2;
   if(r1!=0 && r2!=0 && SAME_SIGNS(r1,r2)) return 0;
   denom=a1*b2-a2*b1;
   if(denom==0) return 2;
   num=b1*c2-b2*c1;
   *x=(double)num/denom;
   num=a2*c1-a1*c2;
   *y=(double)num/denom;
   return 1;
}

int pnpoly(int n,int *px,int *py,int ix,int iy)
{
   double x=ix,y=iy,xpi,ypi,ypj,xpj;
   int i,j,c=0;

   for(i=0;i<n;i++) {
      xpi=px[i];
      ypi=py[i];
      xpj=px[i+1];
      ypj=py[i+1];
      if((((ypi<=y) && (y<ypj)) ||
         ((ypj<=y) && (y<ypi))) &&
         (x < (xpj - xpi) * (y - ypi) / (ypj - ypi) + xpi))
         c=!c; 
   } 
   return c;
}

/* start of convex hull algorithm from geometryalgorithms.com */
double isleft(struct p_s p0,struct p_s p1,struct p_s p2)
{
   return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
}

/* chainhull2d(): Andrew's monotone chain 2D convex hull algorithm
     Input:  p[] = an array of 2D points 
                   presorted by increasing x- and y-coordinates
             n = the number of points in p[]
     Output: h[] = an array of the convex hull vertices (max is n)
     Return: the number of points in h[] */
int chainhull2d(struct p_s *p,int n,struct p_s *h)
{
   /* the output array h[] will be used as the stack */
   int bot=0, top=(-1);  /* indices for bottom and top of the stack */
   int i;                /* array scan index */
   int minmin,minmax,maxmin,maxmax;
   double xmin,xmax;
   int n2;

   /* sort by increasing x- and then y-coordinates */
   qsort(p,n,sizeof(p[0]),compp);
   /* remove duplicates */
   n2=1;
   for(i=1;i<n;i++) {
      if(i!=n2) p[n2]=p[i];
      if(p[i].x!=p[i-1].x || p[i].y!=p[i-1].y) n2++;
   }
   n=n2;
   /* Get the indices of points with min x-coord and min|max y-coord */
   minmin = 0;
   xmin = p[0].x;
   for(i=1;i<n;i++)
      if (p[i].x != xmin) break;
   minmax = i-1;
   if (minmax == n-1) {       /* degenerate case: all x-coords == xmin */
      h[++top] = p[minmin];
      if (p[minmax].y != p[minmin].y) /* a nontrivial segment */
         h[++top] = p[minmax];
      h[++top] = p[minmin];           /* add polygon endpoint */
      return top+1;
   }

   /* Get the indices of points with max x-coord and min|max y-coord */
   maxmax = n-1;
   xmax = p[n-1].x;
   for (i=n-2; i>=0; i--)
      if (p[i].x != xmax) break;
   maxmin = i+1;

   /* Compute the lower hull on the stack H */
   h[++top] = p[minmin];      /* push minmin point onto stack */
   i = minmax;
   while (++i <= maxmin) {
      /* the lower line joins P[minmin] with P[maxmin] */
      if (isleft( p[minmin], p[maxmin], p[i]) >= 0 && i < maxmin)
          continue;          /* ignore P[i] above or on the lower line */

      while (top > 0) {        /* there are at least 2 points on the stack */
        /* test if P[i] is left of the line at the stack top */
         if (isleft( h[top-1], h[top], p[i]) > 0)
            break;         /* P[i] is a new hull vertex */
         else
            top--;         /* pop top point off stack */
      }
      h[++top] = p[i];       /* push P[i] onto stack */
   }

   /* Next, compute the upper hull on the stack H above the bottom hull */
   if (maxmax != maxmin)      /* if distinct xmax points */
      h[++top] = p[maxmax];  /* push maxmax point onto stack */
   bot = top;                 /* the bottom point of the upper hull stack */
   i = maxmin;
   while (--i >= minmax) {
      /* the upper line joins P[maxmax] with P[minmax] */
      if (isleft( p[maxmax], p[minmax], p[i]) >= 0 && i > minmax)
         continue;          /* ignore P[i] below or on the upper line */

      while (top > bot) {  /* at least 2 points on the upper stack */
          /* test if P[i] is left of the line at the stack top */
          if (isleft( h[top-1], h[top], p[i]) > 0)
             break;         /* P[i] is a new hull vertex */
          else
             top--;         /* pop top point off stack */
      }
      h[++top] = p[i];       /* push P[i] onto stack */
   }
   if (minmax != minmin)
      h[++top] = p[minmin];  /* push joining endpoint onto stack */

   return top;
}

int areap(int np,int *px,int *py)
{
   int i,a;

   a=0;
   for(i=1;i<=np;i++)
      a+=px[i-1]*py[i]-
         px[i]*py[i-1];
   return a;
}

double aread(int np,struct p_s *r)
{
   int i;
   double a;

   a=0;
   for(i=1;i<=np;i++)
      a+=r[i-1].x*r[i].y-
         r[i].x*r[i-1].y;
   return a;
}

int px[2][1001],py[2][1001];
int n[2];
struct p_s p[100202],r[5002];
int np,nr;

int main()
{
   int i,j,k;
   double x,y,a1,a2,a3,a;

   while(1) {
      for(i=0;i<2;i++) {
         scanf("%d",&n[i]);
         if(n[0]==0) goto done;
         for(j=0;j<n[i];j++) scanf("%d %d",&px[i][j],&py[i][j]);
         px[i][j]=px[i][0]; py[i][j]=py[i][0];
      }
      np=0;
      for(i=0;i<n[0];i++)
         for(j=0;j<n[1];j++) {
            /* check all lines in polygon 1 against all lines in polygon 2 for
             * intersections */
            k=linesintersect(px[0][i],py[0][i],px[0][i+1],py[0][i+1],
               px[1][j],py[1][j],px[1][j+1],py[1][j+1],&x,&y);
            if(k==1) {
               p[np].x=x; p[np++].y=y;
            } else if(k==2) {
               s[0].x=px[0][i]; s[0].y=py[0][i];
               s[1].x=px[0][i+1]; s[1].y=py[0][i+1];
               s[2].x=px[1][j]; s[2].y=py[1][j];
               s[3].x=px[1][j+1]; s[3].y=py[1][j+1];
               qsort(s,2,sizeof(s[0]),comppi);
               qsort(s+2,2,sizeof(s[0]),comppi);
               if(comppi(&s[1],&s[2])==1) {
                  if(comppi(&s[0],&s[2])==1) {
                     p[np].x=s[0].x; p[np++].y=s[0].y;                     
                  } else {
                     p[np].x=s[2].x; p[np++].y=s[2].y;
                  }
                  if(comppi(&s[1],&s[2])!=0) {
                     if(comppi(&s[1],&s[3])==-1) {
                        p[np].x=s[1].x; p[np++].y=s[1].y;
                     } else {
                        p[np].x=s[3].x; p[np++].y=s[3].y;
                     }
                  }
               }
            }
         }
      /* check if point from polygon 1 is within polygon 2 */
      for(i=0;i<n[0];i++)
         if(pnpoly(n[1],px[1],py[1],px[0][i],py[0][i])) {
            p[np].x=px[0][i]; p[np++].y=py[0][i];
         }
      /* check if point from polygon 2 is within polygon 1 */
      for(j=0;j<n[1];j++)
         if(pnpoly(n[0],px[0],py[0],px[1][j],py[1][j])) {
            p[np].x=px[1][j]; p[np++].y=py[1][j];
         }
/*      printf("%d: ",np);
      for(i=0;i<np;i++) printf("(%.1f %.1f) ",p[i].x,p[i].y);
      printf("\n");*/
      /* convex hull */
      if(np>=3) {
         nr=chainhull2d(p,np,r);
         r[nr]=r[0];
      } else 
         nr=0;
/*      printf("%d: ",nr);
      for(i=0;i<=nr;i++) printf("(%.1f %.1f) ",r[i].x,r[i].y);
      printf("\n");*/
      a1=fabs(areap(n[0],px[0],py[0]));
      a2=fabs(areap(n[1],px[1],py[1]));
      if(nr>=3) a3=fabs(aread(nr,r));
      else a3=0;
      a=(a1+a2)/2-a3;
      printf("%8.2f",a);
   }
done:
   printf("\n");
}
