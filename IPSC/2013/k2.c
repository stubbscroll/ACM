#include <stdio.h>
#include <string.h>
typedef long long ll;
#define MOD 1000000009
/* [i][k]
   at step i
   k: last step on way down was i-k */
int dp[100100][5];

void pre() {
	int i,k,a,v;
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for(i=0;i<100;i++) for(k=0;k<5;k++) if((v=dp[i][k])) {
		printf("dp %d %d: %d\n",i,k,v);
		for(a=1;a<3;a++) {
			/* go up and go down from the same step */
			dp[i+a][0]=(dp[i+a][0]+v)%MOD;
			/* go up and don't go down */
			if(k+a>4) continue;
			dp[i+a][k+a]=(dp[i+a][k+a]+v)%MOD;
		}
	}
}

int rec(int a,int b) {
	int r=0,i,j;
	if(a==1 && b==1) return 1;
	if(a==2 && b==1) return 1;
	if(a==2 && b==2) return 2;
	if(a<b) return 0;
	if(a<3) return 0;
	if(b<1) return 0;
	if(dp[a][b]>-1) return dp[a][b];
	/* go down 1 */
	if(b==1) r=((ll)r+rec(a-1,4)+rec(a-1,3)+rec(a-1,2)+rec(a-1,1))%MOD;
	else if(b==2) {
		r=(r+rec(a-1,b-1))%MOD;
		r=((ll)r+rec(a-2,4)+rec(a-2,3)+rec(a-2,2)+rec(a-2,1))%MOD;
	} else {
		r=((ll)r+rec(a-1,b-1)+rec(a-2,b-2))%MOD;
	}
	return dp[a][b]=r;
}

int main() {
	int T,a;
	memset(dp,-1,sizeof(dp));
	for(a=1;a<100000;a++) rec(a,1),rec(a,2),rec(a,3),rec(a,4);
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&a);
		printf("%I64d\n",((ll)rec(a,1)+rec(a,2)+rec(a,3)+rec(a,4))%MOD);
	}
	return 0;
}
