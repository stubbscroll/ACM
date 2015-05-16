/* solution for factorial, easy input
   observation: there are more factors of 2 than factors of 5 in n! for any n.
   calculate the number of occurrences of 2 and 5 in the factorization of n!
   (which is sum_i floor(n/2^i), evaluate n! mod 10 (without factors 2 and 5),
   then multiply in the correct number of twos */

#include <stdio.h>

void solve(int n) {
	int i,d=1,j,two=0;
	for(i=1;i<=n;i++) {
		j=i;
		while(j%2==0) j/=2;
		while(j%5==0) j/=5;
		d=d*j%10;
	}
	for(i=2;i<=n;i*=2) two+=n/i;
	for(i=5;i<=n;i*=5) two-=n/i;
	while(two--) d=d*2%10;
	printf("%d\n",d);
}

int main() {
	int n;
	while(scanf("%d",&n)==1) solve(n);
	return 0;
}
