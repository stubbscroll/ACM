/* solution for cake, both inputs
   algorithm: for each line, count the number of intersections against previous
   lines, and count regions (same approach as editorial, except i'm too lazy to
   use rational arithmetic) */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 3000
#define EPS 1e-8

typedef struct {
	int x1,y1,x2,y2;
} line_t;

line_t line[MAX];
int n;

typedef struct {
	double x,y;
} isect_t;

isect_t pt[MAX];
int pn;

int gcd(int a,int b) {
	return !b?a:gcd(b,a%b);
}

int compp(const void *A,const void *B) {
	const isect_t *a=A,*b=B;
	if(a->x<b->x) return -1;
	if(a->x>b->x) return 1;
	if(a->y<b->y) return -1;
	if(a->y>b->y) return 1;
	return 0;
}

/* 0: lines are parallel, 1:lines intersect, 2:lines are overlapping */
int linesintersect(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,
                   double *x,double *y) {
	int a1,a2,b1,b2,c1,c2;
	long long teller,nevner;
	a1=y2-y1; b1=x1-x2; c1=x2*y1-x1*y2;
	a2=y4-y3; b2=x3-x4; c2=x4*y3-x3*y4;
	nevner=a1*b2-a2*b1;
	if(!nevner) return 2;
	teller=(long long)b1*c2-(long long)b2*c1;
	*x=(double)teller/nevner;
	teller=(long long)a2*c1-(long long)a1*c2;
	*y=(double)teller/nevner;
	return 1;
}

int main() {
	int i,j,k,r=2;
	double x,y;
	scanf("%d",&n);
	if(n>MAX) { printf("increase MAX to %d\n",n); return 0; }
	for(i=0;i<n;i++) scanf("%d %d %d %d",&line[i].x1,&line[i].y1,&line[i].x2,&line[i].y2);
	for(i=1;i<n;i++) {
		for(pn=j=0;j<i;j++) {
			if(linesintersect(line[i].x1,line[i].y1,line[i].x2,line[i].y2,line[j].x1,line[j].y1,line[j].x2,line[j].y2,&x,&y)==1) {
				pt[pn].x=x; pt[pn++].y=y;
			}
		}
		qsort(pt,pn,sizeof(isect_t),compp);
		for(k=j=1;j<pn;j++) if(compp(pt+j-1,pt+j)) k++;
		r+=k+1;
	}
	printf("%d\n",r);
	return 0;
}
