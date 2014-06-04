/* do random simulations and eventually find solution for N=3 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char t[10][512];
int n;
int val[256];

double simul(int n) {
	int i,j,see,k,z;
	int wins=0;
	int trials=0;
	int right;
	for(i=0;i<(1<<n);i++) {
		for(j=0;j<n;j++) val[j]=(i&(1<<j))?1:0;
		trials++;
		right=0;
		for(j=0;j<n;j++) {
			see=0;
			for(z=k=0;k<n;k++) if(k!=j) {
				if(val[k]>0) see|=1<<z;
				z++;
			}
			if(t[j][see]=='H' && val[j]==1) goto fail;
			if(t[j][see]=='T' && val[j]==0) goto fail;
			if(t[j][see]=='H' && val[j]==0) right=1;
			if(t[j][see]=='T' && val[j]==1) right=1;
		}
		if(right) wins++;
		continue;
	fail:;
	}
	return (double)wins/trials;
}

int solve() {
	int x,i;
	scanf("%s",t[0]);
	if(t[0][0]=='0') exit(0);
	x=strlen(t[0]);
	if(x==1) n=1;
	if(x==2) n=2;
	if(x==4) n=3;
	if(x==8) n=4;
	if(x==16) n=5;
	if(x==32) n=6;
	if(x==64) n=7;
	if(x==128) n=8;
	for(i=1;i<n;i++) scanf("%s",t[i]);
	printf("%f\n",simul(n));
	return 1;
}

double random(int n) {
	int i,j,k;
	for(i=0;i<n;i++) memset(t,0,(1<<(n-1))+1);
	for(i=0;i<(1<<(n-1));i++) for(j=0;j<n;j++) {
		k=rand()%3;
		if(k==0) t[j][i]='H';
		if(k==1) t[j][i]='T';
		if(k==2) t[j][i]='P';
	}
	return simul(n);
}

double best;

void printstr() {
	int i,j;
	printf("T:\n");
	for(i=0;i<(1<<(n-1));i++) if(t[0][i]=='T') {
		for(j=0;j<n-1;j++) if(i&(1<<j)) printf("T"); else printf("H");
		printf(" ");
	}printf("\n");
	printf("H:\n");
	for(i=0;i<(1<<(n-1));i++) if(t[0][i]=='H') {
		for(j=0;j<n-1;j++) if(i&(1<<j)) printf("T"); else printf("H");
		printf(" ");
	}printf("\n");
	printf("P:\n");
	for(i=0;i<(1<<(n-1));i++) if(t[0][i]=='P') {
		for(j=0;j<n-1;j++) if(i&(1<<j)) printf("T"); else printf("H");
		printf(" ");
	}printf("\n");
}

void btr(int at) {
	int i;
	double cur;
	if(at==(1<<(n-1))) {
		cur=simul(n);
		if(cur>=best) {
			best=cur;
			for(i=0;i<n;i++) puts(t[i]);
			printstr();
			printf("win %f\n",cur);
		}
		return;
	}
	for(i=0;i<n;i++) t[i][at]='H'; btr(at+1);
	for(i=0;i<n;i++) t[i][at]='T'; btr(at+1);
	for(i=0;i<n;i++) t[i][at]='P'; btr(at+1);
}

void brute(int N) {
	n=N;
	best=-1;
	memset(t,0,sizeof(t));
	btr(0);
}

int antall;
char verdict[128];

char beststr[10000];

void check() {
	int i,j,k;
	double cur;
	for(i=0;i<(1<<(n-1));i++) {
		for(j=k=0;j<n-1;j++) if(i&(1<<j)) k++;
		for(j=0;j<n;j++) t[j][i]=verdict[k];
	}
	cur=simul(n);
	if(cur>=best) {
		best=cur;
		strcpy(beststr,t[0]);
	}
}

void btr2(int at) {
	if(at==antall) {
		check();
		return;
	}
	verdict[at]='H'; btr2(at+1);
	verdict[at]='T'; btr2(at+1);
	verdict[at]='P'; btr2(at+1);
}

void brute2(int N) {
	int i;
	antall=N;
	n=N;
	best=-1;
	memset(t,0,sizeof(t));
	btr2(0);
	for(i=0;i<n;i++) puts(beststr);
}

int main() {
	double best=-1,cur;
	int i;
	int N=3;
	srand(time(0));
	while(1) {
		cur=random(N);
		if(cur>best) {
			best=cur;
			for(i=0;i<N;i++) puts(t[i]);
			printf("gives %f\n\n",best);
		}
	}
	return 0;
}
