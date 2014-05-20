/* interpreter for quack strikes back.
   since the official interpreter is gone from the web, i decided it would be
   rather nice to have one, so i made one. the program is not optimized for
   user-friendliness.
   usage: pipe program to stdin */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/* set some arbitrary limits: MAX lines, MAXS-1 line length */
#define MAX 10000
#define MAXS 100
char s[MAX][MAXS];
int n;

/* yet another arbitrary limit, queue size MAXQ */
#define MAXQ 1000000
uint16_t q[MAXQ];
int pc,qs,qe;
uint16_t reg[26];

uint16_t getq() {
	uint16_t r;
	if(qs==qe) puts("error, attempt to get from empty queue"),exit(1);
	r=q[qs++]; if(qs==MAXQ) qs=0;
	return r;
}

void putq(uint16_t v) {
	if((qe+1)%MAXQ==qs) puts("attempt to push to full queue"),exit(1);
	q[qe++]=v; if(qe==MAXQ) qe=0;
}

int getregnum(char c) {
	if(c>='a' && c<='z') return c-'a';
	puts("illegal register"),exit(1);
}

/* slow, runs in linear time in number of lines */
int getlabel(char *t) {
	int i;
	for(i=0;i<n;i++) if(s[i][0]==':' && !strcmp(t,s[i]+1)) return i;
	puts("label doesn't exist"),exit(1);
}

void run() {
	uint16_t x,y;
	qs=qe=pc=0;
	while(1) {
		/* quit */
//		printf("at line %d, instr %s, a %d b %d c %d z %d, Q",pc+1,s[pc],(int)reg[0],(int)reg[1],(int)reg[2],(int)reg[25]);for(x=qs;x!=qe;x=(x+1)%MAXQ) printf(" %d",(int)q[x]);printf("\n");
		if(pc==n || !strcmp(s[pc],"Q")) return;
		else if(!strcmp(s[pc],"+")) x=getq(),y=getq(),putq(x+y),pc++;
		else if(!strcmp(s[pc],"-")) x=getq(),y=getq(),putq(x-y),pc++;
		else if(!strcmp(s[pc],"*")) x=getq(),y=getq(),putq(x*y),pc++;
		else if(!strcmp(s[pc],"/")) x=getq(),y=getq(),putq(x/y),pc++;
		else if(!strcmp(s[pc],"%")) x=getq(),y=getq(),putq(x%y),pc++;
		else if(s[pc][0]=='>') reg[getregnum(s[pc][1])]=getq(),pc++;
		else if(s[pc][0]=='<') putq(reg[getregnum(s[pc][1])]),pc++;
		else if(!strcmp(s[pc],"P")) printf("%d\n",(int)getq()),pc++;
		else if(s[pc][0]=='P') printf("%d\n",(int)reg[getregnum(s[pc][1])]),pc++;
		else if(!strcmp(s[pc],"C")) printf("%c\n",getq()&255),pc++;
		else if(s[pc][0]=='C') printf("%c\n",reg[getregnum(s[pc][1])]&255),pc++;
		else if(s[pc][0]==':') pc++;
		else if(s[pc][0]=='J') pc=getlabel(s[pc]+1);
		else if(s[pc][0]=='Z') {
			if(!reg[getregnum(s[pc][1])]) pc=getlabel(s[pc]+2);
			else pc++;
		} else if(s[pc][0]=='E') {
			if(reg[getregnum(s[pc][1])]==reg[getregnum(s[pc][2])]) pc=getlabel(s[pc]+3);
			else pc++;
		} else if(s[pc][0]=='G') {
			if(reg[getregnum(s[pc][1])]>reg[getregnum(s[pc][2])]) pc=getlabel(s[pc]+3);
			else pc++;
		} else putq(strtol(s[pc],0,10)),pc++;
	}
}

int main() {
	char t[MAXS];
	int l;
	n=0;
	while(fgets(t,MAXS-1,stdin)) {
		if(n==MAX) puts("too many lines"),exit(1);
		l=strlen(t);
		while(l && (t[l-1]=='\n' || t[l-1]=='\r')) t[--l]=0;
		strcpy(s[n++],t);
	}
	run();
	return 0;
}
