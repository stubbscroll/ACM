#include <stdio.h>

int main() {
	int cases,a,b,e=0;
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d",&a);
		b=a+10;
		if((b&1)!=e) b++;
		if(b>1000000000) b-=16;
		printf("%d\n",b);
		e^=1;
	}
	return 0;
}
