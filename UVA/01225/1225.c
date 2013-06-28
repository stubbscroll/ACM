#include <stdio.h>
#include <string.h>

int a[10001][10];

int main() {
	int T,i,n;
	memset(a,0,sizeof(a));
	for(i=1;i<10001;i++) {
		for(n=0;n<10;n++) a[i][n]=a[i-1][n];
		for(n=i;n;n/=10) a[i][n%10]++;
	}
	scanf("%d",&T);
	while(T--) scanf("%d",&n),printf("%d %d %d %d %d %d %d %d %d %d\n",
		a[n][0],a[n][1],a[n][2],a[n][3],a[n][4],a[n][5],a[n][6],a[n][7],a[n][8],a[n][9]);
	return 0;
}
