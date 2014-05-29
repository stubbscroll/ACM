/* solution for hard question - p=np?, both inputs
   algorithm: interval compression, convert to explicit representation
   and check if stuff overlaps correctly */

#include <stdio.h>
#include <string.h>

#define MAXV 1200
#define MAX 7000
#define MAXP 2500

#define MAXX 200000

#define INF 1000000000

char g[MAX][MAX];
char h[MAX][MAX];

int px[MAXV],py[MAXV];
int n,m;
int rx1[MAXP],ry1[MAXP],rx2[MAXP],ry2[MAXP];

int ixx[MAXX],ixy[MAXX];
int nx,ny;

int q[MAXP*MAXP*2],qs,qe;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

void flood(int sx,int sy) {
	int cx,cy,x2,y2,d;
	qs=qe=0;
	q[qe++]=sx; q[qe++]=sy; g[sx][sy]=1;
	while(qs<qe) {
		cx=q[qs++]; cy=q[qs++];
		for(d=0;d<4;d++) {
			x2=cx+dx[d]; y2=cy+dy[d];
			/* do we pass a wall? */
			if(x2<0 || y2<0 || x2>=MAX || y2>=MAX || g[x2][y2]) continue;
			x2+=dx[d]; y2+=dy[d];
			if(x2<0 || y2<0 || x2>=MAX || y2>=MAX || g[x2][y2]) continue;
			g[x2][y2]=1;
			q[qe++]=x2; q[qe++]=y2;
		}
	}
}

int solve() {
	int i,j,minx,miny,x1,y1,x2,y2,t,k;
	scanf("%d %d",&n,&m);
	if(!(n+m)) return 0;
	if(n>MAXV) { puts("increase MAXV and recompile"); return 0; }
	if(m>MAXP) { puts("increase MAXP and recompile"); return 0; }
	for(i=0;i<n;i++) scanf("%d %d",&px[i],&py[i]);
	for(i=0;i<m;i++) scanf("%d %d %d %d",&rx1[i],&ry1[i],&rx2[i],&ry2[i]);
	for(minx=miny=INF,i=0;i<n;i++) {
		if(minx>px[i]) minx=px[i];
		if(miny>py[i]) miny=py[i];
	}
	for(i=0;i<n;i++) px[i]-=minx,py[i]-=miny;
	for(i=0;i<m;i++) rx1[i]-=minx,rx2[i]-=minx,ry1[i]-=miny,ry2[i]-=miny;
	/* interval compression */
	for(i=0;i<MAXX;i++) ixx[i]=ixy[i]=-1;
	for(i=0;i<n;i++) {
		if(px[i]>=MAXX || py[i]>=MAXX) { puts("increase MAXX and recompile"); return 0; }
		ixx[px[i]]=ixy[py[i]]=0;
	}
	for(i=0;i<m;i++) {
		if(rx1[i]>=MAXX || ry1[i]>=MAXX || rx2[i]>=MAXX || ry2[i]>=MAXX) { puts("increase MAXX and recompile"); return 0; }
		ixx[rx1[i]]=ixy[ry1[i]]=ixx[rx2[i]]=ixy[ry2[i]]=0;
	}
	for(nx=ny=i=0;i<MAXX;i++) {
		if(ixx[i]>-1) ixx[i]=nx++;
		if(ixy[i]>-1) ixy[i]=ny++;
	}
	if(nx*2>=MAX || ny*2>=MAX) { puts("increase MAX and recompile"); return 0; }
	for(i=0;i<n;i++) {
		px[i]=ixx[px[i]];
		py[i]=ixy[py[i]];
	}
	for(i=0;i<m;i++) {
		rx1[i]=ixx[rx1[i]];
		ry1[i]=ixy[ry1[i]];
		rx2[i]=ixx[rx2[i]];
		ry2[i]=ixy[ry2[i]];
	}
	/* construct polynomial in grid */
	memset(g,0,sizeof(g));
	for(i=0;i<n;i++) {
		x1=px[i]; y1=py[i];
		x2=px[(i+1)%n]; y2=py[(i+1)%n];
		if(x1>x2) t=x1,x1=x2,x2=t;
		if(y1>y2) t=y1,y1=y2,y2=t;
		if(x1==x2) {
			for(j=y1*2+1;j<y2*2;j++) g[x1*2][j]=1;
		} else if(y1==y2) {
			for(j=x1*2+1;j<x2*2;j++) g[j][y1*2]=1;
		} else {
			/* NP contains a diagonal line, insta-reject */
			puts("NO");
			return 1;
		}
	}
	/* flood fill NP */
	for(i=0;i<MAXV-1;i++) for(j=0;j<MAXV-1;j++) if(g[i][j+1] && g[i+1][j]) {
		flood(i+1,j+1);
		goto out;
	}
out:
	/* fill rectangles in another grid */
	memset(h,0,sizeof(h));
	for(i=0;i<m;i++) {
		x1=rx1[i]; y1=ry1[i];
		x2=rx2[i]; y2=ry2[i];
		if(x1>x2) t=x1,x1=x2,x2=t;
		if(y1>y2) t=y1,y1=y2,y2=t;
		/* check if part of rectangle is outside of NP */
		for(j=x1*2+1;j<x2*2;j+=2) for(k=y1*2+1;k<y2*2;k+=2) if(!g[j][k]) {
			/* destroy rectangle */
			rx1[i]=-1;
			goto next;
		}
		for(j=x1*2+1;j<x2*2;j+=2) for(k=y1*2+1;k<y2*2;k+=2) h[j][k]=1;
	next:;
	}
	/* check if there are cells in NP that aren't covered by P */
	for(i=1;i<nx*2;i+=2) for(j=1;j<ny*2;j+=2) if(g[i][j] && !h[i][j]) {
		puts("NO");
		return 1;
	}
	/* since P is disjoint, we are done */
	puts("YES");
	return 1;
}

int main() {
	while(solve());
	return 0;
}
