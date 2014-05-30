/* solution to the tiling problem, both inputs
   algorithm: bipartite matching */

#include <stdio.h>
#include <string.h>

#define MAX 400
int x,y;
char s[MAX][MAX+1];

int id[MAX][MAX];             /* mapping (x,y) -> node-id */
int bx[MAX*MAX],by[MAX*MAX]; /* mapping node-id -> (x,y) */

/* maximum matching in bipartite graph!
   n nodes on left side, m nodes on right side
   g[i][j]=1 if edge, 0<=i<n, 0<=j<m
   returns number of edges
   runtime: O(nm)
*/
#define MAXV 10945
char g[MAXV][MAXV];         /* [i][j]: edge between i on the left and j on the right */
int n,m;                    /* left, right */
int mate[MAXV];             /* mate for right node (or -1 if unmatched) */
int parent[2*MAXV];

int bipartite() {
	int i,j,r=0,cur,qs,qe=0;
	static int q[2*MAXV];
	memset(mate,-1,m*sizeof(int));
	memset(parent,-1,(n+m)*sizeof(int));
	for(i=0;i<n;i++) {
		qs=0;
		q[qe++]=i;
		while(qs<qe) {
			cur=q[qs++];
			if(cur<n) {
				for(j=n;j<m+n;j++) if(g[cur][j-n] && parent[j]<0) {
					parent[j]=cur;
					q[qe++]=j;
					if(mate[j-n]<0) {
						while(j>-1) {
							mate[j-n]=parent[j];
							j=parent[parent[j]];
						}
						r++;
						goto ok;
					}
				}
			} else {
				q[qe++]=mate[cur-n];
				parent[mate[cur-n]]=cur;
			}
		}
		/* unmatched node, we failed */
		break;
	ok:
		while(qe) parent[q[--qe]]=-1;
	}
	return r;
}

int first=1;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

int solve() {
	int i,j,N,M,x2,y2,d;
	scanf("%d %d",&x,&y);
	if(x+y<1) return 0;
	if(first) first=0;
	else putchar('\n');
	if(x>MAX || y>MAX) { printf("increase MAX to %d and recompile\n",x>y?x:y); return 0; }
	for(i=0;i<x;i++) scanf("%s",s[i]);
	/* parse input and create mapping to node number */
	n=m=0;
	for(i=0;i<x;i++) for(j=0;j<y;j++) if(s[i][j]=='#') {
		if((i+j)&1) n++;
		else m++;
	}
	if(n>MAXV || m>MAXV) { printf("increase MAXV to %d and recompile\n",n>m?n:m); return 0; }
	if(n!=m) { puts("IMPOSSIBLE"); return 1; }
	for(N=M=i=0;i<x;i++) for(j=0;j<y;j++) {
		if(s[i][j]=='#') {
			if((i+j)&1) bx[N]=i,by[N]=j,id[i][j]=N++;
			else bx[N+M]=i,by[N+M]=j,id[i][j]=M++;
		} else id[i][j]=-1;
	}
	/* create graph */
	for(i=0;i<n;i++) for(j=0;j<m;j++) g[i][j]=0;
	for(i=0;i<x;i++) for(j=0;j<y;j++) if(((i+j)&1) && s[i][j]=='#') {
		for(d=0;d<4;d++) {
			x2=i+dx[d]; y2=j+dy[d];
			if(x2<0 || y2<0 || x2>=x || y2>=y || s[x2][y2]=='.') continue;
			g[id[i][j]][id[x2][y2]]=1;
		}
	}
	if(bipartite()<n) { puts("IMPOSSIBLE"); return 1; }
	/* find actual tiling */
	for(i=0;i<x;i++) for(j=0;j<y;j++) if(((1+i+j)&1) && s[i][j]=='#') {
		d=mate[id[i][j]];
		x2=bx[d]; y2=by[d];
		if(i-x2<0) s[i][j]='t',s[x2][y2]='b';
		else if(i-x2>0) s[i][j]='b',s[x2][y2]='t';
		else if(j-y2<0) s[i][j]='l',s[x2][y2]='r';
		else if(j-y2>0) s[i][j]='r',s[x2][y2]='l';
		else printf("error: at %d %d, mate ix %d at %d %d\n",i,j,d,x2,y2);
	}
	for(i=0;i<x;i++) puts(s[i]);
	return 1;
}

int main() {
	while(solve());
	return 0;
}
