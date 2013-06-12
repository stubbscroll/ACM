#include <stdio.h>
#include <string.h>
#include <math.h>
typedef long long ll;
#define Z 100000000
ll dp[Z];
void fill() {
	int q,x,y,a;
	dp[1]=0;
	for(a=2;a<Z;a++) {
		q=sqrt(a);
		if(q*q!=a) q++;
		x=a/q; y=a-a/q;
		dp[a]=(ll)x*y+dp[x]+dp[y];
	}
}
ll split(int a) {
	int q=sqrt(a),x,y;
	ll r=0;
again:
	if(a<Z && dp[a]>-1) return dp[a];
	if(q*q!=a) q++;
	x=a/q; y=a-a/q;
	if(a==1) return 0;
	r+=(ll)x*y+split(x);
	if(y<Z) return r+split(y);
	a=y;
	goto again;
}
int main() {
	int T,a;
	scanf("%d",&T);
	memset(dp,-1,sizeof(dp));
	fill();
	while(T--) {
		scanf("%d",&a);
		printf("%I64d\n",split(a));
	}
	return 0;
}
