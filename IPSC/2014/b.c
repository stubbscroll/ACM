/* solution for beating the game, easy input
   algorithm: simulation, and storing powers of two since numbers can get
   larger than long long */

#include <stdio.h>

typedef long long ll;

#define MAX 3333333

int R=43,S=22;
ll M=1LL<<32;

ll x[MAX];
int xp;
int c[MAX];
int n;
char moves[MAX];
int mn;

ll board[MAX];

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

void newtile() {
	int numempty=0,i,pos,newval,at;
	for(i=0;i<n;i++) if(!board[i]) numempty++;
	pos=myrandom()%numempty;
	if(myrandom()%10==0) newval=2; else newval=1;
	for(at=i=0;i<n;i++) if(!board[i]) {
		if(at==pos) break;
		at++;
	}
	board[i]=newval;
}

int shiftleft() {
	int i,previ=-1,j,change=0;
	ll prev=-1;
	for(i=0;i<n;i++) if(board[i]) {
		if(board[i]==prev) {
			board[i]=0;
			board[previ]++;
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
	return change;
}

void moveleft() {
	if(shiftleft()) newtile();
}

void moveright() {
	int i,ch;
	ll t;
	for(i=0;i+i<n;i++) t=board[i],board[i]=board[n-i-1],board[n-i-1]=t;
	ch=shiftleft();
	for(i=0;i+i<n;i++) t=board[i],board[i]=board[n-i-1],board[n-i-1]=t;
	if(ch) newtile();
}

void printcell(ll z) {
	if(!z) { printf("0"); return; }
	if(z<63) { printf("%I64d",1LL<<z); return; }
	switch(z) {
	case 63: printf("9223372036854775808"); break;
	case 64: printf("18446744073709551616"); break;
	case 65: printf("36893488147419103232"); break;
	case 66: printf("73786976294838206464"); break;
	case 67: printf("147573952589676412928"); break;
	case 68: printf("295147905179352825856"); break;
	case 69: printf("590295810358705651712"); break;
	case 70: printf("1180591620717411303424"); break;
	case 71: printf("2361183241434822606848"); break;
	case 72: printf("4722366482869645213696"); break;
	default: printf("ERROR %I64d ",z);
	}
}

void printboard() {
	int i;
	printcell(board[0]);
	for(i=1;i<n;i++) putchar(' '),printcell(board[i]);
	putchar('\n');
}

void solve() {
	ll z;
	int i;
	scanf("%d",&n);
	for(i=0;i<n;i++) {
		scanf("%I64d",&z);
		for(board[i]=0;z>1;board[i]++,z>>=1);
	}
	for(i=0;i<43;i++) scanf("%I64d",&x[i]);
	scanf("%d",&mn);
	scanf("%s",moves);
	genrand();
	xp=43;
	for(i=0;i<mn;i++) {
		if(moves[i]=='l') moveleft(); else moveright();
	}
	printboard();
}

void sanity() {
	int i;
	for(i=0;i<43;i++) x[i]=(999999999LL*i*i*i)%M;
	genrand();
	for(i=43;i<46;i++) printf("%I64d ",x[i]);
	printf("\n");
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
