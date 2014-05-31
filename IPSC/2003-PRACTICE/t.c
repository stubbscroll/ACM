/* solution to strange numbers, both input
   algorithm: observe that the ancient system is very similar
   to gray codes */

#include <stdio.h>
#include <string.h>

char s[10000],t[10000];

/* convert from ancient to binary */
void solve1() {
	int i,j,k;
	printf("b ");
	if(strlen(s)<2) { puts(s); return; }
	strcpy(t,s);
	for(i=3;s[i];i++) for(j=i,k=2;s[j];j++,k++) s[j]^=(t[k]&1);
	printf("%c %c",s[0],s[1]^1);
	for(i=2;s[i];i++) printf(" %c",s[i]^1^(s[1]&1));
	putchar('\n');
}

/* convert from binary to ancient */
void solve2() {
	int i;
	printf("a ");
	if(strlen(s)<2) { puts(s); return; }
	printf("%c %c",s[0],s[1]^1);
	for(i=2;s[i];i++) printf(" %c",s[i]^(s[i-1]&1));
	putchar('\n');
}

void solve() {
	char c[2];
	scanf("%s %9999s",c,s);
	if(c[0]=='a') solve1();
	else solve2();
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
