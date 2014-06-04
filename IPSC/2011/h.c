/* solution to hq0-9+-incomputable?!, easy input
   use o command to erase commands on prime and power-of-two indexes.
   i get wrong answer on the submission page, but i suspect they don't
   handle the TIS stuff properly */

#include <stdio.h>

char tis[]="12345678901234567890";
char s[100];

int pow2(int k) {
	int i;
	for(i=0;i<31;i++) if(k==(1<<i)) return 1;
	return 0;
}

int isprime(int n) {
	int i;
	for(i=2;i*i<=n;i++) if(n%i==0) return 0;
	return 1;
}

int main() {
	int i,j,k;
	for(k=0,j=3,i=19;i>=0;j++) {
		if(pow2(j) || isprime(j)) s[k++]='0';
		else s[k++]=tis[i--];
	}
	for(k--;k>=0;k--) putchar(s[k]);
	puts("qo");
	return 0;
}
