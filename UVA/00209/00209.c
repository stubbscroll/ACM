#include <stdio.h>
#define MAX 32768

int x[MAX],y[MAX];
char s[10000];
int v[6];
int nv;

int compi(int *a,int *b)
{
   return (*a>*b)-(*a<*b);
}

int main()
{
   int i,j,k,l;
   int x1,x2,x3,x4,x5,x6;
   int y1,y2,y3,y4,y5,y6;
   int dx,dy;

   j=k=0;
   for(i=1;i<MAX;i++) {
      x[i]=j; y[i]=k;
      j++;
      if(j>k) {
         k++; j=0;
      }
   }
   while(gets(s)!=NULL) {
      nv=sscanf(s,"%d %d %d %d %d %d",&v[0],&v[1],&v[2],&v[3],&v[4],&v[5]);
      qsort(v,nv,sizeof(int),compi);
      for(i=0;i<nv-1;i++) if(v[i]==v[i+1]) nv=0;
      if(nv==3) {
         x1=x[v[0]]; y1=y[v[0]];
         x2=x[v[1]]; y2=y[v[1]];
         x3=x[v[2]]; y3=y[v[2]];
         /* pointing down */
         if(y1==y2 && x2-x1==y3-y2 && x2==x3) goto ok;
         /* pointing up */
         if(y2==y3 && x1==x2 && x3-x2==y2-y1) goto ok;
      } else if(nv==4) {
         x1=x[v[0]]; y1=y[v[0]];
         x2=x[v[1]]; y2=y[v[1]];
         x3=x[v[2]]; y3=y[v[2]];
         x4=x[v[3]]; y4=y[v[3]];
         if(x1==x3 && y1==y2 && x4-x3==x2-x1 && y4-y2==y3-y1 && y4-y2==x2-x1) goto ok;
         dy=y3-y1;
         if(x1+dy==x3 && y1==y2 && x4-x3==x2-x1 && y4-y2==y3-y1 && y4-y2==x4-x3) goto ok;
         if(x1==x2 && x3==x4 && y2==y3 && x3-x1==x4-x2 && y4-y3==x4-x2) goto ok;
      
      } else if(nv==6) {
         x1=x[v[0]]; y1=y[v[0]];
         x2=x[v[1]]; y2=y[v[1]];
         x3=x[v[2]]; y3=y[v[2]];
         x4=x[v[3]]; y4=y[v[3]];
         x5=x[v[4]]; y5=y[v[4]];
         x6=x[v[5]]; y6=y[v[5]];
         if(y1==y2 && y3==y4 && y5==y6 && x1==x3 && x2==x5 && x4==x6 && y3-y1==y6-y4) goto ok;
      }
      nv=0;
   ok:
      if(nv==3) printf("%s are the vertices of a triangle\n",s);
      else if(nv==4) printf("%s are the vertices of a parallelogram\n",s);
      else if(nv==6) printf("%s are the vertices of a hexagon\n",s);
      else printf("%s are not the vertices of an acceptable figure\n",s);
   }
}
