/* solution for medical research, both inputs
   algorithm: sort */

#include <stdio.h>
#include <stdlib.h>

int a[1000000],n;

int compi(const void *A,const void *B) {
	const int *a=A,*b=B;
	if(*a<*b) return -1;
	if(*a>*b) return 1;
	return 0;
}

void solve() {
	int v;
	for(n=0;;) {
		scanf("%d",&v);
		if(!v) break;
		a[n++]=v;
	}
	qsort(a,n,sizeof(int),compi);
	for(;;) {
		scanf("%d",&v);
		if(!v) break;
		printf("%d ",a[v-1]);
	}
	putchar('\n');
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
