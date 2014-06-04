#include <stdio.h>
#include <string.h>
typedef long long ll;

int n;
int str;
int st[256][64];

/* [i][j]: needed number of guesses for strategy i to guess j */
int guess[256][64];

/* simulate guess: strategy strno, guess num */
int simul(int strno,int num) {
	int guesses=1,at=0;
	int lessthan=10000,largerthan=-1;
	while(1) {
		while(st[strno][at]<=largerthan || st[strno][at]>=lessthan) at++;
		if(st[strno][at]==num) return guesses;
		if(st[strno][at]<num) largerthan=st[strno][at];
		if(st[strno][at]>num) lessthan=st[strno][at];
		guesses++;
	}
}

ll gcd(ll a,ll b) {
	if(b==0) return a;
	return gcd(b,a%b);
}

int vector[128];

int main() {
	ll high,cur,g,teller,nevner;
	int cases,i,j,highs;
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d %d",&n,&str);
		for(i=0;i<str;i++) for(j=0;j<n;j++) scanf("%d",&st[i][j]);
		for(i=0;i<str;i++) for(j=0;j<n;j++) guess[i][j]=simul(i,j);
		high=highs=-1;
		for(i=0;i<n;i++) {
			cur=0;
			for(j=0;j<str;j++) cur+=guess[j][i];
			if(cur>high) {
				high=cur;
				highs=i;
			}
		}
		g=gcd(high,str);
		teller=high/g;
		nevner=str/g;
		printf("%I64d/%I64d\n",teller,nevner);
		for(i=0;i<n;i++) printf("%d ",highs==i?str:0);
		printf("\n");
	}
	return 0;
}
