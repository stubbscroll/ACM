/* solution for b easy
   algorithm: stupid bfs in state graph. add one extra element to the state
   where we store the largest stack moved to the infinite diners */

#include <stdio.h>
#include <string.h>

int d,p[6];
int dist[11111111];
int q[11111111],qs,qe;

int pack(int *st) {
	int i,v=0;
	for(i=0;i<=d;i++) v=v*10+st[i];
	return v;
}

void unpack(int v,int *st) {
	int i;
	for(i=d;i>=0;i--) st[i]=v%10,v/=10;
}

/* element d represents the largest non-starting stack and cannot be split */
void bfs() {
	int cur[7],next[7],moves,val,i,j,k;
	qs=qe=0;
	memset(dist,-1,sizeof(dist));
	for(i=0;i<d;i++) cur[i]=p[i];
	cur[d]=0;
	val=pack(cur);
	dist[val]=0;
	q[qe++]=val;
	while(qs<qe) {
		val=q[qs++];
		unpack(val,cur);
		moves=dist[val];
		for(i=0;i<=d;i++) if(cur[i]) goto more;
		printf("%d\n",moves);
		break;
	more:
		/* eat */
		for(i=0;i<=d;i++) next[i]=cur[i];
		for(i=0;i<=d;i++) if(next[i]) next[i]--;
		val=pack(next);
		if(dist[val]<0) q[qe++]=val,dist[val]=moves+1;
		/* special, split a stack */
		for(i=0;i<d;i++) if(cur[i]>1) for(j=1;j<cur[i];j++) {
			for(k=0;k<=d;k++) next[k]=cur[k];
			next[i]-=j;
			if(next[d]<j) next[d]=j;
			val=pack(next);
			if(dist[val]<0) q[qe++]=val,dist[val]=moves+1;
		}
	}
}

void solve() {
	int i;
	scanf("%d",&d);
	for(i=0;i<d;i++) scanf("%d",&p[i]);
	bfs();
}

int main() {
	int T,caseno=1;
	scanf("%d",&T);
	while(T--) printf("Case #%d: ",caseno++),solve();
	return 0;
}
