/* algorithm: find cycle by searching for a prefix of the sequencde */

#include <stdio.h>
#include <string.h>

char s[4000001];
char t[4000001];

char z[1000001];

void getseq(char *s) {
	int i,j,v;
	scanf("%s",z);
	for(i=j=0;z[i];i++) {
		v=z[i]-33;
		s[j++]=v/27+48;
		s[j++]=v/9%3+48;
		s[j++]=v/3%3+48;
		s[j++]=v%3+48;
	}
	s[j]=0;
}

void solve(char *s) {
	int n=strlen(s),i,j,z,len,k;
	/* try to find cycle length */
	z=100;
	for(i=z;i<n-z;i++) {
		for(j=0;j<z;j++) if(s[j]!='2' && s[j+i]!='2' && s[j]!=s[j+i]) goto fail;
		goto ok;
	fail:;
	}
	printf("error, no cycle\n");
ok:
	len=i;
	for(i=0;i<n;i++) if(s[i]=='2') {
		for(k=-2;k<3;k++) if(i+len*k>=0 && i+len*k<n && s[i+len*k]!='2') {
			putchar(s[i+len*k]);
			goto ok2;
		}
		putchar('0');
	ok2:;
	}
	putchar('\n');
}

int main() {
	getseq(s);
	solve(s);
	return 0;
}
