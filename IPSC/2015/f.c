/* solution for familiar couples, easy input
   algorithm: use disjoint sets to keep track of acquaintance classes
   separately for men and women, and check all pairs of couples for familiarity
*/

#include <stdio.h>

#define MAX 3000

int n,q;

#define MAXSET 3000

int p[MAXSET],rank[MAXSET];

int findset(int x) {
	if(x!=p[x]) p[x]=findset(p[x]);
	return p[x];
}

void unionset(int x,int y) {
	x=findset(x);
	y=findset(y);
	if(x==y) return;
	if(rank[x]>rank[y]) p[y]=x;
	else {
		p[x]=y;
		if(rank[x]==rank[y]) rank[y]++;
	}
}

void initset(int n) {
	int i;
	for(i=0;i<n;i++) { p[i]=i; rank[i]=0; }
}

void solve() {
	int i,j,it;
	int t,a,b;
	int prev=-1,cur;
	int r=0;
	scanf("%d %d",&n,&q);
	initset(n*2);
	for(it=1;it<=q;it++) {
		scanf("%d %d %d",&t,&a,&b);
		b--; a--;
		if(t==1) unionset(a,b);
		else if(t==2) unionset(a+n,b+n);
		if(prev==n*(n-1)) cur=prev;
		else {
			cur=0;
			for(i=0;i<n;i++) for(j=i+1;j<n;j++) {
				if(findset(i)==findset(j) && findset(i+n)==findset(j+n)) cur++;
			}
		}
		r=(r+(long long)it*cur)%1000000007;
	}
	printf("%d\n",(int)r);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
