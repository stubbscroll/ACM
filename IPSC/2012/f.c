/* solution for fair coin toss, easy input
   fair subset exists iff the subset has a fair coin. */

#include <stdio.h>
#include <math.h>

int main() {
	int cases,i,n,y;
	double p;
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d",&n);
		for(y=i=0;i<n;i++) {
			scanf("%lf",&p);
			if(fabs(p-0.5)<1e-9) y=1;
		}
		puts(y?"1":"0");
	}
	return 0;
}
