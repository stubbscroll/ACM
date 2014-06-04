#include <stdio.h>

/* turn number, highest card seen */
double dp[55][14];

double solve(int left,int high) {
	int i;
	double ans=0;
	if(left==0) return high;
	if(dp[left][high]>-10) return dp[left][high];
	for(i=1;i<14;i++) {
		ans+=solve(left-1,i)/13.;
	}
	return dp[left][high]=high>ans?high:ans;
}

int main() {
	int cases,turns,i,j;
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d",&turns);
		for(i=0;i<55;i++) for(j=0;j<14;j++) dp[i][j]=-100;
		printf("%.12f\n",solve(turns,0));
	}
	return 0;
}
