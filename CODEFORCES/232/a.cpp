#include <cstdio>
#include <map>
using namespace std;

#define MOD 1000000007
int n;
map<int,int> f;

void factorize(int n) {
	int i;
	while(!(n&1)) f[2]++,n>>=1;
	for(i=3;i*i<=n;i+=2) while(n%i==0) f[i]++,n/=i;
	if(n>1) f[n]++;
}

#define MAXL 16000
#define MAXR 550
int p[MAXL][MAXR];

void pascal() {
	int i,j;
	for(i=0;i<MAXL;i++) {
		p[i][0]=1;
		if(i<MAXR) p[i][i]=1;
		for(j=1;j<MAXR && j<i;j++) {
			p[i][j]=p[i-1][j-1]+p[i-1][j];
			if(p[i][j]>=MOD) p[i][j]-=MOD;
		}
	}
}

int main() {
	int a,i;
	scanf("%d",&n);
	for(i=0;i<n;i++) {
		scanf("%d",&a);
		factorize(a);
	}
	pascal();
	long long res=1;
	for(auto it=f.begin();it!=f.end();it++) {
		int k=it->second;
		res=(long long)res*p[n+k-1][n-1]%MOD;
	}
	printf("%d\n",(int)res);
}
