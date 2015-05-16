/* solution for panel, easy input
   algorithm: try all ways to flip switches, 2^2n = 2^20 ways,
   runtime O(2^2n*n^2)
*/

#include <stdio.h>

#define MAX 10
int a[MAX][MAX];
int best[MAX][MAX];
int cur[MAX][MAX];

int main() {
	int n,i,j,x,y,r,z;
	scanf("%d",&n);
	if(n>MAX) { printf("increase MAX to %d\n",n); return 0; }
	for(i=0;i<n;i++) for(j=0;j<n;j++) scanf("%d",&a[i][j]);
	for(r=n*n,x=0;x<(1<<n);x++) for(y=0;y<(1<<n);y++) {
		for(z=i=0;i<n;i++) for(j=0;j<n;j++) z+=cur[i][j]=a[i][j]^((x&(1<<i))>0)^((y&(1<<j))>0);
		if(r>z) for(r=z,i=0;i<n;i++) for(j=0;j<n;j++) best[i][j]=cur[i][j];
	}
	printf("%d\n",r);
	for(i=0;i<n;i++) for(j=0;j<n;j++) printf("%d%c",best[i][j],j==n-1?'\n':' ');
	return 0;
}
