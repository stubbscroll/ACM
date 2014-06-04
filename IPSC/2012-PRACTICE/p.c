#include <stdio.h>

int a[15000],n,s,h;
int d[15000];

int main() {
	int cases,i,a1,a2,throw,n1,n2;
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d",&n);
		for(s=i=0;i<n;i++) scanf("%d",&a[i]),s+=a[i];
		h=s/2;
		throw=0;
		n1=n2=0;
		for(a1=a2=i=0;i<n;i++) if(a1+a[i]<=h) d[i]=0,a1+=a[i],n1++;
		else if(a2+a[i]<=h) d[i]=1,a2+=a[i],n2++;
		else d[i]=2,throw++;
		printf("%d",n1); for(i=0;i<n;i++) if(!d[i]) printf(" %d",i+1); putchar('\n');
		printf("%d",n2); for(i=0;i<n;i++) if(d[i]==1) printf(" %d",i+1); putchar('\n');
	}
	return 0;
}
