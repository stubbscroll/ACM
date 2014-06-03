#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int cases,n;
	scanf("%d",&cases);
	printf("%d\n",cases);
	while(cases--) {
		scanf("%d",&n);
		printf("\n%d\n",n);
		vector<int> tall;
		for(int i=0;i<n;i++) {
			int x;
			scanf("%d",&x);
			tall.push_back(x);
		}
		sort(tall.begin(),tall.end());
		swap(tall[0],tall[n-2]);
		for(int i=0;i<n;i++) printf("%d%c",tall[i],i==n-1?'\n':' ');
	}
	return 0;
}
