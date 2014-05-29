/* solution to calls, both inputs.
   algorithm is stolen from editorial */

#include <stdio.h>

#define MAXV 300
#define INF 1000000000

int n,ne,nf;
int g[MAXV][MAXV];
int c[MAXV][MAXV];
char taken[MAXV][MAXV];

int dijkstra(int start,int goal) {
	static int dist[MAXV];
	static char vis[MAXV];
	int i,ix,best;
	for(i=0;i<n;i++) dist[i]=(i==start)?0:INF,vis[i]=0;
	while(1) {
		for(best=INF,ix=-1,i=0;i<n;i++) if(!vis[i] && best>dist[i]) best=dist[i],ix=i;
		if(ix<0) return INF;
		if(goal==ix) return best;
		vis[ix]=1;
		for(i=0;i<n;i++) if(dist[i]>dist[ix]+g[ix][i]) dist[i]=dist[ix]+g[ix][i];
	}
}

int solve() {
	int i,j,ix,iy,best,d;
	scanf("%d %d",&n,&ne);
	if(n>MAXV) { printf("increase MAXV to %d\n",n); return 0; }
	for(i=0;i<n;i++) for(j=i+1;j<n;j++) scanf("%d",&c[i][j]),c[j][i]=c[i][j];
	if(ne>n*(n-1)/2) return 0;
	for(i=0;i<n;i++) c[i][i]=0;
	for(i=0;i<n;i++) for(j=0;j<n;j++) taken[i][j]=0,g[i][j]=i==j?0:INF;
	for(nf=0;;) {
		ix=iy=-1; best=INF;
		for(i=0;i<n;i++) for(j=i+1;j<n;j++) if(!taken[i][j] && best>c[i][j]) best=c[i][j],ix=i,iy=j;
		if(ix<0) return 1;
		taken[ix][iy]=taken[iy][ix]=1;
		d=dijkstra(ix,iy);
		if(d<c[ix][iy]) return 0;
		if(d>c[ix][iy]) {
			g[ix][iy]=g[iy][ix]=c[ix][iy];
			nf++;
			if(nf>ne) return 0;
		}
	}
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) printf("%s\n",solve()?"YES":"NO");
	return 0;
}
