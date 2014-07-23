/* algorithm: try each power d such that x^d=n where x is a candidate for the
   answer. observe that d cannot be larger than log_2(10^18). the naive
   algorithm for counting the number of divisors is sufficient. using binary
   search or similar for root-finding would be better, but the lazy way using
   z=pow(n,1/root) and trying z and z+1 is shorter. */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int numdivisors(ll n) {
	int i;
	int r=0;
	for(i=1;(ll)i*i<n;i++) if(n%i==0) r+=2;
	if(i*i==n) r++;
	return r;
}
#define INF 8000000000000000000LL
struct DivisorsPower {
	long long findArgument(long long n) {
		long long ans=INF,z,y;
		int i,j,k;
		for(i=2;i<62;i++) {
			z=pow(n,1./i);
			/* try z and z+1 since pow is inexact */
			for(k=0;k<2;k++,z++) {
				for(y=1,j=0;j<i;j++) y*=z;
				if(y==n && numdivisors(z)==i && ans>z) ans=z;
			}
		}
		return ans==INF?-1:ans;
	}
};