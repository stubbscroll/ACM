#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int p[55],n;
void flood(string &s,int at,int r) {
	int z,i;
	if(p[at]>-1) return;
	p[at]=r;
	for(i=0;i<n;i++) if(s[i]==s[at]) flood(s,i,r);
	z=n-at-1;
	if(z!=at && s[at]!=s[i]) flood(s,z,r);
}
int solve(string s) {
	int f[26],i,best=0;
	memset(f,0,sizeof(f));
	for(i=0;i<s.size();i++) f[s[i]-'a']++;
	for(i=0;i<26;i++) best=max(best,f[i]);
	return s.size()-best;
}
struct GooseTattarrattatDiv1 {
	int getmin(string S) {
		int i,r=0,res=0,j;
		n=S.size();
		for(i=0;i<n;i++) p[i]=-1;
		for(i=0;i<n;i++) if(p[i]<0) flood(S,i,r++);
		for(i=0;i<r;i++) {
			string s="";
			for(j=0;j<n;j++) if(p[j]==i) s+=S[j];
			res+=solve(s);
		}
		return res;
	}
};
