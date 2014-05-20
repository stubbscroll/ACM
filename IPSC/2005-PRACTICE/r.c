/* solution to rotate and cut, both inputs.
   algorithm: simulation, and stop when string is too short to be cut */

#include <stdio.h>
#include <string.h>

int n;
char s[200000];

void solve() {
	int left,right,flip=0,len;
	scanf("%d %s",&n,s);
	left=0;
	right=strlen(s);
	while(n-- && right-left>3) {
		len=(right-left)/4;
		if(flip) right-=len;
		else left+=len;
		flip^=1;
	}
	s[right]=0;
	puts(s+left);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
