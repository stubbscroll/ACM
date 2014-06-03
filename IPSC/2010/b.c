#include <stdio.h>
#include <math.h>

int ax,ay,bx,by;
double p,q,r;
double ans;

double ABS(double a) { return a<0?-a:a; }
double MIN(double a,double b) { return a<b?a:b; }

double enter(double x1,double y1,double x2,double y2) {
	double res1=ABS(x1-ax)+ABS(y1-ay),res2=ABS(x2-bx)+ABS(y2-by);
	double dx=x2-x1,dy=y2-y1;
	double line=sqrt(dx*dx+dy*dy);
	return res1+res2+line;
}

int main() {
	int cases;
	double x1,y1,x2,y2;
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d %d %d %d %lf %lf %lf",&ax,&ay,&bx,&by,&p,&q,&r);
		ans=ABS(ax-bx)+ABS(ay-by);
		if(p!=0 && q!=0) {
			/* enter at ax, bx */
			x1=ax; y1=(r-p*x1)/q;
			x2=bx; y2=(r-p*x2)/q;
			ans=MIN(ans,enter(x1,y1,x2,y2));
			/* enter at ax, by */
			x1=ax; y1=(r-p*x1)/q;
			y2=by; x2=(r-q*y2)/p;
			ans=MIN(ans,enter(x1,y1,x2,y2));
			/* enter at ay, bx */
			y1=ay; x1=(r-q*y1)/p;
			x2=bx; y2=(r-p*x2)/q;
			ans=MIN(ans,enter(x1,y1,x2,y2));
			/* enter at ay, by */
			y1=ay; x1=(r-q*y1)/p;
			y2=by; x2=(r-q*y2)/p;
			ans=MIN(ans,enter(x1,y1,x2,y2));
		}
		printf("%.14f\n",ans);
	}
	return 0;
}
