/* algorithm: guess that the sum needs max 2 elements.
   then, generate all numbers with no repeating digits, and check if
   difference also has no repeating digits. generate via backtracking to
   avoid checking unnecessary numbers */

#include <stdio.h>

/* return 1 if n has no repeating digits */
int dazzling(int n) {
	int i;
	char z[10];
	for(i=0;i<10;i++) z[i]=0;
	while(n) {
		if(z[n%10]) return 0;
		z[n%10]=1;
		n/=10;
	}
	return 1;
}

int n;
int a,b;

int btr2(long long newa,int at,int mask) {
	int i;
	if(newa>n) return 0;
	/* did we win? */
	if(dazzling(n-newa)) {
		a=newa;
		b=n-newa;
		return 1;
	}
	for(i=0;i<10;i++) if(!(mask&(1<<i))) {
		if(btr2(newa+(long long)i*at,at*10,mask+(1<<i))) return 1;
	}
	return 0;
}

void solve() {
	scanf("%d",&n);
	if(dazzling(n)) { printf("1 %d\n",n); return; }
	if(btr2(0,1,0)) {
		printf("2 %d %d\n",a,b);
		return;
	}
	printf("3 something\n");
	return;
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
