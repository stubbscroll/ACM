#include <stdio.h>
#include <stdlib.h>

int a[100],b[100];
int compi(const void *A,const void *B) {
	return *((int *)B)-*((int *)A);
}
int main() {
	int n,d,r,i,j,ans,best,bestix;
	while(scanf("%d %d %d",&n,&d,&r),r) {
		for(i=0;i<n;i++) scanf("%d",&a[i]);
		qsort(a,n,sizeof(int),compi);
		for(i=0;i<n;i++) scanf("%d",&b[i]);
		for(ans=i=0;i<n;i++) {
			bestix=-1; best=1010101;
			for(j=0;j<n;j++) if(b[j]>-1 && a[i]+b[j]<best) best=a[i]+b[j],bestix=j;
			if(bestix<0) for(best=j=0;j<n;j++) if(best<b[j]) best=b[j],bestix=j;
			if(a[i]+b[bestix]>=d) ans+=(a[i]+b[bestix]-d)*r;
			b[bestix]=-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
