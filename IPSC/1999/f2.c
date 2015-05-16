/* solution for panel, both inputs
   algorithm: direct implementation of randomized solution that flips random
   columns and accepts changes that decrease answer most of the time. P and
   ITER are pretty much guesswork */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50

#define P 0.8
#define ITER 1000000

int a[MAX][MAX];
int n;

int best[MAX][MAX];
int bestn;

void opt() {
	int i,j,c;
	for(i=0;i<n;i++) {
		for(c=j=0;j<n;j++) c+=a[i][j];
		if(c+c>n) for(j=0;j<n;j++) a[i][j]^=1;
	}
}

int cnt() {
	int i,j,r;
	for(r=i=0;i<n;i++) for(j=0;j<n;j++) r+=a[i][j];
	return r;
}

int main() {
	int i,j,iter=ITER,k,old,cur,r;
	srand(time(0));
	scanf("%d",&n);
	for(i=0;i<n;i++) for(j=0;j<n;j++) scanf("%d",&a[i][j]);
	bestn=n*n+1;
	while(iter--) {
		opt();
		old=cnt();
		k=rand()%n;
		for(i=0;i<n;i++) a[i][k]^=1;
		opt();
		cur=cnt();
		if(bestn>cur) for(bestn=cur,i=0;i<n;i++) for(j=0;j<n;j++) best[i][j]=a[i][j];
		r=rand()%100;
		if((cur<old && r>P*100) || (cur>=old && r<P*100)) for(i=0;i<n;i++) a[i][k]^=1;
	}
	printf("%d\n",bestn);
	for(i=0;i<n;i++) for(j=0;j<n;j++) printf("%d%c",best[i][j],j==n-1?'\n':' ');
	return 0;
}
