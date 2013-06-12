#include <stdio.h>

struct t_s {
   int x,y,z;
} t[5001];
int tn;
int h[10];

int compt(struct t_s *a,struct t_s *b)
{
   if(a->x < b->x) return -1;
   else if(a->x > b->x) return 1;
   if(a->y < b->y) return -1;
   else if(a->y > b->y) return 1;
   if(a->z < b->z) return -1;
   else return 1;
}

int main()
{
   int i,j,x,y,z,d,cl;

   tn=0;
   while(1) {
      scanf("%d %d %d",&x,&y,&z);
      if(x==0 && y==0 && z==0) break;
      t[tn].x=x; t[tn].y=y; t[tn++].z=z;
   }
   qsort(t,tn,sizeof(t[0]),compt);
   for(i=0;i<10;i++) h[i]=0;
   for(i=0;i<tn;i++) {
      j=i+1;
      cl=11;
      while(j<tn && t[j].x-t[i].x<10) {
         x=t[j].x-t[i].x;
         y=t[j].y-t[i].y;
         z=t[j].z-t[i].z;
         d=sqrt(x*x+y*y+z*z);
         if(d<cl) cl=d;
         j++;
      }
      j=i-1;
      while(j>=0 && t[i].x-t[j].x<10) {
         x=t[j].x-t[i].x;
         y=t[j].y-t[i].y;
         z=t[j].z-t[i].z;
         d=sqrt(x*x+y*y+z*z);
         if(d<cl) cl=d;
         j--;
      }
      if(cl<10) h[cl]++;
   }
   for(i=0;i<10;i++) printf("%4d",h[i]);
   printf("\n");
}
