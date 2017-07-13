/* algorithm: simulation */

#include <stdio.h>
#include <math.h>

int col[1000]; /* 0:black, 1:white */
int c,s2,s;

void solve() {
	int i,iter,at,at2,j,t,i2,j2;
	scanf("%d %d",&c,&s2);
	s=(int)round(sqrt(s2));
	for(i=0;i<c;i++) col[i]=0;
	at=0;
	/* it seems "never" never happens, so INF works here */
	for(iter=0;iter<10000001;iter++) {
		if(iter) {
			for(i=0;i<c;i++) if(col[i]) goto notblack;
			printf("%d\n",iter);
			return;
		}
	notblack:
		at2=at+s;
		for(i=at;i<at2;i++) col[i%c]^=1;
		for(i=at,j=at2-1;i<j;i++,j--) {
			i2=i; if(i2>=c) i2%=c;
			j2=j; if(j2>=c) j2%=c;
			t=col[i2],col[i2]=col[j2],col[j2]=t;
		}
		at=at2%c;
	}
	puts("never");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
