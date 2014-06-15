/* solution for let there be sound, easy input
   steps:
   1. rename l1.in to l1.mp3, convert it to wav (l1.wav)
   2. run this program. it smoothes the absolute values of the waveform and
      does fuzzy recognition to detect ones and zeros which are then converted
      to ascii.
   3. when we read the sentence that's output, we notice that there should be
      a number (not 0 or 1) somewhere. we go back to the mp3 and listen to it,
      and follow the instructions by plugging the question into wolframalpha.
*/

#include <stdio.h>
#include <stdlib.h>

short int oldwave[33333333];
short int wave[33333333];
short int zero[1000000];
short int one[1000000];
int zn,on;
int n;

unsigned char fil[44444444];

void loadfile() {
	FILE *f=fopen("l1.wav","rb");
	int r,i;
	if(!f) printf("error");
	n=0;
	r=fread(fil,1,44444444,f);
	for(i=0x2c;i<r;i+=2) {
		wave[n]=(fil[i]+fil[i+1]*256)&65535;
		n++;
	}
	fclose(f);
}

#define LOUD 10
int loud(int at) {
	int i,z=0;
	for(i=0;i<20;i++) if(wave[i+at]<=-LOUD || wave[i+at]>=LOUD) z++;
	return z>=5;
}

void grab(int at,short int *wav,int *len) {
	int z=0;
	while(!loud(at)) at++;
	while(loud(at)) wav[z++]=wave[at++];
	*len=z;
}

void get01() {
	grab(10,zero,&zn);
	grab(19000,one,&on);
	printf("zero: %d\n",zn);
	printf("one:  %d\n",on);
}

char seq[11111111];
int sn;

int myabs(int v) {
	if(v<0) return -v; return v;
}

int match(int at,short int *wav,int len) {
	int i,ok=0;
	for(i=0;i<len;i++) {
		if(myabs(wav[i]-wave[i+at])<305) ok++;
		if(ok/(i+1.)<.5) return 0;
	}
	return 1;
}

void parse() {
	int i,j;
	sn=0;
	for(j=i=0;i<n;) {
		if(match(i,zero,zn)) printf("0 at %d\n",i),seq[sn++]=0,i+=zn;
		else if(match(i,one,on)) printf("1 at %d\n",i),seq[sn++]=1,i+=on;
		else i++;
	}
	for(i=0;i<sn;i+=8) {
		j=(seq[i]<<7)+(seq[i+1]<<6)+(seq[i+2]<<5)+(seq[i+3]<<4)+(seq[i+4]<<3)+(seq[i+5]<<2)+
		  (seq[i+6]<<1)+(seq[i+7]<<0);
		printf("%c",j);
	}
}

void preprocess() {
	int j,z,i,sum;
	for(i=0;i<n;i++) oldwave[i]=wave[i];
	for(i=0;i<n;i++) {
		for(sum=z=0,j=-100;j<=100;j++) {
			if(i+j<0 || i+j>=n) continue;
			sum+=myabs(oldwave[i+j]); z++;
		}
		wave[i]=sum/z;
	}
}

int main() {
	loadfile();
	preprocess();
	get01();
	parse();
	return 0;
}
