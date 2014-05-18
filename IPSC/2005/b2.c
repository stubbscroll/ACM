/* solution to bottom coder, hard input.
   algorithm: make a fast version of b2.c, by observing that all mysterious
   functions are performing arithmetic on numbers, represented as base 100 in
   arrays, and checking if the text output is sensible.
   the program needs around 45 seconds to find the answer */

#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll rex,rex1;

/* most of these functions ended up not being used */

/* set a to 0 */
void f3(ll *a) {
	*a=0;
}

/* check if a equals 0 */
int f2(ll *a) {
	return *a==0;
}

/* a=(a+1) mod (rex+1) */
void f1(ll *a) {
	(*a)++;
	if(*a>=rex1) *a=0;
}

/* a=(a-1) mod (rex+1) */
void f4(ll *a) {
	*a=*a+rex;
	if(*a>=rex1) *a-=rex1;
}

/* set a=b */
void f7(ll *a,ll *b) {
	*a=*b;
}

/* a=(a+b+1) mod (rex+1) and set b to 0 */
void f9(ll *a,ll *b) {
	*a=*a+*b+1;
	if(*a>=rex1) {
		*a-=rex1;
		if(*a>=rex1) *a-=rex1;
	}
	*b=0;
}

/* a=(a*b+1) mod (rex+1) and set b to 0 */
void f8(ll *a,ll *b) {
	*a=(*a**b+1)%rex1;
	*b=0;
}

/* a=a^b mod (rex+1) and set b to 0 */
void f5(ll *a,ll *b) {
	ll c=*b,d=*a;
	*a=1;
	while(c) {
		if(c&1) *a=(*a*d)%rex1;
		d=(d*d)%rex1;
		c>>=1;
	}
	*b=0;
}

typedef unsigned int uint;
typedef unsigned long long ull;
/* evaluate 1+a+a^2+...+a^n mod m */
uint powsum(uint a,uint n,uint m) {
	uint z=1,b=a,c=1,r=0,i;
	n++;
	for(i=0;i<32 && (1U<<i)<=n;i++) {
		if((1U<<i)&n) {
			r=(r+(ull)c*z)%m;
			c=((ull)c*b)%m;
		}
		z=(z+(ull)z*b)%m;
		b=((ull)b*b)%m;
	}
	return r;
}

void f10(int x) {
	int rpl[]={
		80, 125, 111, 18, 59, 88, 88, 28, 65, 98, 119, 103, 101, 79, 107, 2, 16,
		92, 102, 123, 103, 84, 112, 78, 68, 98, 65, 37, 105, 85, 107, 13, 45, 9,
		104, 81, 21, 31, 55, 110, 78, 66, 66, 3, 77, 63, 16, 105, 15, 123, 16, 84,
		31, 96, 4, 82, 82, 122, 68, 115, 35, 73, 3, 108, 115, 83, 15, 19, 31, 99,
		5, 123, 24, 65, 36, 15, 75, 84, 4, 2, -1};
	int i;
	ll a,b,c,d;
	if (x<100000000 || x>200000000) return;
	rex=100000000;
	rex1=rex+1;
	for(i=0;rpl[i]>-1;i++) {
		a=(i+1)*(i+1)*(i+1)*(i+1);
		c=2;
		/* evaluate c*x^a */
		b=x;
		d=a;
		f5(&b,&d);
		/* evaluate 1+x+x^2+x^3+x^4+...+x^(a-1)+ */
		c=(2*b+powsum(x,a-1,rex1))%rex1;
		rpl[i]^=c/100%100;
		/* prune on dubious ascii values */
		if(rpl[i]<32 && rpl[i]!=8 && rpl[i]!=10 && rpl[i]!=13) return;
	}
	printf("%d\n",x);
	for(i=0;rpl[i]>-1;i++) printf("%c",rpl[i]);
	printf("\n");
	exit(0);
}

int main() {
	int x;
	for(x=100000000;x<=200000000;x++) f10(x);
	return 0;
}
