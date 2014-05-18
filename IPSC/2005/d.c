/* solution to dance dance revolution, both inputs.
   algorithm: dynamic programming
   note: the sample input is weak, i managed to pass the easy input
   with a wrong program. there are few cases in both input files. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 15
#define MAXTID 400
#define MAXCOMB 400

int snoob(int x) {
	int s=x&-x, r=x+s, o=x^r;
	o=(o>>2)/s;
	return r|o;
}

int bc[1<<MAX];
int step[MAXTID];
int maxt;
int dp[MAXTID][MAXCOMB];
int comb[MAXCOMB],combs;

int main() {
	int i,j,A,L,D,T,M,t,n,diff,prev,cur;
	for(i=1,bc[0]=0;i<(1<<MAX);i++) bc[i]=bc[i>>1]+(1&i);
	while(scanf("%d %d %d %d %d",&A,&L,&D,&T,&M),A) {
		if(A>MAX) puts("increase MAX and recompile"),exit(1);
		memset(step,0,sizeof(step));
		maxt=0;
		for(i=0;i<M;i++) {
			scanf("%d %d",&t,&n);
			if(maxt<t) maxt=t;
			if(maxt>=MAXTID) puts("increase MAXTID and recompile"),exit(1);
			while(n--) scanf("%d",&j),step[t]|=1<<(j-1);
		}
		combs=0,n=(1<<L)-1;
		do {
			if(combs>=MAXCOMB) puts("increase MAXCOMB and recompile"),exit(1);
			comb[combs++]=n;
			n=snoob(n);
		} while(n<(1<<A));
		for(i=0;i<combs;i++) dp[0][i]=0;
		for(t=1;t<=maxt;t++) for(i=0;i<combs;i++) {
			/* do nothing */
			dp[t][i]=dp[t-1][i];
			for(j=0;j<combs;j++) {
				diff=L-bc[comb[i]&comb[j]];
				prev=t-D-(diff>>1);
				if(prev>=0) {
					cur=dp[prev][j];
					if(step[t] && (comb[i]&step[t])==step[t]) cur++;
					if(dp[t][i]<cur) dp[t][i]=cur;
				}
			}
		}
		for(i=n=0;i<combs;i++) if(n<dp[maxt][i]) n=dp[maxt][i];
		printf("%d move(s)\n",n);
	}
	return 0;
}
