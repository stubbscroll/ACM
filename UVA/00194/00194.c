#include <stdio.h>
#include <math.h>
#define Y(v) ((v)!=-1)
#define EPS 1e-7

double a[3];   /* sides from input */
double an[3];  /* angles from input */
double sa[3];  /* calculated sides */
double ang[3]; /* calculated angles */
double pi;

int equal(double a,double b)
{
   return fabs(a-b)<=EPS;
}

int compd(double *a,double *b)
{
   if(equal(*a,*b)) return 0;
   if(*a<*b) return -1;
   else return 1;
}

/* calculate last angle */
void lasta(int x,int y,int z)
{
   ang[z]=pi-an[x]-an[y];
}

/* return index of known side */
int ks()
{
   int i;

   for(i=0;i<3;i++) if(Y(a[i])) return i;
   return 1/0;
}

/* apply sinus rule to find other sides */
void sr(int ks)
{
   int i;

   for(i=0;i<3;i++)
      if(i!=ks) sa[i]=sin(ang[i])*a[ks]/sin(ang[ks]);
}

/* given 2 sides a[x] and a[(x+1)%3] and angle[x] between them, find the rest */
int calc21(int x,int y,int z)
{
   int i,j,k;
   double l,m;

   /* first, find out if we have the potential ambiguous case: check if side
    * with opposite angle is smaller than the other known side */
   if(a[x]<a[y]) {
      j=y;
      /* find angle of smallest side without opposite angle */
      ang[j]=asin(a[j]*sin(an[x])/a[x]);
      /* l: alternate angle */
      l=pi-ang[j];
      /* find last angle */
      for(i=0;i<3;i++)
         if(i!=j && i!=x) k=i;
      ang[k]=pi-an[x]-ang[j];
      m=pi-an[x]-l;
      i=ks(); sr(i);
      /* alternate last angle is within 0..pi, we have two solutions */
      if(m>=EPS && m<pi) return 0;
      return 1;
   }
   /* find smallest side without opposite angle */
   j=y;
   /* find angle of smallest side without opposite angle */
   ang[j]=asin(a[j]*sin(an[x])/a[x]);
   /* find last angle */
   for(i=0;i<3;i++)
      if(i!=j && i!=x) k=i;
   ang[k]=pi-an[x]-ang[j];   
   i=ks(); sr(i);
   return 1;
}

/* x: known angle: y,z: known sides */
void calc12(int x,int y,int z)
{
   int i,j,k;

   if(Y(sa[x])) x=1/0;
   sa[x]=sqrt(a[y]*a[y]+a[z]*a[z]-2*a[y]*a[z]*cos(an[x]));
   for(i=0;i<3;i++)
      if(!Y(an[i])) {
         j=(i+1)%3; k=(i+2)%3;
         ang[i]=acos(sa[j]/(2*sa[k])+sa[k]/(2*sa[j])-sa[i]*sa[i]/(2*sa[j]*sa[k]));
      }
}

int main()
{
   int cases,i,j,k,x,y,z;

   pi=2*acos(0);
   scanf("%d",&cases);
   while(cases--) {
      scanf("%lf %lf %lf %lf %lf %lf",&a[0],&an[0],&a[1],&an[1],&a[2],&an[2]);
      j=k=0;
      for(i=0;i<3;i++) {
         if(!Y(a[i])) j++;
         if(!Y(an[i])) k++;
         sa[i]=a[i]; ang[i]=an[i];
      }
      /* angles are not pi */
      if(!k && !equal(pi,an[0]+an[1]+an[2])) goto invalid;
      /* missing more than 3 elements, or missing all sides, reject */
      if(j+k>3 || j==3) goto invalid;
      /* 3 sides given */
      if(j==0) {
         for(i=0;i<3;i++) {
            j=(i+1)%3; k=(i+2)%3;
            ang[i]=acos(a[j]/(2*a[k])+a[k]/(2*a[j])-a[i]*a[i]/(2*a[j]*a[k]));
         }
         goto done;
      }
      /* angles a+b given */
      if(Y(an[0]) && Y(an[1])) {
         lasta(0,1,2);
         i=ks(); sr(i);
         for(i=0;i<3;i++) if(Y(a[i]) && !equal(a[i],sa[i])) goto invalid;
         goto done;
      }
      /* angles b+c given */
      if(Y(an[1]) && Y(an[2])) {
         lasta(2,1,0);
         i=ks(); sr(i);
         goto done;
      }
      /* angles c+a given */
      if(Y(an[2]) && Y(an[0])) {
         lasta(0,2,1);
         i=ks(); sr(i);
         for(i=0;i<3;i++) if(Y(a[i]) && !equal(a[i],sa[i])) goto invalid;
         goto done;
      }
      /* side a+b and angle a given */
      if(Y(a[0]) && Y(a[1]) && Y(an[0])) {
         if(!calc21(0,1,2)) goto amb;
         goto done;
      }
      /* side a+c and angle a given */
      if(Y(a[0]) && Y(a[2]) && Y(an[0])) {
         if(!calc21(0,2,1)) goto amb;
         goto done;
      }
      /* side b+c and angle b given */
      if(Y(a[1]) && Y(a[2]) && Y(an[1])) {
         if(!calc21(1,2,0)) goto amb;
         goto done;
      }
      /* side b+a and angle b given */
      if(Y(a[1]) && Y(a[0]) && Y(an[1])) {
         if(!calc21(1,0,2)) goto amb;
         goto done;
      }
      /* side c+a and angle c given */
      if(Y(a[2]) && Y(a[0]) && Y(an[2])) {
         if(!calc21(2,0,1)) goto amb;
         goto done;
      }
      /* side c+b and angle c given */
      if(Y(a[2]) && Y(a[1]) && Y(an[2])) {
         if(!calc21(2,1,0)) goto amb;
         goto done;
      }
      /* we have two sides and another angle */
      if(j==1 && k==2) {
         for(i=0;i<3;i++)
            if(!Y(a[i])) x=i;
         if(x==0) {
            y=1; z=2;
         } else if(x==1) {
            y=0; z=2;
         } else if(x==2) {
            y=1; z=0;
         }
         calc12(x,y,z);
         goto done;
      }
      i=1/0;
   invalid:
      printf("Invalid input.\n");
      continue;
   amb:
      printf("More than one solution.\n");
      continue;
   done:
      for(i=0;i<3;i++) {
         if(Y(a[i]) && !equal(a[i],sa[i])) goto invalid;
         if(Y(an[i]) && !equal(an[i],ang[i])) goto invalid;
         if(sa[i]<EPS) goto invalid;
         if(ang[i]<EPS || ang[i]>=pi) goto invalid;
         a[i]=sa[i];
      }
      qsort(a,3,sizeof(double),compd);
      if(a[0]>a[1]+a[2]) goto invalid;
      printf("%.6f %.6f %.6f %.6f %.6f %.6f\n",sa[0],ang[0],sa[1],ang[1],sa[2],ang[2]);
   }
}
