/* solution to gears in action, easy input.
   brute force, increase timesteps by 1, declare impossible if we reach
   2*10^9.
   surprisingly, this passes, and in 56 seconds */

#include <stdio.h>

#define MAX 100

int size[MAX],goal[MAX],at[MAX];
int n;

void solve() {
	int i,t;
	scanf("%d",&n);
	for(i=0;i<n;i++) {
		scanf("%d %d",&size[i],&goal[i]);
		if(i&1) goal[i]=(size[i]-goal[i])%size[i];
		at[i]=0;
	}
	for(t=0;t<2000000000;t++) {
		for(i=0;i<n;i++) if(at[i]!=goal[i]) goto next;
		printf("%d\n",t);
		return;
	next:
		for(i=0;i<n;i++) {
			at[i]++;
			if(at[i]==size[i]) at[i]=0;
		}
	}
	puts("Impossible");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}