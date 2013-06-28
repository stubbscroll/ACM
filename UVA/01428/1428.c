#include <stdio.h>
#include <string.h>

typedef long long ll;
int tree[111111],n;   /* warning, array must be of size n+1 */

void deltree() {
	memset(tree,0,sizeof(int)*(n+1));
}

void update(int a,int ix) {
	while(ix<=n) tree[ix]+=a,ix+=(ix&-ix);
}

int read(int ix) {
	int r=0;
	while(ix) r+=tree[ix],ix-=(ix&-ix);
	return r;
}

int left[22222],right[22222];
int left2[22222],right2[22222];
int a[22222],N;

int main() {
	ll r;
	int T,i;
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&N);
		for(i=0;i<N;i++) scanf("%d",&a[i]);
		n=100100;
		deltree();
		for(i=0;i<N;i++) {
			left[i]=read(a[i]);
			left2[i]=read(100000)-read(a[i]-1);
			update(1,a[i]);
		}
		deltree();
		for(i=N-1;i>=0;i--) {
			/* how many numbers greater than or equal to a[i]? */
			right[i]=read(100000)-read(a[i]-1);
			right2[i]=read(a[i]);
			update(1,a[i]);
		}
		for(r=i=0;i<N;i++) r+=(ll)left[i]*right[i]+(ll)left2[i]*right2[i];
		printf("%lld\n",r);
	}
	return 0;
}
