/* solution for klingelt das glockenspiel, easy input
   prerequisite: convert k1.mp3 to k1.wav
   algorithm: slice the wave into R*W equal-sized chunks, where R=5 is the
   number of rows (hinted at by the image in the problem statement, and
   "confirmed" by looking at the wav) and W is just a convenient screen
   width. for each slice, check if any sample in the chunk has amplitude over
   some cutoff. then, plot a pixel in the corresponding R*W grid. then, output
   the grid and see if we can read a word. if not, tweak the amplitude cutoff
   and try again.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char fil[100000000];
int len;
int header=0x2c;

#define W 79
char g[5][W+1];

#define CUT 100
int issample(int pos) {
	int lyd=fil[header+pos*2]+fil[header+pos*2+1]*256;
	if(lyd>=32768) lyd-=65536;
	return lyd<-CUT || lyd>CUT;
}

int issound(int row,int col) {
	int c=(len-header)/2,w=c/5,bit=w/W;
	int i;
	for(i=0;i<bit/2;i++) if(issample(row*w+bit*col+i)) return 1;
	return 0;
}

void solve() {
	int i,j;
	for(i=0;i<5;i++) for(j=0;j<=W;j++) g[i][j]=(j==W)?0:'.';
	for(i=0;i<5;i++) for(j=0;j<W;j++) {
		if(issound(i,j)) g[i][j]='*';
	}
	for(i=0;i<5;i++) puts(g[i]);
}

void readfile() {
	FILE *f=fopen("k1.wav","rb");
	if(!f) printf("error");
	fseek(f,0,SEEK_END);
	len=ftell(f);
	fclose(f);
	printf("filelen %d\n",len);
	f=fopen("k1.wav","rb");
	fread(fil,1,len,f);
	fclose(f);
}

int main() {
	readfile();
	solve();
	return 0;
}
