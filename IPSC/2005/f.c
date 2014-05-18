/* solution to find the right words, both inputs
   algorithm: min-cost maxflow.
   solves easy instantly, needs 138 seconds on hard.
	 graphs are large on hard, needs around 1.3 gb.
   min-cost bipartite matching would certainly be faster than
   general maxflow for hard */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXW 100000
#define MAXS 24
#define MAXSTR 1500

typedef long long ll;

#define MAXV 100000
#define MAXE 100000000
#define INF 1000000000

int *from,*to;            /* graph */
int gs[MAXV+1];           /* pointer to first node */
int *f;                   /* flow/capacity/residual graph */
int *cost;                /* cost per flow unit */
int *inv;                 /* index to reverse edge */
int n,ne;                 /* number of nodes, edges */

int prev[MAXV],dist[MAXV],q[MAXE];

int augment(int source,int sink) {
	static char vis[MAXV];
	int cur,ix,i,qs,qe;
	memset(vis,0,n);
	memset(dist,120,sizeof(int)*n);
	memset(prev,-1,sizeof(int)*n);
	dist[source]=qs=qe=0;
	q[qe++]=source;
	while(qs<qe) {
		cur=q[qs++];
		vis[cur]=0;
		for(ix=gs[cur];ix<gs[cur+1];ix++) if(f[ix]>0) {
			i=to[ix];
			if(dist[i]>dist[cur]+cost[ix]) {
				dist[i]=dist[cur]+cost[ix];
				prev[i]=ix;
				if(!vis[i]) q[qe++]=i,vis[i]=1;
			}
		}
	}
	return dist[sink];
}

int mincost(int source,int sink) {
	int res=0,cur,pos,flow,ix;
	while((cur=augment(source,sink))<INF) {
		pos=sink,flow=INF;
		while((ix=prev[pos])>-1) {
			if(flow>f[ix]) flow=f[ix];
			pos=from[ix];
		}
		res+=cur*flow;
		pos=sink;
		while((ix=prev[pos])>-1) {
			f[ix]-=flow;
			f[inv[ix]]+=flow;
			pos=from[ix];
		}
	}
	return res;
}

void radixsort() {
	static int newfrom[MAXE],newto[MAXE];
	int i,j;
	/* sort on to */
	memset(gs,0,sizeof(int)*(n+1));
	for(i=0;i<ne;i++) gs[to[i]]++;
	for(i=1;i<n;i++) gs[i]+=gs[i-1];
	for(i=ne-1;i>=0;i--) {
		j=--gs[to[i]];
		newto[j]=to[i];
		newfrom[j]=from[i];
	}
	/* (stable) sort on from */
	memset(gs,0,sizeof(int)*(n+1));
	for(i=0;i<ne;i++) gs[newfrom[i]]++;
	for(i=1;i<n;i++) gs[i]+=gs[i-1];
	gs[n]=ne;
	for(i=ne-1;i>=0;i--) {
		j=--gs[newfrom[i]];
		to[j]=newto[i];
		from[j]=newfrom[i];
	}
}

/* for each edge a->b, find index to b->a */
void inverseedges() {
	static int starts[MAXV+1];
	int i;
	memcpy(starts,gs,sizeof(int)*(n+1));
	for(i=0;i<ne;i++) inv[i]=starts[to[i]]++;
}

/* add both directions of an edge */
void addedge(int a,int b) {
	if(ne+2>MAXE) {
		puts("increase edges and recompile");
		exit(0);
	}
	from[ne]=a; to[ne++]=b;
	from[ne]=b; to[ne++]=a;
}

/* end of min-cost max flow */

char w[MAXW][MAXS];
ll wmask[MAXW];
int nw;

void trimcrlf(char *s) {
	int l=strlen(s);
	if(s[l-1]!='\n' && s[l-1]!='\r') puts("increase MAXSTR and recompile"),exit(0);
	while(l && (s[l-1]=='\n' || s[l-1]=='\r')) s[--l]=0;
}

int getix(char s) {
	if(s>='a' && s<='z') return s-'a';
	if(s>='A' && s<='Z') return s-'A'+32;
	return 62;
}

