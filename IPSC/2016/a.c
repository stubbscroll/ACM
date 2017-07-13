/* algorithm: output the input and append two arbitraty letters */

#include <stdio.h>
#include <string.h>

char s[10][5];

void solve() {
	int i;
	for(i=0;i<10;i++) scanf("%s",s[i]);
	for(i=0;i<10;i++) printf("%s",s[i]);
	puts("AA");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
