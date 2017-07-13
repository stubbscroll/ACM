#include <stdio.h>

int n;
int perm[11];
int temp[11];
int ways;

void btr(int at,int cap) {
	int i,j,t;
	if(at==cap) {
		for(i=0;i<n;i++) if(temp[i]!=i) return;
		ways++;
		return;
	}
	/* pick any number out of place */
	for(i=0;i<n;i++) for(j=i+1;j<n;j++) {
		/* swap i and j */
		t=temp[i]; temp[i]=temp[j]; temp[j]=t;
		btr(at+1,cap);
		t=temp[i]; temp[i]=temp[j]; temp[j]=t;
	}
}

void solve() {
	int i,cap;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&perm[i]),perm[i]--;
	for(cap=0;cap<=10;cap++) {
		ways=0;
		for(i=0;i<n;i++) temp[i]=perm[i];
		btr(0,cap);
		if(ways>0) {
			printf("%d\n",ways);
			break;
		}
	}
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
