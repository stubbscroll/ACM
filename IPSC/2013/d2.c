/* solution for do the grading, hard input
   algorithm: dp where the state is g(prefix length,subset of letters) and the
   associated value is the number of permutations of the subset missing in the
   prefix. to find the value of g(l,mask): take the sum of g(k,mask-letter)
   for each letter in mask; k is a prefix not longer than l that contains the
   last occurrence of letter in prefix. if no such prefix exists, use the base
   case which is (number of elements in mask-letter)!.
   hard input solved in 5437 seconds on a haswell laptop, requiring
   around 13.2 GB RAM.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MOD 65521
#define ALF 26

/* dp[i][mask]: number of missing permutations of subset of alphabet in mask
   mask in prefix of length i */
uint16_t *dp[101];

char s[111];
int n;
int fac[ALF+1];
int table[26][111];
int bc[1<<13];

void solve() {
	int i,j,mask,k,l;
	scanf("%s",s);
	n=strlen(s);
	/* create look-table for the following query: given prefix length and letter,
	   what's the length of the shortest prefix containing the last occurrence of
	   letter in the original prefix? */
	for(i=0;i<=n;i++) for(j=0;j<26;j++) {
		for(k=i-1;k>=0;k--) if(s[k]==j+'a') break;
		table[j][i]=k+1;
	}
	for(bc[0]=0,i=1;i<(1<<13);i++) bc[i]=bc[i>>1]+(i&1);
	for(fac[0]=1,i=1;i<=ALF;i++) fac[i]=(fac[i-1]*i)%MOD;
	/* base case 1: 0 missing permutations in empty set */
	for(i=0;i<=n;i++) dp[i][0]=0;
	/* base case 2: #mask! permutations missing in mask */
	for(mask=1;mask<(1<<ALF);mask++) {
		for(i=j=0;i<ALF;i++) if(mask&(1<<i)) j++;
		dp[0][mask]=fac[j];
	}
	for(i=1;i<=n;i++) for(mask=1;mask<(1<<ALF);mask++) {
		dp[i][mask]=0;
		for(j=0;j<ALF;j++) if(mask&(1<<j)) {
			k=table[j][i];
			if(k) dp[i][mask]=(dp[i][mask]+dp[k][mask-(1<<j)])%MOD;
			else {
				/* no prefix with letter j */
				l=bc[mask&8191]+bc[mask>>13];
				dp[i][mask]=(dp[i][mask]+fac[l-1])%MOD;
			}
		}
	}
	printf("%d\n",dp[n][(1<<ALF)-1]);
}

int main() {
	int T,i;
	for(i=0;i<101;i++) if(!(dp[i]=malloc(sizeof(uint16_t)<<ALF))) {
		printf("out of memory %d/101\n",i);
		return 0;
	}
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
