#include <vector>
using namespace std;
struct TheTree {
	int maximumDiameter(vector <int> cnt) {
		int n=cnt.size(),best=0;
		/* stupid O(n^4) brute force: try all nodes for root, left, right */
		for(int rot=-1;rot<n;rot++) for(int v=rot;v<n;v++) for(int h=rot;h<n;h++) {
			for(int i=rot+1;i<=v && i<=h;i++) if(cnt[i]<2) goto fail;
			best=max(best,v-rot+h-rot);
		fail:;
		}
		return best;
	}
};