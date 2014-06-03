/* solution for pancakes!, easy input */

#include <stdio.h>

int main() {
	int T,c,y,su,sa,f,b,gs,gc,w,r,p;
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d %d %d %d",&c,&y,&su,&sa,&f);
		scanf("%d %d %d %d",&b,&gs,&gc,&w);
		r=c*2; f*=16;
		if(r>y*2) r=y*2;
		if(r>su*4) r=su*4;
		if(r>sa*16) r=sa*16;
		if(r>f/9) r=f/9;
		p=b+gs/30+gc/25+w/10;
		printf("%d\n",r<p?r:p);
	}
	return 0;
}
