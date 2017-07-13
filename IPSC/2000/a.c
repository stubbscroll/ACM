/* solution for k-in-a-row, both inputs
   algorithm: check every coordinate for k-in-a-row in every direction */

#include <stdio.h>

char g[200][201];
int m,n,k;
int w1,w2;
int dx[]={1,1,1,0};
int dy[]={1,0,-1,-1};

int ok(int x,int y,int d,char z) {
	int i;
	for(i=0;i<k;i++) {
		if(x<0 || y<0 || x>=n || y>=m || g[x][y]!=z) return 0;
		x+=dx[d]; y+=dy[d];
	}
	return 1;
}

void solve() {
	int i,j,d;
	scanf("%d %d %d",&m,&n,&k);
	for(i=0;i<n;i++) scanf("%s",g[i]);
	for(i=0;i<n;i++) for(j=0;j<m;j++) for(d=0;d<4;d++) {
		if(ok(i,j,d,'x')) { w1++; return; }
		if(ok(i,j,d,'o')) { w2++; return; }
	}
}

int main() {
	int L;
	w1=w2=0;
	scanf("%d",&L);
	while(L--) solve();
	printf("%d:%d\n",w1,w2);
	return 0;
}
