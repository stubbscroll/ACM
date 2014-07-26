/* solution for exploring the cave, hard input
   algorithm: construct graph as described in the paper "Magic numbers and
   ternary alphabet" (Galina Jiraskova, 2009). the construction cannot
   possibly be intuitively explained here, so please set aside several hours
   and read the paper yourself. to make construction slightly easier, i only
   care about the case where d >= 2^(n-1)-1 which i achieve by reducing n. my
   final trick is to reverse node indexes to make the automaton compatible
   with the problem statement (start node i 0 instead of n-1).
*/

#include <stdio.h>
#include <string.h>

#define MAX 22

char g[MAX][MAX];
int n,d;

void printgraph() {
	int i,j,k,ne=0;
	for(i=0;i<n;i++) for(j=0;j<n;j++) for(k=0;k<3;k++) if(g[i][j]&(1<<k)) ne++;
	printf("%d\n",ne);
	for(i=0;i<n;i++) for(j=0;j<n;j++) for(k=0;k<3;k++) if(g[i][j]&(1<<k)) printf("%d %d %c\n",i,j,k+'a');
	printf("\n");
}

void solve() {
	int i,j,from,prev,a;
	scanf("%d %d",&n,&d);
	/* d > 2^n: no solution */
	if(d>(1<<n)) { puts("-1\n"); return; }
	/* 1 dfa state: 0 edges */
	/* reduce n until we have d >= 2^(n-1)+1 */
	while(d<(1<<(n-1))+1) n--;
	memset(g,0,sizeof(g));
	/* hardcode some cases too small for the proper algorithm */
	if(n==0 && d==1) { n=1; g[0][0]=7; goto end; }
	if(n==1 && d==2) { g[0][0]=1; goto end; }
	if(n==2 && d==3) { g[0][1]=1; goto end; }
	if(n==2 && d==4) { g[0][0]=1; g[0][1]=3; g[1][1]=1; goto end; }
	/* create A_n as described in paper p 5-6, but with reversed node indexes */
	for(i=0;i<n-1;i++) g[i+1][i]|=3;
	for(i=0;i<n;i++) g[i][n-1]|=2;
	g[0][0]|=3; g[1][0]|=4;
	if(d==1<<n) g[n-1][n-1]|=4;
	else {
		d-=(1<<(n-1))+1;
		for(a=1,prev=-1,from=0,i=n-1;i;i--) while(d>=(1<<i)-1) {
			/* add a binary tree of size 2^i-1 */
			for(j=a-(prev==i);j<=n-i-1;j++) g[n-from-1][n-j-1]|=4;
			/* if we are creating transition from n-2, remove edge n-2 -> n-1 c */
			if(from==n-2) g[n-from-1][0]^=4;
			from++; d-=(1<<i)-1; prev=i;
		}
	}
end:
	printgraph();
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
