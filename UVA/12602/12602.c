#include <stdio.h>

int main() {
	int T,a;
	char s[9];
	scanf("%d",&T);
	while(T--) {
		scanf("%s",s);
		a=s[0]*676+s[1]*26+s[2]-45695-s[4]*1000-s[5]*100-s[6]*10-s[7]+53328;
		printf("%snice\n",a<-100||a>100?"not ":"");
	}
	return 0;
}
