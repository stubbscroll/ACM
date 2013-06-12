/* frank rubin's algorithm, slower implementation but otherwise equivalent */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXV 256
#define MAXE 65536
int from[MAXE],to[MAXE];
int inv[MAXE];
int gs[MAXV+1];
int n,ne;
int edge[MAXE];           /* edge classification */
char taken[MAXV];

int path[MAXV];
int picked[MAXV]; /* edge index picked */

#define UNKNOWN 0
#define REQUIRED 1
#define DELETED 2

int countreq(int u) {
	int i,r=0;
	for(i=gs[u];i<gs[u+1];i++) if(edge[inv[i]]==REQUIRED) r++;
	return r;
}

/* follow required edges and return the other loose end */
int follow(char *t2,int u,int *steps) {
	int v=-1,i,c=0;
	t2[u]=1;
	for(i=gs[u];i<gs[u+1];i++) if(edge[inv[i]]==REQUIRED) {
		v=to[i];
		c++;
		t2[v]=1;
		break;
	}
	if(v<0) { *steps=0; return -1; }
	while(1) {
		for(i=gs[v];i<gs[v+1];i++) if(edge[inv[i]]==REQUIRED && to[i]!=u) {
			u=v; v=to[i];
			t2[v]=1;
			c++;
			goto again;
		}
		*steps=c;
		return v;
	again:;
	}
}

/* super-inefficient algorithm for now */
int badadmissible(int ix) {
	int i,j,deg,done,v,steps,exist;
	static char t2[MAXV];
	for(i=0;i<ne;i++) edge[i]=UNKNOWN;
	/* update along path */
	for(i=0;i<ix-1;i++) edge[inv[picked[i]]]=REQUIRED;
	/* apply rules until we can't */
	do {
		done=1;
		/* D1: all other nodes going out from nodes having 2 picked edges are
			 forbidden */
		for(i=0;i<n;i++) {
			deg=0;
			for(j=gs[i];j<gs[i+1];j++) if(edge[inv[j]]==REQUIRED) deg++;
			if(deg==2) for(j=gs[i];j<gs[i+1];j++) if(edge[inv[j]]==UNKNOWN) edge[inv[j]]=DELETED,done=0;
		}
		/* R2: if there are only two non-deleted edges left, they are required */
		for(i=0;i<n;i++) {
			for(deg=0,j=gs[i];j<gs[i+1];j++) if(edge[inv[j]]!=DELETED) deg++;
			if(deg==2)
			for(j=gs[i];j<gs[i+1];j++) if(edge[inv[j]]==UNKNOWN) edge[inv[j]]=REQUIRED,done=0;
		}
		/* F1/2: node has <2 edges */
		for(i=0;i<n;i++) {
			deg=0;
			for(j=gs[i];j<gs[i+1];j++) if(edge[inv[j]]!=DELETED) deg++;
			if(deg<2) return 0;
		}
		/* F5: node has >2 required edges */
		for(i=0;i<n;i++) if(countreq(i)>2) return 0;
		/* F6: there is a small closed circuit */
		memset(t2,0,n);
		for(exist=i=0;i<n;i++) if(!t2[i] && countreq(i)==1) follow(t2,i,&steps),exist=1;
		if(exist) for(i=0;i<n;i++) if(!t2[i] && countreq(i)==2) return 0;
		/* D3: delete edge that forms a non-hamiltonian closed circuit */
		memset(t2,0,n);
		for(i=0;i<n;i++) if(!t2[i]) {
			if(countreq(i)==1) {
				v=follow(t2,i,&steps);
				if(steps<2) continue;
				/* find edge u->v and forbid it */
				for(j=gs[i];j<gs[i+1];j++) if(to[j]==v) {
					if(edge[inv[j]]==REQUIRED) printf("error");
					if(edge[inv[j]]!=DELETED) edge[inv[j]]=DELETED,done=0;
				}
			}
		}
	} while(!done);
	return 1;
}

int iter,maxiter=-1;

int btr(int at,int ix) {
	int i,r;
	if(iter++==maxiter) return 2;
	if(ix==n) {
		for(i=gs[at];i<gs[at+1];i++) if(to[i]==path[0] && edge[inv[i]]!=DELETED) return 1;
		return 0;
	}
	if(!badadmissible(ix)) return 0;
	/* first, check for required edge */
	if(ix>1) {
		for(i=gs[at];i<gs[at+1];i++) if(!taken[to[i]] && edge[inv[i]]==REQUIRED) {
			path[ix]=to[i];
			taken[to[i]]=1;
			picked[ix-1]=i;
			r=btr(to[i],ix+1);
			if(r) return r;
			taken[to[i]]=0;
			return 0;
		}
	}
	for(i=gs[at];i<gs[at+1];i++) if(!taken[to[i]] && edge[inv[i]]!=DELETED) {
		path[ix]=to[i];
		taken[to[i]]=1;
		picked[ix-1]=i;
		r=btr(to[i],ix+1);
		if(r) return r;
		badadmissible(ix); /* recalculate edge status */
		taken[to[i]]=0;
	}
	return 0;
}

void inverseedges() {
	static int starts[MAXV+1];
	int i;
	memcpy(starts,gs,sizeof(int)*(n+1));
	for(i=0;i<ne;i++) inv[i]=starts[to[i]]++;
	for(i=0;i<ne;i++) if(from[i]<to[i]) inv[i]=i;
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
	inverseedges();
}

void addedge(int a,int b) {
	from[ne]=a; to[ne++]=b;
	from[ne]=b; to[ne++]=a;
}

int hamcycle(int start) {
	iter=0;
	memset(taken,0,n);
	taken[start]=1;
	path[0]=start;
	return btr(start,1);
}

int main() {
	char s[16];
	int a,b,i;
	while(scanf("%d",&n)==1) {
		ne=0;
		while(1) {
			scanf("%s",s);
			if(s[0]=='%') break;
			a=strtol(s,0,10);
			scanf("%d",&b);
			addedge(a-1,b-1);
		}
		radixsort();
		if(!hamcycle(0)) puts("N");
		else {
			for(i=0;i<n;i++) printf("%d ",path[i]+1);
			printf("%d\n",path[0]+1);
		}
	}
	return 0;
}
