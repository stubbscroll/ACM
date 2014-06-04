/* faster than r.c, but not fast enough for hard input */

#include <stdio.h>
#include <string.h>
#include <math.h>

typedef long long ll;

int issq(int n) {
	int q;
	if((n&1)>1) return 0;
	q=sqrt(n);
	return q*q==n;
}

ll brute2(int n) {
	int i,j,k;
	ll r=0,z;
	for(i=0;i<n;i++) for(j=i;i*i+j*j<n*n;j++) for(k=j;i*i+j*j+k*k<n*n;k++) if(issq(i*i+j*j+k*k)) {
		z=1;
		if(i) z<<=1;
		if(j) z<<=1;
		if(k) z<<=1;
		if(i<j && j<k) z*=6;
		else if(i<j || j<k) z*=3;
		r+=z;
	}
	return r;
}

int main() {
	int cases,n;
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d",&n);
		printf("%I64d\n",brute2(n));
	}
	return 0;
}
