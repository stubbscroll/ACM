/* solution to dependency problems
   algorithm: greedily "install" packages with in-degree 0
   c++ because i want map */

#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

map<string,int> num;
vector<string> packages;
vector<vector<int> > g;
vector<int> empty;
vector<int> deg;
vector<int> can;

int getnum(char *t) {
	string s=t;
	if(num.find(s)==num.end()) {
		packages.push_back(s);
		g.push_back(empty);
		deg.push_back(0);
		can.push_back(0);
		return num[s]=packages.size()-1;
	}
	return num[s];
}

int main() {
	char c[5000];
	int cur;
	while(1) {
		if(scanf("%4999s",c)!=1) goto solve;
		cur=getnum(c);
		can[cur]=1;
		while(1) {
			if(scanf("%4999s",c)!=1) goto solve;
			if(!strcmp(c,"0")) break;
			g[getnum(c)].push_back(cur);
			deg[cur]++;
		}
	}
solve:
	queue<int> q;
	for(int i=0;i<(int)deg.size();i++) if(!deg[i] && can[i]) q.push(i);
	int r=0;
	while(!q.empty()) {
		r++;
		cur=q.front(); q.pop();
		for(int i=0;i<(int)g[cur].size();i++) if(!--deg[g[cur][i]]) q.push(g[cur][i]);
	}
	printf("%d\n",r);
	return 0;
}
