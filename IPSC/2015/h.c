/* solution for humble captains, easy input
   algorithm: try all ways of assigning teams, using bitmasks, and for each
   assignment, evaluate both scores and update best as we go.
   time complexity: O(2^n*n^2) */

#include <stdio.h>
#include <string.h>

#define MAX 200

int g[MAX][MAX];
int n;

void solve() {
	int m,i,j,a,b,mask,best1,best2,c;
	memset(g,0,sizeof(g));
	scanf("%d %d",&n,&m);
	for(i=0;i<m;i++) {
		scanf("%d %d",&a,&b);
		a--; b--;
		g[a][b]=g[b][a]=1;
	}
	best1=-1;
	best2=1232132131;
	for(mask=2;mask<(1<<n);mask+=4) {
		a=b=0;
		for(i=0;i<n;i++) for(j=i+1;j<n;j++) if(g[i][j]) {
			if((mask&(1<<i)) && (mask&(1<<j))) b++;
			if(!(mask&(1<<i)) && !(mask&(1<<j))) a++;
		}
		c=a-b>0?a-b:b-a;
		if(best1<a+b) best1=a+b;
		if(best2>c) best2=c;
	}
	printf("%d %d\n",best1,best2);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
