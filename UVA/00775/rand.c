/* solution to 775 using angluin/valente's randomized algorithm */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXV 256
#define MAXE 65536

int from[MAXE],to[MAXE];
int gs[MAXV+1];
int n,ne;

void countingsort() {
  static int newto[MAXE];
  int i,j;
  for(i=0;i<=n;i++) gs[i]=0;
  for(i=0;i<ne;i++) gs[from[i]]++;
  for(i=1;i<n;i++) gs[i]+=gs[i-1];
  gs[n]=ne;
  for(i=0;i<ne;i++) {
    j=--gs[from[i]];
    newto[j]=to[i];
  }
  for(i=0;i<ne;i++) to[i]=newto[i];
  for(i=0;i<n;i++) for(j=gs[i];j<gs[i+1];j++) from[j]=i;
}

void addedge(int a,int b) {
	from[ne]=a; to[ne++]=b;
}

char taken[MAXV];
int path[MAXV];

int randham(int s) {
	static int temp[MAXV];
	int pn=1,i,y,j,k;
	memset(taken,0,n);
	path[0]=s;
	taken[s]=1;
	while(1) {
		if(pn==n) for(i=gs[s];i<gs[s+1];i++) if(to[i]==path[n-1]) return 1;
		i=gs[path[pn-1]]+rand()%(gs[path[pn-1]+1]-gs[path[pn-1]]);
		y=to[i];
		if(!taken[y]) path[pn++]=y,taken[y]=1;
		else {
			for(i=0;i<pn;i++) if(path[i]==y) break;
			for(j=i;j<pn;j++) temp[j]=path[j];
			for(k=pn-1,j=i+1;j<pn;j++,k--) path[k]=temp[j];
		}
	}
	return 0;
}

int main() {
	char s[16];
	int a,b,i;
	while(scanf("%d",&n)==1) {
		ne=0;
		while(1) {
			scanf("%s",s);
			if(s[0]=='%') break;
			a=strtol(s,0,10);
			scanf("%d",&b);
			addedge(a-1,b-1);
			addedge(b-1,a-1);
		}
		countingsort();
		randham(0);
		for(i=0;i<n;i++) printf("%d ",path[i]+1);
		printf("%d\n",path[0]+1);
	}
	return 0;
}
