/* solution for game on a conveyor belt, hard input
   algorithm: implement magic from editorial */

#include <stdio.h>

#define MAX 100001

int n;
char s[MAX];

int zeros[MAX],peak[MAX];

void solve() {
	int i,maks=0,z=0,l=0,m,ones=0;
	scanf("%d %s",&n,s);
	zeros[0]=peak[0]=0;
	for(i=0;s[i];i++) {
		if(s[i]=='0') z++,l--;
		else l++,ones++;
		if(maks<l) maks=l;
		zeros[i+1]=z;
		peak[i+1]=maks;
	}
	m=i;
	/* find prefix p such that zeros(p)=(2m-3l)/4 and prefix(p)=l */
	for(i=0;i<=m;i++) if(4*zeros[i]==2*ones-3*peak[i]) {
		puts("Betka");
		return;
	}
	puts("Adam");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
