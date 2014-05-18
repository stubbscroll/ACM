/* solution to ignore the garbage, easy input (all numbers fit in int).
   algorithm: convert to base 7, use given digit mapping, print backwards */

#include <stdio.h>

int a[7]={0,1,2,5,9,8,6};

void solve(int n) {
	while(n) putchar(a[n%7]+48),n/=7;
}

int main() {
	int n;
	while(scanf("%d",&n)==1) solve(n),putchar('\n');
	return 0;
}
