/* solution for crane operator, hard input.
   split y into equivalence classes based on boxes that can be reached by
   changing x only.
   pruning 1: count the number of taken elements in each class, and skip values
              of y with no elements left
   pruning 2: use disjoint set to find next free element. when an element is
              picked, check if the previous and next elements are picked, and
              join if applicable
   solves the hard input in 25.8 seconds, which is acceptable.
*/

#include <stdio.h>
#include <string.h>

#define MAX 1000000
typedef long long ll;

int ci[MAX],pi[MAX];
int N,M,q,p,m,d;

char vis[MAX];

/* disjoint set! */
int setp[MAX],rank[MAX];
int next[MAX]; /* next free element in equivalence class */

int findset(int x) {
	if(x!=setp[x]) setp[x]=findset(setp[x]);
	return setp[x];
}

void unionset(int x,int y) {
	x=findset(x);
	y=findset(y);
	if(x==y) return;
	if(rank[x]>rank[y]) setp[y]=x;
	else {
		setp[x]=y;
		if(rank[x]==rank[y]) rank[y]++;
	}
}

void initset(int n) {
	int i;
	for(i=0;i<n;i++) {
		setp[i]=i;
		rank[i]=0;
	}
}

int gcd(int a,int b) {
	if(!b) return a;
	return gcd(b,a%b);
}

int solve() {
	int res=0,at,i;
	memset(vis,0,N);
	/* first, greedily move box to empty space as long as it should end there */
	at=M%N;
	while(at && !vis[at]) {
		res++;
		vis[at]=1;
		at=pi[at];
	}
	/* the rest of the boxes are in cycles. for each cycle, add length+1 to
	   result, unless length is 1 in which case we do nothing */
	for(at=i=0;i<N;i++) if(pi[i]==i) at++;
	for(i=1;i<N;i++) if(!vis[i] && pi[i]!=i) {
		res+=2;
		at=pi[i];
		vis[i]=1;
		while(at!=i) {
			res++;
			vis[at]=1;
			at=pi[at];
			if(at==0) printf("ERROR");
		}
	}
	return res;
}

int left[MAX];

int main() {
	int i,y,T,Z,z,NZ,x;
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d %d %d %d %d",&N,&M,&q,&p,&m,&d);
		if(N>MAX) { printf("raise MAX to %d and recompile\n",N); return 1; }
		ci[0]=0;
		for(i=1;i<N;i++) ci[i]=((ll)ci[i-1]*q+p)%m;
		Z=N/gcd(d,N);
		memset(vis,0,N);
		memset(pi,0,sizeof(int)*N);
		NZ=N/Z;
		for(i=0;i<NZ;i++) left[i]=Z;
		left[M%NZ]--;
		initset(N);
		for(i=0;i<N;i++) next[findset(i)]=i;
		next[findset(M%N)]=(M+d)%N;
		vis[M%N]=1;
		for(i=1;i<N;i++) {
			for(y=0;y<NZ;y++) if(left[(ci[i]+y)%NZ]) {
				z=(ci[i]+y)%N;
				while(vis[z]) {
					if(z==next[findset(z)]) { printf("error\n"); return 0; }	
					z=next[findset(z)];
				}
				pi[i]=z;
				vis[z]=1;
				left[(ci[i]+y)%NZ]--;
				next[findset(z)]=(z+d)%N;
				/* merge with previous set */
				if(vis[(z-(d%N)+N)%N]) {
					unionset(z,(z-(d%N)+N)%N);
					next[findset(z)]=(z+d)%N;
				}
				/* merge with next set */
				if(vis[(z+d)%N]) {
					x=next[findset((z+d)%N)];
					unionset(z,(z+d)%N);
					next[findset(z)]=x;
				}
				break;
			}
		}
		pi[0]=M%N;
		printf("%d\n",solve());
	}
	return 0;
}
