/* solution for breaking in
   algorithm: count the number of reachable nodes from each node in
   research graph with bfs. runtime O(ne) */

#include <stdio.h>
#include <string.h>

#define MAXE 1000000
#define MAXV 10000
#define INF 1000000000

int from[MAXE],to[MAXE];  /* graph */
int gs[MAXV+1];           /* pointer to first node */
int num[MAXV];
int n,ne;

void countingsort() {
	static int newto[MAXE];
	int i,j;
	for(i=0;i<=n;i++) gs[i]=0;
	for(i=0;i<ne;i++) gs[from[i]]++;
	for(i=1;i<n;i++) gs[i]+=gs[i-1];
	gs[n]=ne;
	for(i=0;i<ne;i++) {
		j=--gs[from[i]];
		newto[j]=to[i];
	}
	for(i=0;i<ne;i++) to[i]=newto[i];
	for(i=0;i<n;i++) for(j=gs[i];j<gs[i+1];j++) from[j]=i;
}

int try(int cur) {
	static char vis[MAXV];
	static int q[MAXV];
	int qs=0,qe=0,next,i;
	for(i=0;i<n;i++) vis[i]=0;
	q[qe++]=cur;
	vis[cur]=1;
	while(qs<qe) {
		cur=q[qs++];
		for(i=gs[cur];i<gs[cur+1];i++) {
			next=to[i];
			if(vis[next]) continue;
			vis[next]=1;
			q[qe++]=next;
		}
	}
	return qe;
}

void solve() {
	int i,best;
	scanf("%d %d",&n,&ne);
	for(i=0;i<ne;i++) scanf("%d %d",&to[i],&from[i]),from[i]--,to[i]--;
	countingsort();
	for(i=0;i<n;i++) num[i]=try(i);
	for(best=-1,i=0;i<n;i++) if(best<num[i]) best=num[i];
	for(i=0;i<n;i++) if(best==num[i]) printf("%d ",i+1);
	putchar('\n');
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
