/* algorithm: roughly, click on every other cell along the upper and leftmost
   border. whether we place on odd or even coordinates depend on parity of
   height and width */

#include <stdio.h>

void solve() {
	int r,c,i;
	scanf("%d %d",&r,&c);
	if(r==1) {
		printf("%d\n",(c+2)/2);
		for(i=0;i<c;i+=2) printf("0 %d\n",i);
		if(!(c&1)) printf("0 %d\n",c-1);
	} else if(c==1) {
		printf("%d\n",(r+2)/2);
		for(i=0;i<r;i+=2) printf("%d 0\n",i);
		if(!(r&1)) printf("%d 0\n",r-1);
	} else if((c&1) && (r&1)) {
		printf("%d\n",(r+c)/2);
		for(i=0;i<c;i+=2) printf("0 %d\n",i);
		for(i=2;i<r;i+=2) printf("%d 0\n",i);
	} else {
		printf("%d\n",(r+1)/2+(c+1)/2);
		for(i=1;i<c;i+=2) printf("0 %d\n",i);
		if(c&1) printf("0 %d\n",c-1);
		for(i=1;i<r;i+=2) printf("%d 0\n",i);
		if(r&1) printf("%d 0\n",r-1);
	}
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
