/* solution for partitioning a square, easy and hard input
   algorithm: find the smallest square by trial division (smallest k such
   that number of letters divides k*k), then write letters in a zig-zag pattern
   to avoid the possibility of disconnected regions */

#include <stdio.h>
#include <string.h>

char g[27][27];

void solve() {
	int n,k,l,x,y,at,c,i;
	scanf("%d",&n);
	/* find smallest square size */
	for(k=1;;k++) if(k*k%n==0) break;
	l=k*k/n;
	/* square size k*k, n different letters, each letter occurring l times */
	x=y=at=0;
	for(i=0;i<k;i++) g[i][k]=0;
	while(at<n) {
		for(c=0;c<l;c++) {
			g[x][y]='a'+at;
			if(y&1) {
				if(--x<0) x++,y++;
			} else {
				if(++x==k) x--,y++;
			}
		}
		at++;
	}
	printf("%d\n",k);
	for(i=0;i<k;i++) puts(g[i]);
	puts("");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
