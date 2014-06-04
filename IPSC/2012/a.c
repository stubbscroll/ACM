#include <stdio.h>

int x,y;
char m[512][512];

int c(int i,int j) {
	if(i<0 || j<0 || i>=x || j>=y) return 0;
	return m[i][j];
}

int main() {
	int cases,i,j,r;
	scanf("%d",&cases);
	while(cases--) {
		scanf("%d %d",&x,&y);
		r=0;
		for(i=0;i<x;i++) scanf("%s",m[i]);
		for(i=0;i<x;i++) for(j=0;j<y;j++) if(m[i][j]=='o') {
			if(c(i-1,j)=='v' && c(i+1,j)=='^') m[i-1][j]=m[i][j]=m[i+1][j]=' ',r++;
			if(c(i,j-1)=='>' && c(i,j+1)=='<') m[i][j-1]=m[i][j]=m[i][j+1]=' ',r++;
		}
		printf("%d\n",r);
	}
	return 0;
}
