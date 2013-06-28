#include <stdio.h>
#include <string.h>

int main() {
	int T,f[128],i,a;
	char s[666];
	scanf("%d",&T);
	while(T--) {
		scanf("%s",s);
		memset(f,0,sizeof(f));
		for(i=0;s[i];i++) f[(int)s[i]]++;
		a=f['M'];
		if(a>f['A']/3) a=f['A']/3;
		if(a>f['R']/2) a=f['R']/2;
		if(a>f['G']) a=f['G'];
		if(a>f['I']) a=f['I'];
		if(a>f['T']) a=f['T'];
		printf("%d\n",a);
	}
	return 0;
}
