#include <stdio.h>
#include <string.h>

int pic[32][32];
int pic2[32][32];
int order[]={15,2,17,1,25,14,11,7,23,28,19,16,21,12,10,3,27,26,9,5,0,20,31,22,29,18,24,8,30,6,4,13};
int order2[]={15,25,2,1,23,28,19,17,11,16,7,14,12,21,10,3,27,26,0,22,31,20,5,9,24,8,29,18,30,6,4,13,};

void fix() {
	int i,j;
	for(i=0;i<32;i++) for(j=0;j<32;j++) pic2[i][j]=pic[order2[i]][j];
}

void write(int no) {
	FILE *f;
	char s[1231];
	int i,j;
	sprintf(s,"%04d.pgm",no);
	f=fopen(s,"w");
	fprintf(f,"P2\n32\n32\n256\n");
	for(i=0;i<32;i++) for(j=0;j<32;j++) fprintf(f,"%d\n",pic2[j][i]);
	fclose(f);
}

int main() {
	int T,no,i,j;
	scanf("%d",&T);
	for(no=1;no<=T;no++) {
		for(j=0;j<32;j++) for(i=0;i<32;i++) scanf("%d",&pic[i][j]);
		fix();
		write(no);
	}
	return 0;
}


