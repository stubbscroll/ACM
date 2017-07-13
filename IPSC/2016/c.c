#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;
int p[111111];
int cycles[111111],cn;
char taken[111111];
int poss[111111];

#define MOD 1000000009

#define MAXP 100001

/* precalculated pascal's triangle */
int *pascal[MAXP];

/* must call this before evalmultinomial and rank/unrank */
void precalculatepascal() {
	int i,j;
	for(i=0;i<MAXP;i++) pascal[i]=malloc(sizeof(int)*(i+1));
	for(i=0;i<MAXP;i++) {
		pascal[i][0]=pascal[i][i]=1;
		for(j=1;j<i;j++) {
			pascal[i][j]=pascal[i-1][j-1]+pascal[i-1][j];
			if(pascal[i][j]>=MOD) pascal[i][j]-=MOD;
		}
		if(i%1000==0) fprintf(stderr,"%d ",i/1000);
	}
	fprintf(stderr,"\n");
}

int mm[111111],nn;

/* evaluate multinomial coefficient (without division)
   based on knuth 1.2.6 equation 4.3 */
int evalmultinomial(int *c,int n) {
	int r=1;
	int a=c[0],b=0,i;
	for(i=1;i<n;i++) a+=c[i],b+=c[i-1],r=(long long)r*pascal[a][b]%MOD;
	return r;
}

/* evaluate n^k mod mod */
unsigned int powmod(unsigned int n,unsigned int k,unsigned int mod) {
	unsigned int ans=1;
	while(k) {
		if(k&1) ans=(unsigned long long)ans*n%mod;
		k>>=1;
		n=(unsigned long long)n*n%mod;
	}
	return ans;
}

void findcycles() {
	int i,len,j;
	int ways;
	for(i=0;i<n;i++) taken[i]=0;
	cn=0;
	for(i=0;i<n;i++) if(!taken[i]) {
		taken[i]=1;
		len=1;
		j=i;
		while(1) {
			j=p[j];
			if(taken[j]) break;
			taken[j]=1;
			len++;
		}
		cycles[cn++]=len;
	}
	/* ways: */
	ways=1;
	for(i=0;i<cn;i++) ways=((long long)ways*poss[cycles[i]])%MOD;
	/* make new multinomial */
	nn=0;
	for(i=0;i<cn;i++) if(cycles[i]>1) mm[nn++]=cycles[i]-1;
	ways=(long long)ways*evalmultinomial(mm,nn)%MOD;
	printf("%d\n",ways);
}

void solve() {
	int i;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&p[i]),p[i]--;
	findcycles();
}

int main() {
	int T,i;
	precalculatepascal();
	poss[1]=1; poss[2]=1;
	for(i=3;i<=100000;i++) poss[i]=powmod(i,i-2,MOD);
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
