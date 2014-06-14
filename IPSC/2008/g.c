/* solution for game on words
   algorithm: minimax. traverse the game tree and evaluate the result for
   each prefix. instead of merely storing win/loss we store the number of
   moves to win or loss, where number<0 means we lose in -number moves
   and number>0 means we win in number moves.

   usage: write queries (current word) at the bottom of the input file */

/* sample run on easy input:
   me:     j
   server: ja
   me:     jad
   server: jadi
   me:     jadin
   server: OK (which means we won, as we forced the server to write jading or
           something illegal)
*/

/* sample run on hard input:
   me: i
   server: iv
   me: ivg
   server: ivgo
   me: ivgoo
   server: ivgoon
   me: ivgoond
   server: ivgoonds
   me: ivgoondse
   server: ivgoondsei
   me: ivgoondseij
   server: ivgoondseijj
   me: ivgoondseijjy
   server: ivgoondseijjyb
   me: ivgoondseijjybk
   server: OK (server forced to write r which finishes the word)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXW 1010101
#define MAXS 30

typedef struct {
	char w[MAXS];
	char best;
	char isdict;
} w_t;

w_t w[MAXW];
int nw;

int compw(const void *A,const void *B) {
	const char *a=A,*b=B;
	return strcmp(a,b);
}

int res[MAXW];

int bs(char *s) {
	int lo=0,hi=nw,mid;
	while(lo<hi) {
		mid=lo+(hi-lo)/2;
		if(strcmp(s,w[mid].w)>0) lo=mid+1;
		else hi=mid;
	}
	if(strcmp(s,w[lo].w)) return -1;
	return lo;
}

int best(int oldbest,int cur) {
	/* when losing, better to lose as slowly as possible */
	if(oldbest<0 && cur<0) return cur<oldbest?cur:oldbest;
	/* prefer winning over losing */
	if(oldbest<0 && cur>0) return cur;
	if(oldbest>0 && cur<0) return oldbest;
	/* when winning, better to win as fast as possible */
	if(oldbest>0 && cur>0) return cur<oldbest?cur:oldbest;
	printf("error-comp");
	return 0;
}

int play(char prefix[MAXS]) {
	int pos,r=-1,i,l=strlen(prefix),cur,oldr;
	char next[MAXS];
	pos=bs(prefix);
	/* if we are an illegal prefix, we won as the enemy did that */
	if(pos<0) return 1;
	if(res[pos]) return res[pos];
	/* if we are at a word, we won at the enemy made it */
	if(w[pos].isdict) return res[pos]=1;
	/* try all ways of extending prefix */
	strcpy(next,prefix);
	next[l+1]=0;
	w[pos].best=-1;
	for(i=0;i<26;i++) {
		next[l]=i+'a';
		if(bs(next)<0) continue;
		cur=-play(next);
		if(cur<0) cur--; else cur++;
		oldr=r;
		r=best(cur,r);
		if(oldr!=r) w[pos].best=i+'a';
	}
	return res[pos]=r;
}

int main() {
	int i,n,l;
	char s[100];
	scanf("%d",&n);
	nw=0;
	w[nw].w[0]=0;
	w[nw++].isdict=0;
	i=0;
	while(n--) {
		scanf("%s",s);
		strcpy(w[nw].w,s);
		w[nw++].isdict=1;
		for(l=strlen(s)-1;l;l--) {
			s[l]=0;
			strcpy(w[nw].w,s);
			w[nw++].isdict=0;
		}
	}
	qsort(w,nw,sizeof(w_t),compw);
	for(i=n=1;i<nw;i++) {
		if(!strcmp(w[n-1].w,w[i].w)) w[n-1].isdict|=w[i].isdict;
		else w[n++]=w[i];
	}
	nw=n;
	for(i=0;i<nw;i++) res[i]=0;
	s[0]=0;
	play(s);
	/* place our queries at the bottom of the input file */
	printf("at empty string: result %d best move %c\n",res[0],w[0].best);
	while(scanf("%s",s)==1) {
		n=bs(s);
		if(n<0) { puts("string doesn't exist"); continue; }
		printf("%d %s: result %d best move %c\n",n,s,res[n],w[n].best);
	}
	return 0;
}
