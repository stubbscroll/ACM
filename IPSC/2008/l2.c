/* solution for large party, hard input
   algorithm: combinatorics
   - calculate all eligible combinations of length N, then divide by N (since
     we counted all rotations)
   - however, we only counted each bitpattern once. for N=4 K=1, we would need
     4 copies of 0101 so that the division is correct, but we only counted
     0101 and 1010. remedy by going through each divisor of N and for every
     divisor d, count N/d-1 sequences of length d. however, if we have two
     divisors d,e where e divides d, we end up counting some sequences
     too many times. therefore, for e, multiply by N/e-1-v where v is the
     number we subtracted for d. actually, v is the sum for all d such that
     e is a divisor of d and d is a divisor of n.
   runtime: O(nk) */

#include <stdio.h>

#define MOD 100000007
#define MAX 965

typedef long long ll;

int n,k;
ll dp[MAX][MAX]; /* dp: position, number of women in a row */

/* calculate dp array. first entry is ALWAYS a man to avoid a cyclic
   woman streak */
void calcdp() {
	ll v;
	int i,j;
	for(i=0;i<n;i++) for(j=0;j<n;j++) dp[i][j]=0;
	dp[0][0]=1;
	for(i=0;i<n;i++) for(j=0;j<n;j++) if((v=dp[i][j])) {
		/* man */
		dp[i+1][0]=(dp[i+1][0]+v)%((ll)MOD*n);
		/* woman */
		if(j<k) dp[i+1][j+1]=(dp[i+1][j+1]+v)%((ll)MOD*n);
	}
}

/* return all combinations of length len, including rotations */
ll calclen(int len) {
	ll r=0;
	int i,j;
	for(i=0;i<=k && i<len;i++) for(j=0;j<=k-i && j<len;j++) r=(r+dp[len-i-1][j])%((ll)MOD*n);
	return r;
}

void solve() {
	ll r;
	int i,j;
	int divs[MAX];
	scanf("%d %d",&n,&k);
	if(k>n) k=n;
	calcdp();
	r=calclen(n);
	for(i=1;i<n;i++) if(n%i==0) divs[i]=n/i-1;
	for(i=n-1;i;i--) if(n%i==0) for(j=i-1;j;j--) if(i%j==0) divs[j]-=divs[i];
	for(i=1;i<n;i++) if(n%i==0) r=(r+divs[i]*calclen(i))%((ll)MOD*n);
	if(n==k) r+=n;
	printf("%I64d\n",r/n);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
