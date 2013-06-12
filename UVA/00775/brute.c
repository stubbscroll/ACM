/* stupid brute force algorithm */

/* to my huge surprise, this submission actually passed. i was planning to
   make at least 2 more submissions with increasingly better algorithms */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256

char g[MAX][MAX];
int n;

char taken[MAX];
int path[MAX];

int btr(int at,int num) {
	int i;
	if(num==n) return g[at][0];
	for(i=0;i<n;i++) if(g[at][i] && !taken[i]) {
		taken[i]=1;
		path[num]=i;
		if(btr(i,num+1)) return 1;
		taken[i]=0;
	}
	return 0;
}

int main() {
	char s[16];
	int a,b,i;
	while(scanf("%d",&n)==1) {
		memset(g,0,sizeof(g));
		while(1) {
			scanf("%s",s);
			if(s[0]=='%') break;
			a=strtol(s,0,10);
			scanf("%d",&b);
			--a; --b;
			g[a][b]=g[b][a]=1;
		}
		memset(taken,0,n);
		taken[0]=1;
		path[0]=0;
		if(!btr(0,1)) puts("N");
		else {
			for(i=0;i<n;i++) printf("%d ",path[i]+1);
			printf("%d\n",path[0]+1);
		}
	}
	return 0;
}
