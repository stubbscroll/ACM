/* solution for rain, both inputs
   algorithm: binary search on the length of the sequence. test a length by
   checking all intervals of given length and check if it is larger than M.
   use cumulative sums to check a given interval in constant time.
   total runtime O(N log M) */

#include <stdio.h>

#define MAX 1344521

int s[MAX+1],t[MAX+1],N,M;
long long c[MAX+1];

void solve() {
	int i,lo,mid,hi;
	scanf("%d %d %d %d",&s[0],&t[0],&N,&M);
	if(N>MAX) printf("increase MAX to %d\n",N);
	for(c[0]=0,i=1;i<=N;i++) {
		s[i]=(78901+31*s[i-1])%699037;
		t[i]=(23456+64*t[i-1])%2097151;
		c[i]=c[i-1]+(s[i]%100+1)*(t[i]%100+1);
	}
	lo=0; hi=N+1;
	/* find lowest length that has subsequence with greater sum than M */
	while(lo<hi) {
		mid=lo+(hi-lo)/2;
		for(i=0;i<N-mid;i++) if(c[i+mid]-c[i]>M) { hi=mid; goto end; }
		lo=mid+1;
	end:;
	}
	printf("%d\n",lo-1);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
