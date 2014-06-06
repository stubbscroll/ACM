/* solution for do the grading, easy input
   algorithm: dp where the state is a subset of letters, holding the length
   of the shortest prefix that contains all permutations of this subset.
   traverse by looping over bitmasks in ascending order. for each way of
   removing one letter from this subset, find the length of the shortest
   prefix that contains this permutation and the next occurrence of the
   missing letter. take the max of all these. if at any point the entire string
   cannot hold all permutations of a subset, we could prune and print NO
   outright, but my solution just propagates the no to the final dp state,
   wasting some time. my solution needs 727 seconds. */

#include <stdio.h>
#include <string.h>

#define INF 1000000

/* state: length of shortest suffix containing all permutations of mask as
   substrings */
int dp[1<<26];
/* given letter and index, return index after next occurrence of letter in
   string */
int pos[26][3000];
char s[3000];
int n;

void precalc() {
	int i,j,k;
	for(i=0;i<26;i++) for(j=0;j<n;j++) pos[i][j]=INF;
	for(i=0;i<26;i++) for(j=0;j<n;j++) {
		for(k=j;k<n;k++) if(s[k]==i+'a') {
			pos[i][j]=k+1;
			break;
		}
	}
}

void solve() {
	int mask,i,p;
	scanf("%s",s);
	n=strlen(s);
	precalc();
	dp[0]=0;
	for(mask=1;mask<(1<<26);mask++) {
		dp[mask]=0;
		for(i=0;i<26;i++) if(mask&(1<<i)) {
			if(dp[mask-(1<<i)]>=n) { dp[mask]=INF; break; }
			p=dp[mask-(1<<i)];
			if(dp[mask]<pos[i][p]) dp[mask]=pos[i][p];
		}
	}
	puts(dp[(1<<26)-1]<INF?"YES":"NO");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
