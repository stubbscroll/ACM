/* solution for divide the rectangle, easy input
   observation: impossible iff r*c is odd.
   algorithm: for each R added, add a B reflected along the diagonal
   (and vice versa) */

#include <stdio.h>

char g[111][111];
int r,c;

void solve() {
	int x1,y1,x2,y2,i,j;
	scanf("%d %d %d %d %d %d",&r,&c,&x1,&y1,&x2,&y2);
	if(r*c&1) { puts("IMPOSSIBLE\n"); return; }
	for(i=0;i<r;i++) for(j=0;j<=c;j++) g[i][j]=0;
	g[x1-1][y1-1]='R'; g[r-x1][c-y1]='B';
	g[x2-1][y2-1]='B'; g[r-x2][c-y2]='R';
	for(i=0;i<r;i++) for(j=0;j<c;j++) if(!g[i][j]) g[i][j]='R',g[r-i-1][c-j-1]='B';
	for(i=0;i<r;i++) puts(g[i]);
	putchar('\n');
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
