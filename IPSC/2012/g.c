#include <stdio.h>
#include <string.h>

int a,b,c,n;

int try(int at) {
	char v[300];
	int num=0;
	memset(v,0,sizeof(v));
	while(!v[at]) {
		v[at]=1;
		at=(a*at*at+b*at+c)%n;
		num++;
	}
	return num;
}

int brute() {
	int maks=0,cur,i;
	for(i=0;i<n;i++) {
		cur=try(i);
		if(maks<cur) maks=cur;
	}
	return maks;
}

int main() {
	int cases;
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d %d %d %d",&a,&b,&c,&n);
		printf("%d\n",brute());
	}
	return 0;
}
