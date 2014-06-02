/* solution to enhancing ipsc rules, both inputs
   algorithm: rather ad hoc-ish colour analysis of each subimage to detect
   thing. must convert from png to bmp beforehand (uncompressed bmp, 8-bits
   where palette entry takes 4 bytes) */

#include <stdio.h>
#include <stdlib.h>

#define H 0x48a
#define PAL 0x8a

unsigned char buf[5000000];
int len;
int hp,num;

#define GRAA 10
#define FARGE 120

int abs(int a) {
	return a<0?a:-a;
}

/* each subpicture is 60*80 */
int identify(int y,int x) {
	int i,j,p,hvit=0,svart=0,graa=0,farge=0,r,g,b,col;
	for(i=0;i<80;i++) for(j=0;j<60;j++) {
		p=H+i*120+j+x*60+y*(120*80);
		col=buf[p];
		r=buf[PAL+col*4];
		g=buf[PAL+1+col*4];
		b=buf[PAL+2+col*4];
		if(r>0xfb && g>0xfb && b>0xfb) hvit++;
		if(abs(r-g)<GRAA && abs(r-b)<GRAA && abs(g-b)<GRAA && r<80) svart++;
		if(abs(r-g)<GRAA && abs(r-b)<GRAA && abs(g-b)<GRAA && r>140 && r<200) graa++;
		if(abs(r-g)>FARGE || abs(r-b)>FARGE || abs(b-g)>FARGE) farge++;
	}
	/* 0=stein 1=papir 2=saks */
	if(svart>80) return 0;
	if(farge>20) return 2;
	return 1;
}

int main(int argc,char **argv) {
	FILE *fi;
	int i,pic,t1,t2,no,left,right;
	char s[64];
	if(argc<2) puts("usage: e n, where n is input (1 or 2)"),exit(0);
	no=strtol(argv[1],0,10);
	if(no<1 || no>2) puts("n must be 1 or 2"),exit(0);
	for(pic=0;;pic++) {
		sprintf(s,"e%d_%02d.bmp",no,pic);
		fi=fopen(s,"rb");
		if(!fi) break;
		len=fread(buf,1,5000000,fi);
		hp=(len-H)/120;
		num=hp/80;
		/* analyse each pair */
		left=right=0;
		for(i=num-1;i>=0;i--) {
			t1=identify(i,0);
			t2=identify(i,1);
			if(t1==(t2+1)%3) left++;
			else if(t1==(t2+2)%3) right++;
		}
		if(left>right) puts("LEFT");
		else if(left<right) puts("RIGHT");
		else puts("DRAW");
		fclose(fi);
	}
	return 0;
}
