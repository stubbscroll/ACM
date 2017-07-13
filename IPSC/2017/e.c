/* algorithm: simulate the thing with an array containing all the terrain
   (also in the hard subproblem where the array takes 8 gb) */

#include <stdio.h>
#include <stdlib.h>

int *a;

int p[5000000],e[5000000],n;

void solve() {
	int i,min,max,ix;
	int cost=0,c,j;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d %d",&p[i],&e[i]);
	min=max=p[0];
	for(i=0;i<n;i++) {
		if(min>p[i]) min=p[i];
		if(max<p[i]) max=p[i];
	}
	/* safety margin in case endpoints are changed a lot */
	min-=n+1;
	max+=n+1;
	a=calloc((max-min+1LL),sizeof(int));
	for(i=0;i<n;i++) {
		ix=p[i]-min;
		a[ix]+=e[i];
		c=1;
		for(j=ix-1;j>=0;j--) {
			if(a[j]==a[j+1] || a[j]==a[j+1]-1 || a[j]==a[j+1]+1) break;
			if(a[j]>a[j+1]) a[j]--,c++;
			if(a[j]<a[j+1]) a[j]++,c++;
		}
		for(j=ix+1;j<max-min+1;j++) {
			if(a[j]==a[j-1] || a[j]==a[j-1]-1 || a[j]==a[j-1]+1) break;
			if(a[j-1]>a[j]) a[j]++,c++;
			if(a[j-1]<a[j]) a[j]--,c++;
		}
		cost=(cost+(long long)(i+1)*c)%1000000009;
	}
	printf("%d\n",cost);
	free(a);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
}
