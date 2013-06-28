/* this solution times out. apparently n*(log 1e9)^2 is too much */

#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
typedef long long ll;
map<int,int> tree;
int n;

void deltree() {
	tree.clear();
}

void update(int a,int ix) {
	while(ix<=n) tree[ix]+=a,ix+=(ix&-ix);
}

int read(int ix) {
	int r=0;
	while(ix) r+=tree[ix],ix-=(ix&-ix);
	return r;
}

int N;

int main() {
	ll r;
	int i,a;
	while(scanf("%d",&N),N) {
		n=1000000100;
		deltree();
		for(r=i=0;i<N;i++) {
			scanf("%d",&a);
			a+=10;
			r+=read(n-2)-read(a);
			update(1,a);
		}
		printf("%lld\n",r);
	}
	return 0;
}
