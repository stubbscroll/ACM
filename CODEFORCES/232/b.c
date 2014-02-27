#include <stdio.h>

typedef long long ll;

int isprime(int n) {
	int i;
	if(n<4) return n>1;
	if(!(n&1)) return 0;
	for(i=3;i*i<=n;i+=2) if(n%i==0) return 0;
	return 1;
}

int findprime(int n,int d) {
	while(!isprime(n)) n+=d;
	return n;
}

int main() {
	int t,n,prev,next;
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		if(isprime(n+1)) printf("%d/%d\n",n-1,2*n+2);
		else {
			prev=findprime(n,-1);
			next=findprime(n+1,1);
			printf("%I64d/%I64d\n",(ll)(prev-2)*next+2*(n-prev+1),(ll)2*prev*next);
		}
	}
	return 0;
}
