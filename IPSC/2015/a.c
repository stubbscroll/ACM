/* solution for a+b, both inputs
   algorithm: sort digits in nonincreasing order, let A=all digits but one
   and B=last digit */

#include <stdio.h>
#include <string.h>

char s[111];

void solve() {
	int i,j,n;
	char t;
	long long d;
	scanf("%s",s);
	n=strlen(s);
	for(i=0;i<n;i++) for(j=0;j<n-1;j++) if(s[j]<s[j+1]) {
		t=s[j]; s[j]=s[j+1]; s[j+1]=t;
	}
	d=0;
	for(i=0;i<n-1;i++) d=d*10+s[i]-48;
	d+=s[i]-48;
	printf("%I64d\n",d);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
