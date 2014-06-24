/* program that checks the results from the server for empathy system.
   if the correct answer is known and there is a unique hash-tuple for at least
   190 images, then generate a new lua program and submit it */

#include <stdio.h>
#include <string.h>

#define H 10

int correct[200];
int wrongmask[200];
int hash[H][200];
int bc[16];

char s[100000];
char cs[]="1 is right, 2 is right, 1 is right, 4 is right, 3 is right, 3 is right, 4 is right, 2 is right, 3 is right, 4 is right, 1 is right, 2 is right, ";

int main() {
	int h=1,i,j,k,z,bad;
	char *p;
	for(i=0;i<200;i++) correct[i]=wrongmask[i]=0;
	while(fgets(s,99999,stdin)) {
		/* skip the 12 input images */
		if(!(p=strstr(s,cs))) printf("error");
		p+=strlen(cs);
		for(i=12;i<200;i++) {
			z=*p-'0';
			hash[h-1][i]=z;
			if(p[5]=='r') correct[i]=z;
			else wrongmask[i]|=1<<(z-1);
			p+=12;
		}
		h++;
	}
	for(i=0;i<16;i++) for(bc[i]=j=0;j<4;j++) if(i&(1<<j)) bc[i]++;
	for(bad=0,i=12;i<200;i++) {
		if(!correct[i] && bc[wrongmask[i]]==3) {
			for(j=0;j<4;j++) if(!(wrongmask[i]&(1<<j))) correct[i]=j+1;
		}
		if(!correct[i]) bad++;
	}
	/* check if each item is unique */
	for(i=12;i<200;i++) if(correct[i]) {
		for(j=12;j<200;j++) if(i!=j && correct[j]) {
			for(k=0;k<h-1;k++) if(hash[k][i]!=hash[k][j]) goto ok;
			if(correct[i]!=correct[j]) {
				bad++;
				goto notgood;
			}
		ok:;
		}
		/* good */
	notgood:;
	}
	fprintf(stderr,"number of bad images: %d\n",bad);
	for(i=12;i<200;i++) {
		printf("\t%sif hash1==%d",i==12?"":"else",hash[0][i]);
		for(j=1;j<h-1;j++) printf(" and hash%d==%d",j+1,hash[j][i]);
		printf(" then answer=%d\n",correct[i]?correct[i]:1);
	}
	puts("\t	else answer=1");
	puts("\tend");
	return 0;
}
