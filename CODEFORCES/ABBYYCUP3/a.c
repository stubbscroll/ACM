/* observation: no need to use bigint for ?, just append a string with
   the right number of zeros */

#include <stdio.h>
#include <string.h>

char s[1231231];
char z[1111111];
int zn;

int main() {
	long long ans=1;
	int i,taken[10],mul=10;
	scanf("%s",s);
	zn=0;
	memset(taken,0,sizeof(taken));
	for(i=0;s[i];i++) {
		if(s[i]=='?') {
			if(i==0) ans*=9;
			else z[zn++]='0';
		} else if(s[i]>='A' && s[i]<='J' && !taken[s[i]-'A']) {
			taken[s[i]-'A']=1;
			ans*=mul-(i==0);
			mul--;
		}
	}
	z[zn]=0;
	printf("%I64d%s\n",ans,z);
	return 0;
}
