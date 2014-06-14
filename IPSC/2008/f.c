/* solution to find the meaning, easy input
   this program doesn't output the exact answer, but the entire
   decrypted sentence. */

#include <stdio.h>

int main() {
	int a;
	while(scanf("%d",&a)==1) {
		a-=9847;
		if(a>='A' && a<='Z') putchar(a);
	}
	return 0;
}
