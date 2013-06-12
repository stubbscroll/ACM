#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int kx[20][100];	/*	convex hull of each kingdom */
int ky[20][100];
int knn[21];			/*	size of each kingdom */
int kn;						/*	number of kingdoms */

/*	convex hull! (for integer coordinates)
		input points in struct p, the resulting convex hull in struct h
		n:number of points in input, hn:number of points in output
		algorithm: graham's algorithm, sort O(n log n), convex hull O(n)
		note: input array is destroyed.
		algorithm seems to be robust against degenerate cases.
		source: computational geometry in c
*/

#define MAX 100

typedef struct { int x,y,del,id; } point;
typedef long long ll;

point p[MAX],h[MAX];
int n,hn;

ll area2(const point a,const point b,const point c) {
	return ((ll)b.x-a.x)*((ll)c.y-a.y)-((ll)c.x-a.x)*((ll)b.y-a.y);
}

/* accesses global p[0] */
int compp(const void *A,const void *B) {
	point *pi=(point *)A,*pj=(point *)B;
	ll a=area2(p[0],*pi,*pj),x,y;
	if(a>0) return -1;
	else if(a<0) return 1;
	else {
		x=llabs((ll)pi->x-p[0].x)-llabs((ll)pj->x-p[0].x);
		y=llabs((ll)pi->y-p[0].y)-llabs((ll)pj->y-p[0].y);
		if(x<0 || y<0) { pi->del=1; return -1; }
		else if(x>0 || y>0) { pj->del=1; return 1; }
		else {
			if(pi->id>pj->id) pj->del=1;
			else pi->del=1;
			return 0;
		}
	}
}

/* graham's algorithm for 2d convex hull, O(n log n) */
void convexhull() {
	int i,j,m=0;
	/* find lowest point, swap it to pos 0 */
	for(i=1;i<n;i++) if(p[i].y<p[m].y || (p[i].y==p[m].y && p[i].x>p[m].x)) m=i;
	for(i=0;i<n;i++) { p[i].del=0; p[i].id=i; }
	if(m) {
		i=p[0].x; p[0].x=p[m].x; p[m].x=i;
		i=p[0].y; p[0].y=p[m].y; p[m].y=i;
	}
	for(i=1;i<n;i++) if(p[i].y==p[0].y && p[i].x==p[0].x) p[i].del=1;
	/* leave pos 0 alone */
	if(n>2) qsort(p+1,n-1,sizeof(point),compp);
	/* remove deleted points */
	for(i=j=0;i<n;i++) if(!p[i].del) { if(i!=j) p[j]=p[i]; j++; }
	n=j;
	/* find convex hull */
	h[0]=p[0]; h[1]=p[1]; hn=i=2;
	if(n<3) { hn=n; return; }
	while(i<n) {
		if(area2(h[hn-2],h[hn-1],p[i])>0) h[hn++]=p[i++];
		else hn--;
	}
}

ll area2xy(int x1,int y1,int x2,int y2,int x3,int y3) {
	return ((ll)x2-x1)*((ll)y3-y1)-((ll)x3-x1)*((ll)y2-y1);
}

/*	check if px,py is strictly inside polygon */
int insidepoly(int *x,int *y,int n,int px,int py) {
	int i,j,in=0;
	for(j=n-1,i=0;i<n;j=i++) {
		if(py>y[j] && py<=y[i] && area2xy(x[j],y[j],x[i],y[i],px,py)>0) in^=1;
		else if(py>y[i] && py<=y[j] && area2xy(x[i],y[i],x[j],y[j],px,py)>0) in^=1;
	}
	return in;
}

/*	signed area*2 of polygon */
int polyarea2(int *x,int *y,int n) {
	int a=0,i,j;
	for(j=n-1,i=0;i<n;j=i++) a+=x[j]*y[i]-x[i]*y[j];
	return a;
}

char hit[100];

int main() {
	int i,xx,yy,ans,z;
	kn=0;
	while(scanf("%d",&n),n>-1) {
		for(i=0;i<n;i++) scanf("%d %d",&p[i].x,&p[i].y);
		convexhull();
		for(i=0;i<hn;i++) kx[kn][i]=h[i].x,ky[kn][i]=h[i].y;
		knn[kn++]=hn;
	}
	memset(hit,0,sizeof(hit));
	while(scanf("%d %d",&xx,&yy)==2) {
		for(i=0;i<kn;i++) if(insidepoly(kx[i],ky[i],knn[i],xx,yy)) { hit[i]=1; break; }
	}
	for(ans=i=0;i<kn;i++) if(hit[i]) {
		z=polyarea2(kx[i],ky[i],knn[i]);
		ans+=z<0?-z:z;
	}
	printf("%.2f\n",ans*.5);
	return 0;
}
