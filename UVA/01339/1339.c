#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compc(const void *A,const void *B) {
	const char *a=A,*b=B;
	if(*a>*b) return -1;
	if(*a<*b) return 1;
	return 0;
}

void canon(char *s) {
	char m[128];
	int i;
	memset(m,0,128);
	for(i=0;s[i];i++) m[(int)s[i]]++;
	qsort(m,128,1,compc);
	strcpy(s,m);
}

int main() {
	char s[111],t[111];
	while(scanf("%s %s",s,t)==2) canon(s),canon(t),puts(strcmp(s,t)?"NO":"YES");
	return 0;
}
