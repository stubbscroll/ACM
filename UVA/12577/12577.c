#include <stdio.h>
int main() {
	char s[99];
	int n=1;
	while(scanf("%s",s),s[0]>55) printf("Case %d: Hajj-e-A%sar\n",n++,s[0]>'H'?"sgh":"kb");
	return 0;
}
