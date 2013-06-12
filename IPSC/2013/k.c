#include <stdio.h>
#define MAX 1000000
int dp[MAX];
int dq[MAX];
#define MOD 1000000009
typedef long long ll;
void pre() {
	int i;
	dp[0]=1;
	dq[0]=1;
	dq[1]=1;
	dp[1]=1;
	/* up */
	for(i=2;i<MAX;i++) {
		dp[i]=(dp[i-1]+dp[i-2])%MOD;
	}
	/* down */
	for(i=2;i<MAX;i++) {
		dq[i]=(dq[i-1]+dq[i-2])%MOD;
		if(i>2) dq[i]=(dq[i]+dq[i-3])%MOD;
		if(i>3) dq[i]=(dq[i]+dq[i-4])%MOD;
	}
}

int main() {
	int T,a;
	pre();
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&a);
		printf("%I64d\n",(ll)dp[a]*dq[a]%MOD);
	}
	return 0;
}