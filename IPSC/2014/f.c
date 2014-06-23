/* solution for find a sudoku in pi, both inputs
   algorithm: read pi output from fparse.c, find all permutations of 1-9 and
   backtrack on legal sudoku grid on increasing largest offset */

#include <stdio.h>
#include <string.h>

#define MAXPERM 100000
#define DIG 100000000

typedef long long ll;

char perm[MAXPERM][10];
ll mask[MAXPERM][2];
int offset[MAXPERM];
int n;

char pi[101010101];

void findperm() {
	int i,j;
	int count[10];
	for(i=0;i<10;i++) count[i]=0;
	for(i=0;i<DIG;i++) pi[i]-='0';
	for(i=0;i<9;i++) count[(int)pi[i]]++;
	for(n=i=0;i<DIG-9;i++) {
		for(j=1;j<10;j++) if(count[j]!=1) goto fail;
		for(j=0;j<9;j++) perm[n][j]=pi[i+j];
		offset[n]=i;
		mask[n][0]=mask[n][1]=0;
		for(j=0;j<9;j++) mask[n][j/5]|=(1LL<<(pi[i+j]-1+(j%5)*9));
		n++;
	fail:;
		count[(int)pi[i]]--;
		count[(int)pi[i+9]]++;
	}
}

int maks;
char line[9][10];
int path[9];

int btr(int at,ll m[2]) {
	ll m2[2];
	int i,j,k,count[9],a;
	if(at%3!=1) {
		/* check 3x3-boxes so far */
		a=(at-1)/3*3;
		for(k=0;k<3;k++) {
			for(i=0;i<9;i++) count[i]=0;
			for(i=0;i<at-a;i++) for(j=0;j<3;j++) count[line[a+i][k*3+j]-'1']++;
			for(i=0;i<9;i++) if(count[i]>1) return 0;
		}
	}
	if(at==9) {
		/* check for overlapping indexes */
		for(i=0;i<9;i++) for(j=0;j<9;j++) if(i!=j && path[i]>=path[j] && path[i]<path[j]+9) return 0;
		return 1;
	}
	if(at==3 || at==6) i=path[at-3]-1;
	else i=path[at-1]-1;
	for(;i>=0;i--) {
		if((m[0]&mask[i][0]) || (m[1]&mask[i][1])) continue;
		m2[0]=m[0]+mask[i][0];
		m2[1]=m[1]+mask[i][1];
		for(j=0;j<9;j++) line[at][j]=pi[offset[i]+j]+'0';
		line[at][9]=0;
		path[at]=i;
		if(btr(at+1,m2)) return 1;
	}
	return 0;
}

int main() {
	int i,j;
	ll m[2];
	scanf("%100000000s",pi);
	findperm();
	for(i=8;;i++) {
		maks=i;
		path[0]=i;
		for(j=0;j<9;j++) line[0][j]=pi[offset[i]+j]+'0';
		line[0][9]=0;
		m[0]=mask[i][0];
		m[1]=mask[i][1];
		if(btr(1,m)) break;
	}
	for(i=0;i<9;i++) printf("%s %d\n",line[i],offset[path[i]]+1);
	return 0;
}
