/* algorithm: greedy.
   whenever we encounter + or - that is preceeded by ?, we scan upwards
   through all contiguous ? to check if + (or -) was set on one of the rows
   we scanned. if no, we need to change the light. */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct SwitchingGame {
	int timeToWin(vector <string> s) {
		char lys[111];
		int sm[111],sp[111],on,off;
		int i,j,k,n=s.size(),m=s[0].size();
		for(i=0;i<m;i++) lys[i]='-';
		for(i=0;i<n;i++) sm[i]=sp[i]=0;
		int r=0;
		for(i=0;i<n;i++) {
			on=off=0;
			if(i) for(j=0;j<m;j++) if(s[i-1][j]=='?' && s[i][j]!='?' && lys[j]!=s[i][j]) {
				if(s[i][j]=='-') {
					lys[j]='-';
					for(k=i-1;k>=0 && s[k][j]=='?';k--) if(sm[k]) goto ok;
					off=1; sm[i]=1;
				} else {
					lys[j]='+';
					for(k=i-1;k>=0 && s[k][j]=='?';k--) if(sp[k]) goto ok;
					on=1; sp[i]=1;
				}
			ok:;
			}
			for(j=0;j<m;j++) {
				if(i && s[i-1][j]=='?') continue;
				if(s[i][j]=='+' && lys[j]=='-') lys[j]='+',on=1,sp[i]=1;
				if(s[i][j]=='-' && lys[j]=='+') lys[j]='-',off=1,sm[i]=1;
			}
			r+=on+off+1;
		}
		return r;
	}
};
