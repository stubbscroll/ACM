#include <stdio.h>

int r,c;
char cols[2],col;
char m[133][133];
int pathr[55555],pathc[55555],colnum;

int dx[]={1,1,-1,-1};
int dy[]={1,-1,1,-1};

int btr(int x,int y,int at) {
	int d,x2,y2;
	m[x][y]=1;
	pathr[at]=x; pathc[at]=y;
	if(at==colnum-1) return 1;
	for(d=0;d<4;d++) {
		x2=x+dx[d]; y2=y+dy[d];
		if(x2<0 || y2<0 || x2>=r || y2>=c || m[x2][y2]) continue;
		if(btr(x2,y2,at+1)) return 1;
	}
	return m[x][y]=0;
}

void solve() {
	int i,j,k;
	scanf("%d %d %s",&r,&c,cols);
	col=cols[0];
	colnum=0;
	for(i=0;i<r;i++) for(j=0;j<c;j++) {
		k=(i+j)&1;
		colnum+=(k==(col=='B'));
	}
	for(i=0;i<r;i++) for(j=0;j<c;j++) m[i][j]=0;
	for(i=0;i<r;i++) for(j=0;j<c;j++) if(((i+j)&1)==(col=='B')) {
		if(btr(i,j,0)) goto ok;
	}
	puts("impossible\n");
	return;
ok:
	for(i=0;i<colnum;i++) printf("%d %d\n",pathr[i]+1,pathc[i]+1);
	putchar('\n');
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
