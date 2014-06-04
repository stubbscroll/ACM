#include <stdio.h>
#include <math.h>

int issq(int n) {
	int q;
	if((n&3)>1) return 0;
	q=(int)sqrt(n);
	return q*q==n;
}

int brute(int n) {
	int i,j,k,r=0;
	for(i=-n;i<=n;i++) for(j=-n;j<=n;j++) for(k=-n;k<=n;k++) {
		if(i*i+j*j+k*k>=n*n) continue;
		if(issq(i*i+j*j+k*k)) r++;
	}
	return r;
}

int main() {
	int cases,n;
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d",&n);
		printf("%d\n",brute(n));
	}
	return 0;
}
