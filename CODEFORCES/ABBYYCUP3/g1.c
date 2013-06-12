#include <stdio.h>
#include <string.h>

#define HASH 1000000007

char s[2222];
int len;
int n;
char p[10][2222];
int pl[10];
int L[10],R[10];

int ok[222][222];
int hash[222][222];
int okn[222];

int gethash(int l,int r) {
	int h=0;
	for(;l<r;l++) h=(h*177LL+s[l])%HASH;
	return h;
}

int exists(int l,int r) {
	int len=r-l,i;
	int hasj=gethash(l,r);
	for(i=0;i<okn[len];i++) {
		if(hasj!=hash[len][i]) continue;
		if(!strncmp(s+l,s+ok[len][i],len)) return 1;
	}
	return 0;
}

int ruleok(int i,int j) {
	int k,l,num;
	for(k=0;k<n;k++) {
		for(num=0,l=0;l<=pl[k]-(j-i);l++) if(!strncmp(s+i,p[k]+l,j-i)) num++;
		if(num<L[k] || num>R[k]) return 0;
	}
	return 1;
}

int main() {
	int i,j,r=0;
	scanf("%s %d",s,&n);
	for(i=0;i<n;i++) scanf("%s %d %d",p[i],&L[i],&R[i]);
	len=strlen(s);
	for(i=0;i<222;i++) okn[i]=0;
	for(i=0;i<n;i++) pl[i]=strlen(p[i]);
	for(i=0;i<len;i++) for(j=i+1;j<=len;j++) if(!exists(i,j)) {
		/* check if it follows rules */
		if(ruleok(i,j)) {
			r++;
			ok[j-i][okn[j-i]]=i;
			hash[j-i][okn[j-i]++]=gethash(i,j);
		}
	}
	printf("%d\n",r);
	return 0;
}
