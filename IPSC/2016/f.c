#include <stdio.h>
#include <string.h>

int N,K;
int a[21];

int gs[200001];
int ferry[2][100000];

#define MAXV 200000
#define MAXE 400000
int n,ne;               /* number of nodes, number of edges */
int from[MAXE],to[MAXE];/* edge i: from[i] to[i] */
char ferge[MAXE];
int gs[MAXV+1];         /* gs[i]: start of edges from i, gs[i+1]: end */

char sol[1000000];
int solp;

int R(int p) {
	return 2*(p%N)+(p/N);
}

int L(int p) {
	return 2*(p%N)+(1-p/N);
}

int prev[MAXV];
char took[MAXV];
int q[MAXV],qs,qe;
char taken[MAXV];

char temp[250000];

void bfs(int start,int goal) {
	int i,cur,next,p;
	if(start==goal) return;
	for(i=0;i<n;i++) prev[i]=-1;
	for(i=0;i<n;i++) took[i]=taken[i]=0;
	qs=qe=0;
	q[qe++]=start;
	taken[start]=1;
	while(qs<qe) {
		cur=q[qs++];
		for(i=gs[cur];i<gs[cur+1];i++) {
			next=to[i];
			if(taken[next]) continue;
			taken[next]=1;
			prev[next]=cur;
			took[next]=ferge[i];
			q[qe++]=next;
			if(next==goal) goto end;
		}
	}
	printf("fail\n");
	return;
end:
	p=0;
	while(next!=start) {
		temp[p++]=took[next];
		next=prev[next];
	}
	while(--p>=0) sol[solp++]=temp[p];
}

/* subroutine: sort from[],to[] on increasing from[] */
/* (see maxflow-edge-general for a full radix sort which also sorts to[]) */
void countingsort() {
	static int newto[MAXE];
	static char newferge[MAXE];
	int i,j;
	for(i=0;i<=n;i++) gs[i]=0;
	for(i=0;i<ne;i++) gs[from[i]]++;
	for(i=1;i<n;i++) gs[i]+=gs[i-1];
	gs[n]=ne;
	for(i=0;i<ne;i++) {
		j=--gs[from[i]];
		newto[j]=to[i];
		newferge[j]=ferge[i];
	}
	for(i=0;i<ne;i++) to[i]=newto[i];
	for(i=0;i<ne;i++) ferge[i]=newferge[i];
	for(i=0;i<n;i++) for(j=gs[i];j<gs[i+1];j++) from[j]=i;
}

void solve() {
	int i;
	scanf("%d %d %d",&N,&a[0],&K);
	for(i=0;i<K;i++) scanf("%d",&a[i+1]);
	for(i=0;i<=K;i++) a[i]--;
	n=2*N;
	ne=0;
	/* create graph: L-ferry */
	for(i=0;i<n;i++) {
		from[ne]=i; to[ne]=L(i); ferge[ne++]='L';
	}
	/* create graph: R-ferry */
	for(i=0;i<n;i++) {
		from[ne]=i; to[ne]=R(i); ferge[ne++]='R';
	}
	countingsort();
	solp=0;
	for(i=0;i<K;i++) bfs(a[i],a[i+1]);
	sol[solp]=0;
	printf("%d:%s\n",(int)strlen(sol),sol);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
