/* solution for divide the rectangle, hard input
   algorithm: first, reject if r*c is odd.
   then, add initial R and B. do a flood fill from R (filling in B on
   the other side of the diagonal accordingly), and only allow moves that
   don't disconnect the pieces.
   disconnection routine isn't very efficient, rendering the runtime as bad
   as O(r^2*c^2), but the hard input is nevertheless solved in 5.9 seconds. */

#include <stdio.h>

char g[111][111];
int r,c;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

/* search from given R and check if all R are reachable via R and space */
int disconnected(int cx,int cy) {
	static int q[22222];
	static char vis[111][111];
	int qs=0,qe=0,x2,y2,d,i,j;
	q[qe++]=cx; q[qe++]=cy;
	for(i=0;i<r;i++) for(j=0;j<c;j++) vis[i][j]=0;
	vis[cx][cy]=1;
	while(qs<qe) {
		cx=q[qs++]; cy=q[qs++];
		for(d=0;d<4;d++) {
			x2=cx+dx[d]; y2=cy+dy[d];
			if(x2<0 || y2<0 || x2>=r || y2>=c || vis[x2][y2] || g[x2][y2]=='B') continue;
			vis[x2][y2]=1;
			q[qe++]=x2; q[qe++]=y2;
		}
	}
	for(i=0;i<r;i++) for(j=0;j<c;j++) if(g[i][j]=='R' && !vis[i][j]) return 1;
	return 0;
}

int flood(int cx,int cy,int sx,int sy) {
	static int q[11111];
	int qs=0,qe=0,x2,y2,d;
	q[qe++]=cx; q[qe++]=cy;
	q[qe++]=sx; q[qe++]=sy;
	while(qs<qe) {
		cx=q[qs++]; cy=q[qs++];
		for(d=0;d<4;d++) {
			x2=cx+dx[d]; y2=cy+dy[d];
			if(x2<0 || y2<0 || x2>=r || y2>=c || g[x2][y2]) continue;
			g[x2][y2]='R';
			g[r-x2-1][c-y2-1]='B';
			if(disconnected(x2,y2)) {
				g[x2][y2]='B';
				g[r-x2-1][c-y2-1]='R';
				if(disconnected(r-x2-1,c-y2-1)) return 0;
			}
			q[qe++]=x2; q[qe++]=y2;
		}
	}
	return 1;
}

void solve() {
	int x1,y1,x2,y2,i,j;
	scanf("%d %d %d %d %d %d",&r,&c,&x1,&y1,&x2,&y2);
	if(r*c&1) { puts("IMPOSSIBLE\n"); return; }
	for(i=0;i<r;i++) for(j=0;j<=c;j++) g[i][j]=0;
	g[x1-1][y1-1]='R'; g[r-x1][c-y1]='B';
	g[x2-1][y2-1]='B'; g[r-x2][c-y2]='R';
	if(disconnected(x1-1,y1-1) || !flood(x1-1,y1-1,r-x2,c-y2)) { puts("IMPOSSIBLE\n"); return; }
	for(i=0;i<r;i++) puts(g[i]);
	putchar('\n');
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
