/* algorithm:
   for each d, scale the probability using multinomial.
   the probabilities as a whole are wrongly scaled,
   but somehow this got accepted */

#include <stdio.h>
#include <math.h>

int n,a,b,m;
int x[40];

#define MAXP 41

/* precalculated pascal's triangle */
double pascal[MAXP][MAXP];

/* must call this before evamultinomial and rank/unrank */
void precalculatepascal() {
	int i,j;
	for(i=0;i<MAXP;i++) {
		pascal[i][0]=pascal[i][i]=1;
		for(j=1;j<i;j++) pascal[i][j]=pascal[i-1][j-1]+pascal[i-1][j];
	}
}

/* evaluate multinomial coefficient (without division)
   based on knuth 1.2.6 equation 4.3 */
/* HNU 11763 (BAPC 2009 problem D) 0 ms, 18.08.2001 */
double evalmultinomial(int *c,int n) {
	double r=1;
	int a=c[0],b=0,i;
	for(i=1;i<n;i++) a+=c[i],b+=c[i-1],r*=pascal[a][b];
	return r;
}

void solve() {
	double p=0,tp=0,q=0,nn=0;
	int i,d;
	scanf("%d %d %d %d",&n,&a,&b,&m);
	if(!m) return;
	for(i=0;i<n;i++) scanf("%d",&x[i]);
	for(i=0;i<n;i++) nn+=x[i];
	for(d=1;d<=m;d++) {
		if(n>d) continue;
		q=1;
		q*=pow(1./d,nn-n);
		for(i=1;i<n;i++) q*=((double)(d-i)/d);
		/* multiply q with multinomial x */
		q*=evalmultinomial(x,n);
		if(d>=a && d<=b) p+=q;
		tp+=q;
	}
	printf("%.10e\n",p/tp);
}

int main() {
	int T;
	scanf("%d",&T);
	precalculatepascal();
	while(T--) solve();
	return 0;
}
