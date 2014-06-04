/* solution to fair coin toss, hard input.
   algorithm: use standard combinatorics to count the number of
   subsets that contains a fair coin.
   this problem has the interesting property that the program that
   solves the hard input also solves the easy one. */

#include <stdio.h>
#include <math.h>

typedef long long ll;

ll pascal[64][64];

void gen() {
	int i,j;
	for(i=0;i<64;i++) {
		pascal[i][0]=pascal[i][i]=1;
		for(j=1;j<i;j++) pascal[i][j]=pascal[i-1][j-1]+pascal[i-1][j];
	}
}

double p[64];
int n;

ll fast() {
	int half=0,i;
	ll r=0;
	for(i=0;i<n;i++) if(fabs(.5-p[i])<1e-8) half++;
	for(i=1;i<=half;i++) {
		/* (half choose i) ways to choose i fair coins */
		/* 2^(n-half) ways to choose any additional biased coins */
		r+=pascal[half][i]*(1LL<<(n-half));
	}
	return r;
}

int main() {
	int cases;
	int i;
	gen();
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d",&n);
		for(i=0;i<n;i++) scanf("%lf",&p[i]);
		printf("%I64d\n",fast());
	}
	return 0;
}
