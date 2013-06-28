#include <stdio.h>
#include <stdlib.h>

void gen(int n) {
	int i;
	printf("%d\n",n);
	for(i=0;i<n;i++) printf("%d%c",(rand()+rand()*32768)%100000+1,i==n-1?'\n':' ');
}

int main() {
	puts("20");
	gen(10);
	gen(50);
	gen(100);
	gen(200);
	gen(300);
	gen(400);
	gen(500);
	gen(600);
	gen(800);
	gen(1000);
	gen(2000);
	gen(3000);
	gen(4000);
	gen(6000);
	gen(8000);
	gen(10000);
	gen(12500);
	gen(15000);
	gen(17500);
	gen(20000);
	return 0;
}
