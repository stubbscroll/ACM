/* solution to arranging flowers, easy input
   algorithm: backtracking */

#include <stdio.h>
#include <string.h>

#define MAX 300

int grid[MAX][MAX];    /* [i][j]: i row j column */
char taken[MAX][MAX];  /* taken[i][j]: column i number j is taken */
int n,m;

char t[MAX];

int btr(int row,int col) {
	int i;
	if(col==n) {
		col=0;
		row++;
		if(row==n) return 1;
	}
	if(!col) memset(t,0,n);
	for(i=0;i<n;i++) if(!t[i] && !taken[col][i]) {
		t[i]=taken[col][i]=1;
		grid[row][col]=i;
		if(btr(row,col+1)) return 1;
		t[i]=taken[col][i]=0;
	}
	return 0;
}

void solve() {
	int i,j;
	scanf("%d %d",&n,&m);
	for(i=0;i<n;i++) for(j=0;j<n;j++) taken[i][j]=0;
	for(i=0;i<m;i++) {
		for(j=0;j<n;j++) {
			scanf("%d",&grid[i][j]);
			grid[i][j]--;
			taken[j][grid[i][j]]=1;
		}
	}
	btr(m,0);
	printf("%d\n",n-m);
	for(i=m;i<n;i++) {
		for(j=0;j<n;j++) printf("%d ",grid[i][j]+1);
		printf("\n");
	}
	printf("\n");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
