/* generate all strange numbers by brute force in an attempt to spot pattern */

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

vector<string> s;

int exists(string &t) {
	for(int i=0;i<(int)s.size();i++) if(t==s[i]) return 1;
	return 0;
}

int main() {
	int at=2;
	s.push_back("0");
	s.push_back("1");
	puts("0: 0\n1: 1");
	while(1) {
		string t=s[s.size()-1];
		for(int i=(int)t.size()-1;i;i--) {
			t[i]^=1;
			if(!exists(t)) goto can;
			t[i]^=1;
		}
		t="1"+t;
		s.push_back(t);
		printf("%d: %s\n",at++,t.c_str());
		continue;
	can:
		s.push_back(t);
		printf("%d: %s\n",at++,t.c_str());
	}
}
