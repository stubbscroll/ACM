/* solution for candies, hard input
   algorithm: find top 3 of each category, then brute force on those,
              runtime O(n) */

#include <stdio.h>

#define MAX 5000
int bag[3][MAX];
int n;

void findtop(int *a,int *b,int *c) {
	int i,j,best,bestix;
	for(i=0;i<3;i++) {
		for(best=bestix=-1,j=0;j<n;j++) if(best<a[j]) best=a[j],bestix=j;
		b[i]=best;
		c[i]=bestix;
		a[bestix]=-1;
	}
}

int main() {
	int i,j,k,cur,best=0,besta=-1,bestb=-1,bestc=-1;
	int top[3][3],ix[3][3];
	scanf("%d",&n);
	for(i=0;i<n;i++) for(j=0;j<3;j++) scanf("%d",&bag[j][i]);
	for(i=0;i<3;i++) findtop(bag[i],top[i],ix[i]);
	for(i=0;i<3;i++) for(j=0;j<3;j++) for(k=0;k<3;k++) {
		if(ix[0][i]==ix[1][j]) continue;
		if(ix[0][i]==ix[2][k]) continue;
		if(ix[1][j]==ix[2][k]) continue;
		cur=top[0][i]+top[1][j]+top[2][k];
		if(best<cur) best=cur,besta=ix[0][i],bestb=ix[1][j],bestc=ix[2][k];
	}
	printf("Bag for chocolate candies: %d\n",besta+1);
	printf("Bag for strawberry candies: %d\n",bestb+1);
	printf("Bag for banana candies: %d\n",bestc+1);
	return 0;
}
