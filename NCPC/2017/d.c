#include <stdio.h>

int q[1048576],qs,qe;
char vis[1048576];

int main() {
	int n,k,i,j,v;
	char s[21];
	scanf("%d %d",&n,&k);
	qs=qe=0;
	for(i=0;i<n;i++) {
		scanf("%s",s);
		for(v=j=0;j<k;j++) v=v*2+s[j]-48;
		if(!vis[v]) {
			vis[v]=1;
			q[qe++]=v;
		}
	}
	while(qs<(1<<k)-1) {
		int cur=q[qs++];
		for(i=0;i<k;i++) {
			int x2=cur^(1<<i);
			if(!vis[x2]) {
				vis[x2]=1;
				q[qe++]=x2;
			}
		}
	}
	for(i=k-1;i>=0;i--) printf("%c",q[qs]&(1<<i)?'1':'0');
	putchar('\n');
	return 0;
}
