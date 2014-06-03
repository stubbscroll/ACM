#include <stdio.h>
#include <string.h>

int N,c1,g1,c2,g2;
int prince,draw;

#define M 100000
char seen[M];
int q[M],qs,qe;

void iterkapp(int n) {
	int next;
	qs=qe=0;
	q[qe++]=n;
	seen[n]=1;
	while(qs<qe) {
		n=q[qs++];
		if(n-c1==0) {prince=1;return;}
		if(n-c2==0) {prince=1;return;}
		if(n-c1==-1) draw=1;
		if(n-c2==-1) draw=1;
		if(n-c1>0) {
			next=n-c1+g1;
			if(next<M && !seen[next]) q[qe++]=next,seen[next]=1;
		}
		if(n-c2>0) {
			next=n-c2+g2;
			if(next<M && !seen[next]) q[qe++]=next,seen[next]=1;
		}
	}
}

int main() {
	int cases;
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d %d %d %d %d",&N,&c1,&g1,&c2,&g2);
		prince=draw=0;
		memset(seen,0,M);
		if(N==0) prince=1;
		iterkapp(N);
		
		if(prince) puts("PRINCE");
		else if(draw) puts("DRAW");
		else puts("DRAGON");
	}
	return 0;
}
