/* find articulation point using recursive dfs */

#include <stdio.h>
#include <string.h>

/* find all articulation points in connected undirected graph! */

#define MAXV 111
#define MAXE 99999

int n,ne;               /* number of nodes, number of edges */
int from[MAXE],to[MAXE];/* edge i: from[i] to[i] */
int gs[MAXV+1];         /* gs[i]: start of edges from i, gs[i+1]: end */

char vis[MAXV];
int ud[MAXV];           
int ulow[MAXV];
int resn;               /* counter */

char isartic[MAXV];
int ac[MAXV];           /* list of articulation points */
int acn;                /* number of articulation points */

void dfsvisit(int v,int p) {
	int ch=0,i,w;
	vis[v]=1;
	ud[v]=ulow[v]=++resn;
	for(i=gs[v];i<gs[v+1];i++) {
		w=to[i];
		if(w==p) continue;
		if(vis[w]) {
			if(ulow[v]>ud[w]) ulow[v]=ud[w];
		} else {
			dfsvisit(w,v);
			if(ulow[v]>ulow[w]) ulow[v]=ulow[w];
			if(ulow[w]>=ud[v] && p>-1 && !isartic[v]) isartic[v]=1,ac[acn++]=v;
			ch++;
		}
	}
	if(p<0 && ch>1 && !isartic[v]) isartic[v]=1,ac[acn++]=v;
}

void articulation(int root) {
	resn=acn=0;
	memset(vis,0,n);
	memset(isartic,0,n);
	dfsvisit(0,-1);
}

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

char g[MAXV][MAXV];
int a[MAXV],an;

#define MAXS 11111
int main() {
	int i;
	static char s[MAXS+3];
	while(1) {
		fgets(s,MAXS,stdin);
		sscanf(s,"%d",&n);
		if(!n) break;
		memset(g,0,sizeof(g));
		ne=0;
		while(1) {
			fgets(s,MAXS,stdin);
			an=sscanf(s,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
				&a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8],&a[9],
				&a[10],&a[11],&a[12],&a[13],&a[14],&a[15],&a[16],&a[17],&a[18],&a[19],
				&a[20],&a[21],&a[22],&a[23],&a[24],&a[25],&a[26],&a[27],&a[28],&a[29],
				&a[30],&a[31],&a[32],&a[33],&a[34],&a[35],&a[36],&a[37],&a[38],&a[39],
				&a[40],&a[41],&a[42],&a[43],&a[44],&a[45],&a[46],&a[47],&a[48],&a[49],
				&a[50],&a[51],&a[52],&a[53],&a[54],&a[55],&a[56],&a[57],&a[58],&a[59],
				&a[60],&a[61],&a[62],&a[63],&a[64],&a[65],&a[66],&a[67],&a[68],&a[69],
				&a[70],&a[71],&a[72],&a[73],&a[74],&a[75],&a[76],&a[77],&a[78],&a[79],
				&a[80],&a[81],&a[82],&a[83],&a[84],&a[85],&a[86],&a[87],&a[88],&a[89],
				&a[90],&a[91],&a[92],&a[93],&a[94],&a[95],&a[96],&a[97],&a[98],&a[99],
				&a[100],&a[101],&a[102],&a[103],&a[104],&a[105],&a[106],&a[107],&a[108],&a[109]);
			if(an==1 && !a[0]) break;
			a[0]--;
			for(i=1;i<an;i++) {
				a[i]--;
				if(!g[a[0]][a[i]]) {
					g[a[0]][a[i]]=g[a[i]][a[0]]=1;
					from[ne]=a[0]; to[ne++]=a[i]; 
					from[ne]=a[i]; to[ne++]=a[0]; 
				}
			}
		}
		countingsort();
		articulation(0);
		printf("%d\n",acn);
	}
	return 0;
}
