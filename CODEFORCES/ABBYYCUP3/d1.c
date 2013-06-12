#include <stdio.h>
#include <string.h>
typedef long long ll;
int left[10];
int n;
char seen[3628800];

ll fact[21];

/*  must be called before using rank/unrank */
void initfact() {
  int i;
  fact[0]=1;
  for(i=1;i<21;i++) fact[i]=fact[i-1]*i;
}

ll permbtr(int n,int *p,int *q) {
  int s,t;
  if(n<2) return 0;
  s=p[n-1]; p[n-1]=p[q[n-1]]; p[q[n-1]]=s;
  t=q[s];   q[s]=q[n-1];      q[n-1]=t;
  return s+n*permbtr(n-1,p,q);
}

/*  return rank of permutation
    n: number of elements
    *p: permutation to rank */
/*  warning, *p is destroyed! */
ll permutationrank2(int n,int *p) {
  int i,q[16];
  for(i=0;i<n;i++) q[p[i]]=i;
  return permbtr(n,p,q);
}

int order[10];

void btr() {
	int t,i,j;
	int p[10],r;
	for(i=0;i<n;i++) p[i]=order[i];
	r=permutationrank2(n,p);
	seen[r]=1;
	for(i=0;i<n-1;i++) if(left[i]) for(j=i+1;j<n;j++) if(left[j]) {
		left[j]--; left[i]--;
		t=order[j],order[j]=order[i],order[i]=t;
//		printf("  throw %d %d\n",at,i);
		btr();
		left[j]++; left[i]++;
		t=order[j],order[j]=order[i],order[i]=t;
	}
}

int pre[11][11];


void setpre() {
	memset(pre,-1,sizeof(pre));
	pre[8][0]=764;
	pre[8][1]=1856;
	pre[8][2]=4256;
	pre[8][3]=8736;
	pre[8][4]=16800;
	pre[8][5]=26880;
	pre[8][6]=40320;
	pre[8][7]=40320;
	pre[8][8]=40320;
	pre[9][0]=2620;
	pre[9][1]=6876;
	pre[9][2]=16704;
	pre[9][3]=38304;
	pre[9][4]=78624;
	pre[9][5]=151200;
	pre[9][6]=241920;
	pre[9][7]=362880+0;
	pre[9][8]=362880;
	pre[9][9]=362880;
	pre[10][0]=9496;
	pre[10][1]=26200;
	pre[10][2]=68760;
	pre[10][3]=167040;
	pre[10][4]=383040;
	pre[10][5]=786240;
	pre[10][6]=1512000;
	pre[10][7]=2419200;
	pre[10][8]=3628800+0;
	pre[10][9]=3628800;
	pre[10][10]=3628800;
}

int main() {
	int i,z=0,two;
	initfact();
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&left[i]),order[i]=i;
	/* precalced values */
	setpre();
	for(i=two=0;i<n;i++) if(left[i]>1) two++;
	if(pre[n][two]>-1) {
		printf("%d\n",pre[n][two]);
		return 0;
	}
	
	memset(seen,0,sizeof(seen));
	btr();
	for(i=0;i<3628800;i++) z+=seen[i];
	printf("%d\n",z);
	return 0;
}
