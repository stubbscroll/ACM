/* solution for trolls, both inputs
   algorithm: generate all substrings that occur a unique number of times, then
   use binary search and use server feedback (fewer, more) to eliminate halves.
   find substrings by using an inefficient suffix array construction algorithm,
   and for each pair (all of them, not just adjacent) of suffixes, find largest
   common prefix (by brute force). the number of such substrings is the
   difference between them in the suffix array+1. then, count all counts and
   pick the unique ones. runtime: not too pretty but preprocessing is instant
   for the hard input */

/* usage: c [l1 l2 verdict] < input
   the first time c is run, it will output a word, and two integers l1 and l2.
   the integers are output to stderr, so stdout can be submitted as is.
   on subsequent runs, l1 and l2 are the integers output from the last run and
   verdict is the feedback from the server (either 'more' or 'fewer', without
   quotes). input is the input file. the output is the next guess */

/* sequence for solving easy input:
   [me] c < input
   [output] w 0 7
   [server] Wrong answer: There are fewer Trolls than 'w's in my forest.
   [me] c 0 7 fewer < input
   [output] b 4 7
   [server] Wrong answer: There are fewer Trolls than 'b's in my forest.
   [me] c 6 7 fewer < input
   [output] wolf 6 7
   [server] OK
   summary: submitted: w b wolf (2 WA before OK)
*/

/* sequence for solving hard input:
   [me] c < input
   [output] ijhijhijh 0 83
   [server] Wrong answer: There are fewer Trolls than 'ijhijhijh's in my forest.
   [me] c 0 83 fewer < input
   [output] ai 42 83
   [server] Wrong answer: There are more Trolls than 'ai's in my forest.
   [me] c 42 83 more < input
   [output] ijhijhijhij 42 62
   [server] Wrong answer: There are more Trolls than 'ijhijhijhij's in my forest.
   [me] c 42 62 more < input
   [output] ijhijhijhi 42 52
   [server] Wrong answer: There are fewer Trolls than 'ijhijhijhi's in my forest.
   [me] c 42 52 fewer < input
   [output] jhijhijhij 48 52
   [server] Wrong answer: There are more Trolls than 'jhijhijhij's in my forest.
   [me] c 48 52 more < input
   [output] ababa 48 50
   [server] Wrong answer: There are more Trolls than 'ababa's in my forest.
   [me] c 48 50 more < input
   [output] babab 48 49
   [server] OK
   summary: submitted: ijhijhijh ai ijhijhijhij ijhijhijhi jhijhijhij ababa babab
     (6 WA before OK)
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 7000

char s[MAX+1];
int n;

char *sa[MAX];
int N;

int cc[MAX+1];

/* all substrings that occur at least twice, along with their count */
typedef struct {
	int i,j;
	int cnt;
} subs_t;

subs_t subs[MAX*MAX];
int su;

typedef struct {
	char *s;
	int len,count;
} sub_t;

sub_t sub[MAX];
int sn;

int comps(const void *A,const void *B) {
	char *const*a=A,*const*b=B;
	return strcmp(*a,*b);
}

int comp2(const void *A,const void *B) {
	const sub_t *a=A,*b=B;
	if(a->count>b->count) return -1;
	return 1;
}

void printstr(char *s,int len) {
	while(len--) putchar(*(s++));
}

void findwords() {
	int i,j,k,l;
	char *t,*u;
	N=n-1;
	for(i=0;i<N;i++) sa[i]=s+i;
	qsort(sa,N,sizeof(char *),comps);
	for(su=i=0;i<N;i++) for(j=i+1;j<N;j++) {
		t=sa[i]; u=sa[j];
		for(k=0;t[k]==u[k];k++);
		if(k) {
			/* if interval can be extended, ignore it */
			if(i) {
				for(l=0;l<k;l++) if(sa[i-1][l]!=sa[i][l]) break;
				if(l==k) goto ignore;
			}
			if(j<N-1) {
				for(l=0;l<k;l++) if(sa[j+1][l]!=sa[i][l]) break;
				if(l==k) goto ignore;
			}
			subs[su].i=t-s,subs[su].j=k,subs[su++].cnt=j-i+1;
		} else break;
	ignore:;
	}
	for(i=0;i<=n;i++) cc[i]=0;
	for(i=0;i<su;i++) cc[subs[i].cnt]++;
	for(sn=i=0;i<su;i++) if(cc[subs[i].cnt]==1) sub[sn].s=s+subs[i].i,sub[sn].len=subs[i].j,sub[sn++].count=subs[i].cnt;
	qsort(sub,sn,sizeof(sub_t),comp2);
}

int main(int argc,char **argv) {
	int p=0,lo,hi,mid;
	while(scanf("%s",s+p)==1) p+=strlen(s+p);
	n=strlen(s);
	findwords();
	if(argc<4) lo=0,hi=sn;
	else {
		lo=strtol(argv[1],0,10);
		hi=strtol(argv[2],0,10);
		mid=lo+(hi-lo)/2;
		if(!strcmp(argv[3],"fewer")) lo=mid+1;
		else hi=mid;
	}
	mid=lo+(hi-lo)/2;
	printstr(sub[mid].s,sub[mid].len);
	fprintf(stderr," %d %d",lo,hi);
	printf("\n");
	return 0;
}
