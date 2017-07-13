/* solution for santo's bottles, both inputs
   algorithm: dp with state (number of bottles processed, drinking streak */

#include <stdio.h>
#include <string.h>

#define MAX 700

int dp[MAX+1][3]; /* at, bottles drunk in row */
int n;

int main() {
	int i,j,v,a;
	scanf("%d",&n);
	if(n>MAX) { printf("increase MAX to %d\n",n); return 0; }
	memset(dp,0,sizeof(dp));
	for(i=0;i<n;i++) {
		scanf("%d",&a);
		for(j=0;j<3;j++) {
			v=dp[i][j];
			if(j<2 && dp[i+1][j+1]<v+a) dp[i+1][j+1]=v+a;
			if(dp[i+1][0]<v) dp[i+1][0]=v;
		}
	}
	for(a=i=0;i<3;i++) if(a<dp[n][i]) a=dp[n][i];
	printf("%d\n",a);
	return 0;
}
