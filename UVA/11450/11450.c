#include <stdio.h>
#include <string.h>

int k[20][20];
int kn[20];
int m,c;

char can[2][222];

int solve() {
	int prev=0,cur=1,i,j,z;
	memset(can,0,sizeof(can));
	can[prev][0]=1;
	for(i=0;i<c;i++) {
		memset(can[cur],0,222);
		for(j=0;j<=m;j++) if(can[prev][j]) {
			for(z=0;z<kn[i];z++) if(j+k[i][z]) can[cur][j+k[i][z]]=1;
		}
		prev^=1; cur^=1;
	}
	for(i=m;i>=0;i--) if(can[prev][i]) break;
	return i;
}

int main() {
	int T,i,j;
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d",&m,&c);
		for(i=0;i<c;i++) {
			scanf("%d",&kn[i]);
			for(j=0;j<kn[i];j++) scanf("%d",&k[i][j]);
		}
		i=solve();
		if(i<0) puts("no solution");
		else printf("%d\n",i);
	}
	return 0;
}
