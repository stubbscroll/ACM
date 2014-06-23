/* solution for beating the game, hard input
   algorithm: tree search with memoization with state (board,timestep)
   c++ because i'm lazy and want map */

#include <cstdio>
#include <map>
#include <vector>
using std::map;
using std::vector;

#define MAX 100000
typedef long long ll;

/* random stuff */

int R=43,S=22;
ll M=1LL<<32;
ll x[MAX];
int xp;
int c[MAX];

ll myrandom() {
	if(xp==MAX) printf("error");
	return x[xp++];
}

void genrand() {
	int i;
	for(i=0;i<43;i++) c[i]=0;
	for(i=43;i<MAX;i++) {
		x[i]=x[i-S]-x[i-R]-c[i-1];
		if(x[i]<0) c[i]=1;
		else c[i]=0;
		x[i]%=M;
		if(x[i]<0) x[i]+=M;
	}
}

/* game logic */

int board[9],n;

void newtile() {
	int numempty=0,i,pos,newval,at;
	for(i=0;i<n;i++) if(!board[i]) numempty++;
	pos=myrandom()%numempty;
	if(myrandom()%10==0) newval=4; else newval=2;
	for(at=i=0;i<n;i++) if(!board[i]) {
		if(at==pos) break;
		at++;
	}
	board[i]=newval;
}

int shiftleft() {
	int i,previ=0,j,change=0,prev=-1,score=0;
	for(i=0;i<n;i++) if(board[i]) {
		if(board[i]==prev) {
			board[i]=0;
			board[previ]*=2;
			score+=prev+prev;
			change=1;
		}
		prev=board[i];
		previ=i;
	}
	for(j=i=0;i<n;i++) if(board[i]) {
		if(j!=i) change=1;
		board[j++]=board[i];
	}
	for(;j<n;j++) board[j]=0;
	return change?score:-1;
}

int moveleft() {
	int score=shiftleft();
	if(score>-1) newtile();
	return score;
}

int moveright() {
	int i,ch;
	ll t;
	for(i=0;i+i<n;i++) t=board[i],board[i]=board[n-i-1],board[n-i-1]=t;
	ch=shiftleft();
	for(i=0;i+i<n;i++) t=board[i],board[i]=board[n-i-1],board[n-i-1]=t;
	if(ch>-1) newtile();
	return ch;
}

void printboard() {
	int i;
	printf("%d",board[0]);
	for(i=1;i<n;i++) printf(" %d",board[i]);
	putchar('\n');
}

map<vector<int>,int> prev,next;

vector<int> pack() {
	vector<int> v(0);
	int i;
	for(i=0;i<n;i++) v.push_back(board[i]);
	return v;
}

void unpack(vector<int> v) {
	int i;
	for(i=0;i<n;i++) board[i]=v[i];
}

void solve() {
	int i,best=0,cur,score;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&board[i]);
	for(i=0;i<43;i++) scanf("%lld",&x[i]);
	genrand();
	prev.clear(); next.clear();
	prev[pack()]=0;
	for(i=0;!prev.empty();i++) {
		next.clear();
		for(auto it=prev.begin();it!=prev.end();it++) {
			unpack(it->first);
			cur=it->second;;
			if(best<cur) best=cur;
			xp=i*2+43;
			score=moveleft();
			if(score>-1) next[pack()]=cur+score;
			unpack(it->first);
			xp=i*2+43;
			score=moveright();
			if(score>-1) next[pack()]=cur+score;
		}
		prev=next;
	}
	printf("%d\n",best);
}

void sanity() {
	int i;
	for(i=0;i<43;i++) x[i]=(999999999LL*i*i*i)%M;
	genrand();
	for(i=43;i<46;i++) printf("%lld ",x[i]);
	printf("\n");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
