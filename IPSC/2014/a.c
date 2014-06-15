/* solution for adjusting passwords, both inputs
   algorithm: take minimum of these two alternatives:
   - press enter and type correct password
   - backspace until P and Q have common prefix and type the rest */

#include <stdio.h>
#include <string.h>

char p[111],q[111];

void solve() {
	int best,i,j,z;
	char seq[223],try[223];
	scanf("%s %s",p,q);
	/* alternative 1: delete */
	for(i=0;p[i] && p[i]==q[i];i++);
	for(z=0,j=i;q[j];j++) try[z++]='<';
	for(j=i;p[j];j++) try[z++]=p[j];
	try[z++]='*';
	try[z]=0;
	/* alternative 2: press enter and type whole password */
	strcpy(seq,try); best=z;
	z=0;
	try[z++]='*';
	for(i=0;p[i];i++) try[z++]=p[i];
	try[z++]='*';
	try[z]=0;
	if(z<best) puts(try);
	else puts(seq);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
