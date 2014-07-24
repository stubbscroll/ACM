/* my solution from the actual competition, with bugs fixed. the only
   error was that my arrays were to small - 2000 conductors means the
   expression is 3999 chars.
   the main idea is the same as my other solution, except that i explicitly
   build the tree, put values inside it and explicitly parse the tree to get
   the result.
*/

#include <bits/stdc++.h>
using std::string;
using std::vector;
typedef long long ll;

int par[4444],left[4444],right[4444],num[4444];
int val[4444];
string s;
int gat;
int n;

int btr(int prev) {
	int at=gat;
	par[gat]=prev;
	if(s[gat]=='X') {
		left[at]=right[at]=-1;
		gat++;
		return 1;
	}
	gat++;
	left[at]=gat;
	num[left[at]]=btr(at);
	right[at]=gat;
	num[right[at]]=btr(at);
	return num[left[at]]+num[right[at]];
}

vector<int> cond;
int take;

void numfix(int at) {
	while(at>-1) num[at]--,at=par[at];
}

void process(int ix,int at) {
	if(s[at]=='X') {
		if(val[at]<0) val[at]=cond[take++],numfix(at);
	} else process(ix,left[at]),process(ix,right[at]);
}

int eval(int at) {
	int a,b;
	if(s[at]=='X') return val[at];
	a=eval(left[at]);
	b=eval(right[at]);
	if(s[at]=='A') return a+b;
	return a>b?a:b;
}

struct CircuitsConstruction {
	int maximizeResistance(string circuit, vector <int> conductors) {
		int i;
		sort(conductors.begin(),conductors.end());
		cond=conductors;
		take=0;
		s=circuit;
		n=s.size();
		if(n==1) return conductors[0];
		gat=0;
		num[0]=btr(-1);
		for(i=0;i<n;i++) val[i]=-1;
		/* for each unprocessed B in increasing size of subtree */
		while(1) {
			int best=111111,bestix=-1;
			for(i=0;i<n;i++) if(s[i]=='B' && val[i]<0 && best>num[i]) best=num[i],bestix=i;
			if(bestix<0) break;
			int ix=bestix;
			val[ix]=0;
			if(num[left[ix]]<num[right[ix]]) process(ix,left[ix]);
			else process(ix,right[ix]);
		}
		for(i=0;i<n;i++) if(s[i]=='X' && val[i]<0) val[i]=cond[take++];
		printf("take %d cond %d\n",take,(int)cond.size());
		return eval(0);
	}
};
