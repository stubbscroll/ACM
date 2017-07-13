/* algorithm: try all pairs and find common suffix+previx */

#include <stdio.h>
#include <string.h>

char s[10][5];

void solve() {
	int i,j,k;
	for(i=0;i<10;i++) scanf("%s",s[i]);
	for(i=0;i<10;i++) for(j=0;j<10;j++) if(i!=j) {
		if(s[i][3]==s[j][0]) { printf("%s%s",s[i],s[j]+1); goto ok; }
		if(s[i][2]==s[j][0] && s[i][3]==s[j][1]) { printf("A%s%s",s[i],s[j]+2); goto ok; }
		if(s[i][1]==s[j][0] && s[i][2]==s[j][1] && s[i][3]==s[j][2]) { printf("AA%s%s",s[i],s[j]+3); goto ok; }
		if(!strcmp(s[i],s[j])) { printf("AAA%s",s[i]); goto ok; }
	}
	puts("FAIL");
	return;
ok:
	for(k=0;k<10;k++) if(k!=i && k!=j) printf("%s",s[k]);
	putchar('\n');
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
