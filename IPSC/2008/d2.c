/* solution for discover all sets, hard input
   algorithm: backtracking sped up by bitmasks and precalculation.
   optimizations:
   - fix a variable property. each search depth searches for one value using
     precalculated lists.
   - quickly check if a card is eligible by bitwise operators
   solving hard input takes 450 seconds
*/

#include <stdio.h>

#define MAXSET 5000
#define MAXPROP 10
#define MAXVAL 8

typedef unsigned long long ull;

int n,m,k;
int set[MAXSET][MAXPROP];
int list[MAXVAL][MAXSET]; /* for each value, list of cards */
int ln[MAXVAL];           /* number of cards with value */
ull setmask[MAXSET];      /* helper mask for card */
ull fixedmask,varmask;

ull pascal[MAXSET+1][MAXPROP+1];

void genpascal() {
	int i,j;
	for(i=0;i<=MAXSET;i++) {
		pascal[i][0]=1;
		if(i<=MAXPROP) pascal[i][i]=1;
		for(j=1;j<i && j<=MAXPROP;j++) pascal[i][j]=pascal[i-1][j-1]+pascal[i-1][j];
	}
}

ull btr(int at,ull cur) {
	int i,j;
	ull r=0;
	if(at==m) return 1;
	/* at level at, pick value at at property hi */
	for(j=0;j<ln[at];j++) {
		i=list[at][j];
		/* check if fixed properties are satisfied */
		if((setmask[i]&cur&fixedmask)!=(cur&fixedmask)) continue;
		/* check if variable properties aren't picked previously */
		if(setmask[i]&cur&varmask) continue;
		r+=btr(at+1,cur|setmask[i]);
	}
	return r;
}

void solve() {
	int i,j,l,num,mask,hi;
	ull r,cur;
	scanf("%d %d %d",&n,&m,&k);
	for(i=0;i<k;i++) for(j=0;j<n;j++) scanf("%d",&set[i][j]),set[i][j]--;
	r=0;
	/* count sets where all values are equal for each property */
	for(i=0;i<k;i++) {
		for(num=j=0;j<k;j++) if(j!=i) {
			for(l=0;l<n;l++) if(set[i][l]!=set[j][l]) goto noteq;
			if(j<i) goto wrong; /* already counted */
			num++;
		noteq:;
		}
		if(num>=n) r+=pascal[num][n];
	wrong:;
	}
	/* 0 in mask means all values of this property should be the same */
	for(mask=1;mask<(1<<n);mask++) {
		/* hi is the lowest 1-bit, the one we'll backtrack on */
		for(hi=0;hi<n && !(mask&(1<<hi));hi++);
		/* for each value, create list of cards with this value at property hi */
		for(j=0;j<m;j++) for(ln[j]=i=0;i<k;i++) if(set[i][hi]==j) list[j][ln[j]++]=i;
		/* create bitmask for each card */
		for(i=0;i<k;i++) for(setmask[i]=j=0;j<n;j++) setmask[i]|=(1ULL<<set[i][j])<<(j*m);
		for(fixedmask=varmask=i=0;i<n;i++) {
			if(mask&(1<<i)) varmask|=((1ULL<<m)-1)<<(i*m);
			else fixedmask|=((1ULL<<m)-1)<<(i*m);
		}
		/* first level of backtracking: pick value 0 in property hi */
		for(j=0;j<ln[0];j++) {
			i=list[0][j];
			cur=setmask[i];
			r+=btr(1,cur);
		}
	}
	printf("%I64u\n",r);
}

int main() {
	int T;
	genpascal();
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
