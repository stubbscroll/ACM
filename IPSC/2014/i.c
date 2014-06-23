/* solution for intrepid cave explorer, both inputs
   algorithm: use huffman coding at each node with subtree sizes for all
   children. runtime O(n^3), i think */

#include <stdio.h>
#include <string.h>

int n;
int parent[21111]; /* parent of node */
int num[21111];    /* size of subtree at node */
int len[21111];    /* length of prefix for node */

int numbtr(int at) {
	int r=1,i;
	for(i=at+1;i<n;i++) if(parent[i]==at) r+=numbtr(i);
	return num[at]=r;
}

int nodelen[44444]; /* number of dots for child */
int sizes[44444];   /* size of subtree for child */
int next[44444];    /* successor */
char taken[44444];

void huffman(int m) {
	int i,M=m,j;
	int best[2],bestix[2];
	if(m<2) { nodelen[0]=0; return; }
	for(i=0;i<m;i++) taken[i]=0,next[i]=-1;
	while(m<M+M-1) {
		best[0]=best[1]=bestix[0]=bestix[1]=1000000000;
		for(i=0;i<m;i++) if(!taken[i] && best[1]>sizes[i]) {
			if(best[0]>sizes[i]) {
				best[1]=best[0]; bestix[1]=bestix[0];
				best[0]=sizes[i],bestix[0]=i;
			} else best[1]=sizes[i],bestix[1]=i;
		}
		taken[bestix[0]]=taken[bestix[1]]=1;
		sizes[m]=sizes[bestix[0]]+sizes[bestix[1]];
		taken[m]=0;
		next[m]=-1;
		next[bestix[0]]=next[bestix[1]]=m++;
	}
	for(i=0;i<M;i++) {
		nodelen[i]=0;
		j=next[i];
		while(j>-1) j=next[j],nodelen[i]++;
	}
}

int btr(int at,int len) {
	int r=0,i,j;
	for(j=0,i=at+1;i<n;i++) if(parent[i]==at) sizes[j++]=num[i];
	huffman(j);
	for(j=0,i=at+1;i<n;i++) if(parent[i]==at) r+=len+nodelen[j]+btr(i,len+nodelen[j]),j++;
	return r;
}

void solve() {
	int i;
	scanf("%d",&n);
	parent[0]=-1;
	for(i=1;i<n;i++) scanf("%d",&parent[i]),parent[i]--;
	/* calculate subtree size for each node */
	numbtr(0);
	printf("%d\n",btr(0,0));
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
