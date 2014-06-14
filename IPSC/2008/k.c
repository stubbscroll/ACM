/* solution for k equal digits, easy input
   algorithm: try each length in increasing order and check modulo */

#include <stdio.h>
#include <stdlib.h>

#define MAXR 100

typedef long long ll;

int k,r;
ll a[MAXR];
ll mod[MAXR];

void solve() {
	int i,best=1,bestd=0,d,len;
	scanf("%d %d",&k,&r);
	if(r>MAXR) printf("increase MAXR to %d and recompile\n",r),exit(1);
	for(i=0;i<r;i++) scanf("%I64d",&a[i]);
	for(d=1;d<10;d++) {
		for(i=0;i<r;i++) mod[i]=0;
		for(len=1;len<=k;len++) for(i=0;i<r;i++) {
			mod[i]=(mod[i]*10+d)%a[i];
			if(!mod[i] && best<=len) best=len,bestd=d;
		}
	}
	printf("%d %d\n",best,bestd);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