int include[MAXW];
int ni;

void solve() {
	char s[MAXSTR],t[MAXSTR];
	ll mask1=0,mask2=0,mask3;
	int i,j,tn;
	int source,sink,letters,words;
	int match[MAXSTR];
	fgets(s,MAXSTR-1,stdin); trimcrlf(s);
	for(i=j=0;;) {
		while(s[j]==' ') j++;
		if(!s[j]) break;
		t[i++]=s[j++];
	}
	t[i]=0;
	mask1=(1LL<<getix(t[0]))|(1LL<<getix(t[1]));
	for(i=2;t[i];i++) {
		if(!isalpha(t[i])) printf("illegal char [%c]\n",t[i]),exit(0);
		mask2|=(1LL<<getix(t[i]));
	}
	tn=strlen(t);
	for(ni=i=0;i<nw;i++) if((wmask[i]&mask1)==mask1 && (wmask[i]&mask2)) include[ni++]=i;
	if(ni<tn-2) {
		/* trivial reject - fewer eligible words than letters */
		puts("-1");
		return;
	}
	/* create graph */
	source=0;
	letters=1;
	words=letters+tn-2;
	sink=words+ni;
	n=sink+1;
	ne=0;
	if(n>MAXV) puts("increase MAXV and recompile"),exit(0);
	for(i=0;i<tn-2;i++) addedge(source,letters+i);
	for(i=0;i<tn-2;i++) for(j=0;j<ni;j++) {
		mask3=mask1|(1LL<<getix(t[i+2]));
		if((wmask[include[j]]&mask3)==mask3) addedge(letters+i,words+j);
	}
	for(i=0;i<ni;i++) addedge(words+i,sink);
	radixsort();
	inverseedges();
	memset(f,0,ne*sizeof(int));
	memset(cost,0,ne*sizeof(int));
	/* set capacities and costs */
	for(i=0;i<ne;i++) {
		if(from[i]==source) f[i]=1;
		if(to[i]==sink) f[i]=1,cost[i]=strlen(w[include[from[i]-words]]);
		if(from[i]==sink) f[i]=1,cost[i]=-strlen(w[include[to[i]-words]]);
		if(from[i]>=letters && from[i]<words && to[i]>=words && to[i]<sink) f[i]=1;
	}
	mincost(source,sink);
	for(i=0;i<ne;i++) if(from[i]==source && f[i]) {
		/* unmatched letter, reject */
		puts("-1");
		return;
	}
	printf("%d\n",tn-2);
	for(i=0;i<ne;i++) if(!f[i] && from[i]>=letters && from[i]<words && to[i]>=words && to[i]<sink)
		match[from[i]-letters]=to[i]-words;
	for(i=0;i<tn-2;i++) puts(w[include[match[i]]]);
}

int main() {
	char s[MAXSTR];
	int i,j,M;
	if(!(from=malloc(sizeof(int)*MAXE))) { puts("out of memory on from"); return 0; }
	if(!(to=malloc(sizeof(int)*MAXE))) { puts("out of memory on to"); return 0; }
	if(!(f=malloc(sizeof(int)*MAXE))) { puts("out of memory on f"); return 0; }
	if(!(cost=malloc(sizeof(int)*MAXE))) { puts("out of memory on cost"); return 0; }
	if(!(inv=malloc(sizeof(int)*MAXE))) { puts("out of memory on inv"); return 0; }
	fgets(s,MAXSTR-1,stdin); sscanf(s,"%d",&nw);
	for(i=0;i<nw;i++) {
		fgets(s,MAXSTR-1,stdin); trimcrlf(s);
		if(strlen(s)>MAXS-1) { printf("increase MAXS to %d and recompile\n",(int)strlen(s)+1); return 0; }
		strcpy(w[i],s);
		wmask[i]=0;
		for(j=0;s[j];j++) wmask[i]|=1LL<<getix(s[j]);
	}
	fgets(s,MAXSTR-1,stdin); sscanf(s,"%d",&M);
	while(M--) solve();
	return 0;
}
