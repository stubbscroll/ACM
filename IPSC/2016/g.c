/* algorithm: extract digits only, make sure to avoid leading zeros */

#include <stdio.h>
#include <ctype.h>

char s[1111],t[1111];

void solve() {
	int i,j;
	scanf("%s",s);
	/* find non-zero */
	for(i=0;s[i];i++) if(isdigit(s[i]) && s[i]!='0') break;
	if(!s[i]) { puts("0"); return; }
	t[0]=s[i]; j=1;
	for(i++;s[i];i++) if(isdigit(s[i])) t[j++]=s[i];
	t[j]=0;
	puts(t);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
