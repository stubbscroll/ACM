#include <stdio.h>
#include <string.h>

int pic[32][32];

char taken[32];
int path[32];
int abs(int a) { return a<0?-a:a; }
int fancyabs(int a,int b) {
	if(a<128) a=128;
	if(b<128) b=128;
	return abs(a-b);
}
void order() {
	int start=15,z,i,j,best,bestix,cur;
	memset(taken,0,32);
	taken[start]=1;
	path[0]=start;
	for(z=1;z<32;z++) {
		best=1231231231,bestix=-1;
		for(i=0;i<32;i++) if(!taken[i]) {
			for(cur=j=0;j<32;j++) cur+=fancyabs(pic[start][j],pic[i][j]);
			if(best>cur) best=cur,bestix=i;
		}
		path[z]=bestix;
		taken[bestix]=1;
		start=bestix;
	}
	for(i=0;i<32;i++) printf("%d,",path[i]);
}

int main() {
	int T,no,i,j;
	scanf("%d",&T);
	for(no=1;no<=T;no++) {
		for(j=0;j<32;j++) for(i=0;i<32;i++) scanf("%d",&pic[i][j]);
		if(no!=29) continue;
		order();
	}
	return 0;
}
