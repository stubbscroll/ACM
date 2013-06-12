/* solves both B1 and B2 */

#include <stdio.h>
#include <string.h>

int in[2222],out[2222];
int front[2222];
int n,us;

int size[10000],sn;
char dp[2][10000];

void solve() {
	int i,we,j,place=0,at;
	int prev=0,cur=1;
	sn=0;
	for(i=0;i<n;i++) if(!in[i]) {
		we=0;
		j=0;
		at=i;
		while(at>=0) {
			if(we) place++;
			j++;
			if(at==us) we=1,place=0;
			at=front[at];
		}
		if(!we) size[sn++]=j;
	}
	memset(dp,0,sizeof(dp));
	dp[prev][0]=1;
	for(i=0;i<sn;i++) {
		for(j=0;j<1001;j++) dp[cur][j]=0;
		for(j=0;j<1001;j++) if(dp[prev][j]) {
			dp[cur][j]=1;
			dp[cur][j+size[i]]=1;
		}
		prev^=1; cur^=1;
	}
	for(i=0;i<1001;i++) if(dp[prev][i]) printf("%d\n",1+i+place);
}

int main() {
	int i,z;
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(in));
	memset(front,-1,sizeof(in));
	scanf("%d %d",&n,&us);
	us--;
	for(i=0;i<n;i++) {
		scanf("%d",&z);
		z--;
		if(z>=0) {
			front[i]=z;
			in[z]++;
			out[i]++;
		}
	}
	solve();
	return 0;
}
