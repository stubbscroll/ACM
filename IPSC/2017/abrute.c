/* try all 2^(r*c) combinations, simulate flooding, take the combination with
   fewest clicks */

#include <stdio.h>

int r,c;
int bestnum;

char m[100][100];
char best[100][100];

char grid[100][100];

int get(int x,int y) {
	if(x<0 || y<0 || x>=r || y>=c) return 0;
	return grid[x][y];
}

int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

int sim() {
	int i,j,d,cnt;
	char changed;
	for(i=0;i<r;i++) for(j=0;j<c;j++) grid[i][j]=m[i][j];
	do {
		changed=0;
		for(i=0;i<r;i++) for(j=0;j<c;j++) if(!grid[i][j]) {
			for(cnt=d=0;d<4;d++) cnt+=get(i+dx[d],j+dy[d]);
			if(cnt>=2) grid[i][j]=changed=1;
		}
	} while(changed);
	for(i=0;i<r;i++) for(j=0;j<c;j++) if(!grid[i][j]) return 0;
	return 1;
}

void solve() {
	long long mask;
	int i,j,bc;
	scanf("%d %d",&r,&c);
	bestnum=65;
	for(mask=0;mask<(1LL<<(r*c));mask++) {
		bc=0;
		for(i=0;i<r*c;i++) bc+=m[i/c][i%c]=(mask&(1LL<<i))?1:0;
		if(bc>=bestnum) continue;
		if(sim()) {
			bestnum=bc;
			for(i=0;i<r;i++) for(j=0;j<c;j++) best[i][j]=m[i][j];
		}
	}
	printf("%d\n",bestnum);
	for(i=0;i<r;i++) for(j=0;j<c;j++) if(best[i][j]) printf("%d %d\n",i,j);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
