/* solution for game on a conveyor belt, easy input
   algorithm: search game tree with minimax */

#include <stdio.h>

int res[21][1<<20];

int n,m;
int pos[20];
char s[101];

int btr(int at,int mask) {
	int i;
	for(i=0;i<m;i++) if((mask&(1<<i)) && pos[i]-at<0) mask-=1<<i;
	if(res[at][mask]>-1) return res[at][mask];
	for(i=0;i<m;i++) if(mask&(1<<i)) if(!btr(at+1,mask-(1<<i))) return res[at][mask]=1;
	return res[at][mask]=0;
}

void solve() {
	int i,j,k;
	scanf("%d %s",&n,s);
	for(i=j=0;s[i];i++) if(s[i]=='1') pos[j++]=i;
	m=j;
	for(i=0;i<=j;i++) for(k=0;k<(1<<j);k++) res[i][k]=-1;
	printf("%s\n",btr(0,(1<<j)-1)?"Adam":"Betka");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
