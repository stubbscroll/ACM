/* solution for inventing test data, both inputs
   algorithm: stolen from editorial */

#include <stdio.h>
#include <stdlib.h>

#define MAXV 15000

#define MAXSET MAXV

int p[MAXSET],rank[MAXSET];

int findset(int x) {
	if(x!=p[x]) p[x]=findset(p[x]);
	return p[x];
}

void unionset(int x,int y) {
	x=findset(x);
	y=findset(y);
	if(x==y) return;
	if(rank[x]>rank[y]) p[y]=x;
	else {
		p[x]=y;
		if(rank[x]==rank[y]) rank[y]++;
	}
}

void initset(int n) {
	int i;
	for(i=0;i<n;i++) { p[i]=i; rank[i]=0; }
}

int g[MAXV][MAXV];
int n;

typedef struct {
	int from,to,cost;
} e_t;

e_t e[MAXV];
int ne;

int compe(const void *A,const void *B) {
	const e_t *a=A,*b=B;
	if(a->cost<b->cost) return -1;
	if(a->cost>b->cost) return 1;
	return 0;
}

void solve() {
	int i,j,k,a,b,c,x,y;
	long long r=0;
	scanf("%d",&n);
	ne=n-1;
	for(i=0;i<n;i++) for(j=0;j<n;j++) g[i][j]=0;
	initset(n);
	for(i=0;i<ne;i++) {
		scanf("%d %d %d",&a,&b,&c);
		a--; b--;
		e[i].from=a; e[i].to=b; e[i].cost=c;
		g[a][b]=g[b][a]=c;
		r+=c;
	}
	qsort(e,ne,sizeof(e_t),compe);
	for(i=0;i<ne;i++) {
		a=e[i].from; b=e[i].to;
		x=findset(a); y=findset(b);
		for(j=0;j<n;j++) if(findset(j)==x) for(k=0;k<n;k++) if(findset(k)==y) {
			if(j==a && k==b) continue;
			if(j==b && k==a) continue;
			r+=e[i].cost+1;
		}
		unionset(a,b);
	}
	printf("%I64d\n",r);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
