/* solution for say it loudly, both inputs
   algorithm: straightforward parsing and integer comparison */

#include <stdio.h>
#include <ctype.h>

void solve() {
	int teller=0,nevner=1,ix=-1,n,star,i,upper,ord,len,score,j;
	char s[999];
	fgets(s,998,stdin);
	fgets(s,998,stdin); sscanf(s,"%d",&n);
	for(j=0;j<n;j++) {
		fgets(s,998,stdin);
		for(score=len=ord=star=i=0;s[i];i++) {
			if(isalpha(s[i])) {
				if(!len) upper=1;
				len++;
				if(islower(s[i])) upper=0;
			} else {
				if(len) ord++,score+=(1+2*star)*(1+upper),len=0;
				if(s[i]=='*') star^=1;
			}
		}
		if(score*nevner>teller*ord) teller=score,nevner=ord,ix=j;
	}
	printf("%d\n",ix+1);
}

int main() {
	int T;
	char s[999];
	fgets(s,998,stdin); sscanf(s,"%d",&T);
	while(T--) solve();
	return 0;
}
