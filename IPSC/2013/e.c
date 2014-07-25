/* solution for exploring the cave, easy input
   algorithm: as suggested by the editorial, generate random caves
   and throw away until we get one with d states. count the number of
   states using bfs with bitmasks.
   this solution took 26 seconds. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 22

char g[MAX][MAX];
int n,d;

int can(double p) {
	int r=rand()&32767;
	return r>=p*32768;
}

void randgraph() {
	double d=rand()%1000*.001;
	int i,j;
	for(i=0;i<n;i++) for(j=0;j<n;j++) g[i][j]=can(d)+can(d)*2+can(d)*4;
}

char vis[1<<MAX];
int q[1<<MAX],qs,qe;

int count() {
	int r=1,cur,next,i,j,a;
	qs=qe=0;
	memset(vis,0,1<<n);
	q[qe++]=1;
	vis[1]=1;
	while(qs<qe) {
		cur=q[qs++];
		for(a=0;a<3;a++) {
			next=0;
			for(i=0;i<n;i++) if(cur&(1<<i)) for(j=0;j<n;j++) if(g[i][j]&(1<<a)) next|=1<<j;
			if(vis[next]) continue;
			r++;
			vis[next]=1;
			q[qe++]=next;
		}
	}
	return r;
}

int bc[]={0,1,1,2,1,2,2,3};

void solve() {
	int i,j,k,ne;
	scanf("%d %d",&n,&d);
	if(d>(1<<n)) { puts("-1"); return; }
	do randgraph(); while(count()!=d);
	for(ne=i=0;i<n;i++) for(j=0;j<n;j++) ne+=bc[(int)g[i][j]];
	printf("%d\n",ne);
	for(i=0;i<n;i++) for(j=0;j<n;j++) for(k=0;k<3;k++) if(g[i][j]&(1<<k)) printf("%d %d %c\n",i,j,k+'a');
	printf("\n");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
