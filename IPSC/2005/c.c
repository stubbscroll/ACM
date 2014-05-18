/* solution for crane operator, easy input.
   do stuff with permutation cycles.
   very inefficient finding of x,y, O(n^2) per box.
   warning, problems with problem statement:
   - it's not mentioned that x,y should be found per box
     (it has to be - otherwise c_1==c_7 is forced in sample input)
   - it's not mentioned that M should be reduced modulo N, instead of merely
     interpreting M>=N as "free space is where no box happens to end up"
*/

#include <stdio.h>
#include <string.h>

#define MAX 100000
typedef long long ll;

int ci[MAX],pi[MAX],inv[MAX];
int N,M,q,p,m,d;

char vis[MAX];

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

int main() {
	int i,x,y,T,Z,z;
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d %d %d %d %d",&N,&M,&q,&p,&m,&d);
		if(N>MAX) { printf("raise MAX to %d and recompile\n",N); return 1; }
		ci[0]=0;
		for(i=1;i<N;i++) ci[i]=((ll)ci[i-1]*q+p)%m;
		Z=N/gcd(d,N);
		memset(vis,0,N);
		memset(pi,0,sizeof(int)*N);
		for(i=1;i<N;i++) {
			for(y=0;y<N;y++) for(x=0;x<Z;x++) {
				z=(ci[i]+(ll)d*x+y)%N;
				if(z!=M%N && !vis[z]) {
					pi[i]=z;
					vis[z]=1;
					goto ok;
				}
			}
		ok:;
		}
		pi[0]=M%N;
		printf("%d\n",solve());
	}
	return 0;
}
