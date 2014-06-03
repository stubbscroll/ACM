#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FAIL "Impossible"
struct FoxAndChess {
	string ableToMove(string a, string b) {
		int i,j,n=a.size();
		for(i=j=0;i<n;i++) {
			if(a[i]!='.') {
				while(j<n && b[j]=='.') j++;
				if(j==n) return FAIL;
				printf("%d %d, %c %c\n",i,j,a[i],b[j]);
				if(a[i]!=b[j]) return FAIL;
				if(a[i]=='L' && i<j) return FAIL;
				if(a[i]=='R' && i>j) return FAIL;
				j++;
			}
		}
		for(;j<n;j++) if(b[j]!='.') return FAIL;
		return "Possible";
	}
};
