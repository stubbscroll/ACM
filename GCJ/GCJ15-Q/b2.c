/* solution for both inputs:
   observation: all special minutes can happen before all normal minutes
   algorithm: try all different numbers of normal minutes, and calculate how
   many special minutes we need to spend splitting */

#include <stdio.h>

int d,p[1000];

void solve() {
	int i,best=1001,eat,cur;
	scanf("%d",&d);
	for(i=0;i<d;i++) scanf("%d",&p[i]);
	for(eat=1;eat<=1000;eat++) {
		for(cur=eat,i=0;i<d;i++) cur+=(p[i]-1)/eat;
		if(best>cur) best=cur;
	}
	printf("%d\n",best);
}

int main() {
	int T,caseno=1;
	scanf("%d",&T);
	while(T--) printf("Case #%d: ",caseno++),solve();
	return 0;
}
