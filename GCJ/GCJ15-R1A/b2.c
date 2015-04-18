/* solution for B small */

#include <stdio.h>

int b;
int tid[1000];
int left[1000];
int N;

void solve() {
	static int caseno=1;
	int i=-1,min,j,mul,cycle;
	scanf("%d %d",&b,&N);
	for(i=0;i<b;i++) scanf("%d",&tid[i]),left[i]=0;
	for(mul=1,i=0;i<b;i++) mul*=tid[i];
	for(cycle=i=0;i<b;i++) cycle+=mul/tid[i];
	if(N>cycle) {
		N%=cycle;
		if(!N) N=cycle;
	}
	for(i=j=0;j<N;j++) {
		min=123123123;
		for(i=0;i<b;i++) if(min>left[i]) min=left[i];
		if(min) for(i=0;i<b;i++) left[i]-=min;
		for(i=0;left[i];i++);
		left[i]=tid[i];
	}
	printf("Case #%d: %d\n",caseno++,i+1);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
