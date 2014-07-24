/* observation: we can divide the X's into two partitions: the ones that are
   added in the final result, and those that are min'd away by the B
   operation. the actual positions don't matter, only the counts.
   algorithm: use recursion to parse the expression tree and count the number
   of X's that are added. when a B is encountered, calculate counts of
   both arguments and take max. base case is the subtree X of size 1.
   then, sum the n highest values of cond where n was the number found above.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
/* find second argument of instruction at at */
int findright(int at) {
	int lv=1;
	while(lv) lv=lv+(s[++at]=='X'?-1:1);
	return at+1;
}
/* count number of X's that gets added for subtree rooted at at */
int count(int at) {
	if(s[at]=='X') return 1;
	int a=count(at+1),b=count(findright(at));
	if(s[at]=='A') return a+b;
	else return max(a,b);
}
struct CircuitsConstruction {
	int maximizeResistance(string circuit, vector <int> cond) {
		s=circuit;
		sort(cond.rbegin(),cond.rend());
		int x=count(0),i,r=0;
		for(i=0;i<x;i++) r+=cond[i];
		return r;
	}
};
