/* solution for copier, both inputs
   algorithm: output first occurrence of each number */

#include <stdio.h>

char taken[111111];
int tall[111111],tn;

void solve() {
	int n,i,a;
	scanf("%d",&n);
	for(i=0;i<n;i++) taken[i]=0;
	for(tn=i=0;i<n;i++) {
		scanf("%d",&a); a--;
		if(!taken[a]) taken[a]=1,tall[tn++]=a+1;
	}
	printf("%d",tall[0]);
	for(i=1;i<tn;i++) printf(" %d",tall[i]);
	putchar('\n');
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
