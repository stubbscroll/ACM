#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
typedef long long ll;
int B[] = { 1894607624, 1927505134, 1861486949, 2052221263, 1953703270, 1772249212, 1704106159, 147456, 1829198849 };
std::vector<int> A(B,B+9);
#define MAX 1000000
ll dp[MAX];

ll t(ll n) {
  long long z=n,a,b;
	if(n<MAX) return dp[n];
	for(a=2;a*a<=n;a++) if(n%a==0) {
		b=n/a;
		if(t(a)>=a) z/=t(a),z*=t(a)-1;
		if(a!=b && t(b)>=b) z/=t(b),z*=t(b)-1;
	}
	 if(z+1<n) return z+1;
	 else return n;
}

void pre() {
	ll n,z,a,b;
	dp[0]=0;
	dp[1]=1;
	for(n=2;n<MAX;n++) {
		z=n;
		for(a=2;a*a<=n;a++) if(n%a==0) {
			b=n/a;
			if(dp[a]>=a) z/=dp[a], z*=dp[a]-1;
			if(a!=b && dp[b]>=b) z/=dp[b], z*=dp[b]-1;
		}
		if(z+1<n) dp[n]=z+1; else dp[n]=n;
	}
}

char s[1000];
int pn;

int main() {
	int u[2],up;
	pre();
again:
    sort( A.begin(), A.end() );
    for (int i=0; i<4; ++i) A[i+5] ^= t(A[i+1]-A[0])>>7;
    long long z = std::max( t(A[0])-1, A[0]+1-t(A[0]) );
    for (long long i=0; i<z%9; ++i) std::rotate( A.begin(), A.begin()+1, A.end() );
    A.insert( A.begin()+1, z );
	pn=0;
	up=0;
    for (long long x=8; x<1e7; ++x) {
        int y = A[x/4]>>(18-6*(x%4))&63;
        if (!y) break;
        if (y<60) s[pn++]=31+y,printf("%c",31+y); else printf("%d",A[y-60]),u[up++]=A[y-60];
    }
	s[pn]=0;
	printf("\n[%s]\n",s);
	if(!strcmp(s,"CHANGE  TO ")) {
		printf("change\n");
		for(int i=0;i<9;i++) if(A[i]==u[0]) A[i]=u[1];
		goto again;
	}
	return 0;
}
