/* solution for urban planning, easy input
   observation: the reachability list thing in easy implies that the graph
   is a path.
   algorithm: sort nodes by degree and output all ordered adjacent pairs */

#include <stdio.h>
#include <stdlib.h>

#define MAXV 300

int deg[MAXV];
int order[MAXV];
int n;

void solve() {
	int i,j,b,bix;
	char s[MAXV+1];
	scanf("%d",&n);
	if(n>MAXV) printf("increase MAXV to %d and recompile\n",n),exit(1);
	for(i=0;i<n;i++) {
		scanf("%s",s);
		for(deg[i]=j=0;j<n;j++) deg[i]+=s[j]-'0';
	}
	for(i=0;i<n;i++) {
		for(b=bix=-1,j=0;j<n;j++) if(b<deg[j]) b=deg[j],bix=j;
		deg[bix]=-1;
		order[i]=bix;
	}
	printf("%d\n",n-1);
	for(i=0;i<n-1;i++) printf("%d %d\n",order[i]+1,order[i+1]+1);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
