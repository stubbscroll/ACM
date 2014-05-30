/* "solution" to censored smiles, easy input
   "algorithm": convert input to bmp and count manually */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1001

typedef unsigned char uchar;
typedef unsigned int uint;

char s[MAX][MAX+1];
char t[MAX*MAX];
int x,y;

void setword4(uchar *a,uint v) {
	a[0]=v&255; a[1]=(v>>8)&255; a[2]=(v>>16)&255; a[3]=(v>>24)&255;
}

int saveimage(char *s,int x,int y,char *t) {
	int w,i,j;
	unsigned char header[54]={
		0x42,0x4d,0,0,0,0,0,0,0,0,54,0,0,0,40,0,
		0,0,0,0,0,0,0,0,0,0,1,0,24,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0
	};
	unsigned char *b;
	FILE *f=fopen(s,"wb");
	if(!f) return 0;
	w=x*3;
	if(w&3) w+=4-(w&3);
	if(!(b=calloc(w*y,1))) { fclose(f); return 0; }
	setword4(header+2,54+w*y);
	setword4(header+0x12,x);
	setword4(header+0x16,y);
	setword4(header+0x22,w*y);
	for(j=0;j<y;j++) for(i=0;i<x;i++) {
		b[i*3+(y-j-1)*w]=t[i+j*x]*255;
		b[i*3+(y-j-1)*w+1]=t[i+j*x]*255;
		b[i*3+(y-j-1)*w+2]=t[i+j*x]*255;
	}
	fwrite(header,54,1,f);
	fwrite(b,w*y,1,f);
	fclose(f);
	return 1;
}

int main() {
	int i,j;
	scanf("%d %d",&x,&y);
	if(x>MAX || y>MAX) { puts("increase MAX and recompile"); return 0; }
	for(i=0;i<x;i++) scanf("%s",s[i]);
	for(i=0;i<x;i++) for(j=0;j<y;j++) t[j+i*y]=s[i][j]=='1';
	saveimage("s.bmp",y,x,t);
	return 0;
}
