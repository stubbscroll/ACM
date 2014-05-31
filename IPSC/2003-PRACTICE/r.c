/* solution for candies, easy input
   algorithm: try all combinations of bags with linear time processing,
              total runtime O(n^3) */

#include <stdio.h>

#define MAX 5000
int bag[MAX][3];
int n;

int main() {
	int i,j,k,cur,best=0,besta=-1,bestb=-1,bestc=-1;
	scanf("%d",&n);
	for(i=0;i<n;i++) for(j=0;j<3;j++) scanf("%d",&bag[i][j]);
	for(i=0;i<n;i++) for(j=0;j<n;j++) if(i!=j) for(k=0;k<n;k++) if(i!=k && j!=k) {
		cur=bag[i][0]+bag[j][1]+bag[k][2];
		if(best<cur) best=cur,besta=i,bestb=j,bestc=k;
	}
	printf("Bag for chocolate candies: %d\n",besta+1);
	printf("Bag for strawberry candies: %d\n",bestb+1);
	printf("Bag for banana candies: %d\n",bestc+1);
	return 0;
}
