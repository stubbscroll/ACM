/* solution for maximum enjoyment, both inputs
   algorithm: formulate as linear programming (each vertex split into layers
   as described in editorial), run simplex. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

int c[MAX][MAX];  /* capacities */
int n,s,t,L;      /* number of nodes, source, sink, max number of links */

int map[MAX][MAX];/* mapping from edges to LP variable indexes */
int mn;           /* number of non-zero edges */

#define MAXEQ 2018
#define MAXVAR 6588
#define EPS 1e-9
#define INF 1e50

double lpmax[MAXVAR];     /* objective function to maximize */
double lpconst;           /* constant in expression */

double eq[MAXEQ][MAXVAR]; /* coefficients */
double eqrhs[MAXEQ];      /* right-hand side */
int eqn;                  /* number of equations */
int vn;                   /* number of variables */

void initsimplex() {
	int i,j,need=eqn;
	/* add need extra variables, append identity matrix to the right */
	if(vn+need>MAXVAR) printf("increase MAXVAR to %d and recompile\n",vn+need),exit(1);
	for(i=0;i<eqn;i++) for(j=0;j<need;j++) eq[i][j+vn]=i==j;
	for(i=0;i<eqn;i++) lpmax[i+vn]=0;
	for(i=0;i<vn;i++) lpmax[i]=-lpmax[i];
	vn+=need;
}

void pivot(int lx,int e) {
	double m;
	int i,j;
	/* normalize row lx */
	m=eq[lx][e];
	for(i=0;i<vn;i++) eq[lx][i]/=m;
	eqrhs[lx]/=m;
	/* from each row i, subtract multiple of eq[i][e] of row lx */
	for(i=0;i<eqn;i++) if(i!=lx && eq[i][e]) {
		m=eq[i][e];
		for(j=0;j<vn;j++) eq[i][j]-=m*eq[lx][j];
		eqrhs[i]-=m*eqrhs[lx];
	}
	/* subtract multiple from objective function */
	m=lpmax[e];
	if(m) for(j=0;j<vn;j++) lpmax[j]-=m*eq[lx][j];
	lpconst-=m*eqrhs[lx];
}

double simplex() {
	double best,r;
	int i,e,ix;
	initsimplex();
	while(1) {
		/* select variable whose coefficient in the objective function
		   is negative, and pick the maximal among these */
		ix=-1; best=INF;
		for(e=0;e<vn;e++) if(best>lpmax[e]) best=lpmax[e],ix=e;
		if(best>=-EPS) break;
		e=ix;
		/* find variable that maximizes ratio rhs/e */
		ix=-1; best=INF;
		for(i=0;i<eqn;i++) if(eq[i][e]>EPS) {
			r=eqrhs[i]/eq[i][e];
			if(best>r) best=r,ix=i;
		}
 		if(best>=INF) return INF; /* unbounded */
		pivot(ix,e);
	}
	return lpconst;
}

char kill[MAXVAR];

void solve() {
	int i,j,k,l,z;
	scanf("%d %d %d %d",&n,&s,&t,&L);
	if(n>MAX) printf("increase MAX to %d and recompile\n",n),exit(1);
	for(i=0;i<n;i++) for(j=0;j<n;j++) scanf("%d",&c[i][j]);
	/* LP stuff starts here */
	eqn=mn=0;
	/* create mapping from edges to LP variables */
	for(i=0;i<n;i++) for(j=0;j<n;j++) if(c[i][j]) map[i][j]=mn++;
	vn=mn*(L+0);
	if(vn>MAXVAR) printf("increase MAXVAR to %d and recompile\n",vn),exit(1);
	/* create equations for capacity constraints: sum of all layers of a single
	   edge shouldn't exceed the capacity */
	for(i=0;i<n;i++) for(j=0;j<n;j++) if(c[i][j]) {
		if(eqn==MAXEQ) puts("increase MAXEQ and recompile"),exit(1);
		for(z=0;z<vn;z++) eq[eqn][z]=0;
		l=map[i][j];
		for(k=0;k<L;k++) eq[eqn][l+k*mn]=1;
		eqrhs[eqn++]=c[i][j];
	}
	/* flow conservation constraints: for a given vertex, incoming flow should
	   equal outgoing flow (except for source and sink) */
	/* this is an equality equation, so add two inequalities */
	for(l=0;l<L-1;l++) for(i=0;i<n;i++) if(i!=s && i!=t) {
		if(eqn+2>MAXEQ) puts("increase MAXEQ and recompile"),exit(1);
		for(z=0;z<vn;z++) eq[eqn][z]=0;
		for(j=0;j<n;j++) if(c[i][j]) {
			eq[eqn][map[j][i]+l*mn]=1;       /* incoming edge */
			eq[eqn][map[i][j]+(l+1)*mn]=-1;  /* outgoing edge */
		}
		eqrhs[eqn++]=0;
		for(z=0;z<vn;z++) eq[eqn][z]=0;
		for(j=0;j<n;j++) if(c[i][j]) {
			eq[eqn][map[j][i]+l*mn]=-1;      /* incoming edge */
			eq[eqn][map[i][j]+(l+1)*mn]=1;   /* outgoing edge */
		}
		eqrhs[eqn++]=0;
	}
	/* objective: maximize flow (for instance by maximizing outgoing flow from
	   source at layer 0 */
	for(i=0;i<vn;i++) lpmax[i]=0;
	lpconst=0;
	for(i=0;i<n;i++) if(c[s][i]) lpmax[map[s][i]]=1;
	/* some variables are forced to be 0 or else they cause illegal situations.
	   remove them from the system altogether */
	for(i=0;i<vn;i++) kill[i]=0;
	/* flow can only start in source at level 0 */
	for(i=0;i<n;i++) if(i!=s) for(j=0;j<n;j++) if(c[i][j]) kill[map[i][j]]=1;
	/* flow can only end in sink from level L */
	for(i=0;i<n;i++) for(j=0;j<n;j++) if(j!=t && c[i][j]) kill[map[i][j]+(L-1)*mn]=1;
	/* forbid self-loops to source */
	for(l=0;l<L;l++) for(i=0;i<n;i++) if(c[i][s]) kill[map[i][s]+l*mn]=1;
	/* horizontal contraction */
	for(i=0;i<eqn;i++) for(j=k=0;j<vn;j++) if(!kill[j]) eq[i][k++]=eq[i][j];
	for(j=k=0;j<vn;j++) if(!kill[j]) lpmax[k++]=lpmax[j];
	vn=k;
	printf("%.10f\n",simplex()/8);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
