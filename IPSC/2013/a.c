#include <stdio.h>

int z[]={1,2,5,10,20,50,100,200,500,1000,2000,5000,10000};
int y[13];

int main() {
	int T,a,b,i;
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d",&a,&b);
		a=a*100+b;
		for(i=0;i<13;i++) y[i]=0;
		for(i=12;i>=0;i--) while(a>=z[i]) a-=z[i],y[i]++;
		for(i=0;i<13;i++) printf("%d ",y[i]);
		printf("\n");
	}
	return 0;
}
