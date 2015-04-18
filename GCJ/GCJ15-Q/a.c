/* solution for A small and large */

#include <stdio.h>

void solve() {
	static int caseno=1;
	int m,i,r=0,t=0;
	char s[1111];
	scanf("%d %s",&m,s);
	for(i=0;i<=m;i++) {
		if(s[i]>48 && t<i) r+=i-t,t=i;
		t+=s[i]-48;
	}
	printf("Case #%d: %d\n",caseno++,r);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
