/* solution to hidden messages, easy input
   algorithm: shift chars to solve caesar cipher until we have sensible words.
   then, solve vigenere cipher by trying all keys in order of increasing
   length */

/* hints:
   EASY-A1 Roman emperor, 100 B.C. to 44 B.C.
   EASY-A2 Try deciphering just the first paragraph.
   EASY-A3 The original text contains the word "method".
   EASY-B1 Second part is encoded two times.
   EASY-B2 Some parts of the ciphertext repeat: Kyffo, Nilmr, Ukoyld
   EASY-B3 Having hard time finding the key? Try a wild guess ;)
   EASY-B4 What contest are you solving right now?
   EASY-B5 No ideas left? Have a break, read a book, get some inspiration.
           Lewis Carroll is recommended.
   EASY-B6 `Twas brillig, and the slithy toves / Did gyre and gimble in the
           wabe...
*/

/* solution is "total fiasco" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXS 100000
char s[MAXS];

#define WORDS 5
char w[WORDS][10]={"a","i","the","and","this"};
int sc[WORDS]=    {  1,  1,    3,    3,     4};

/* stupid test: check for presence of some normal words */
int score(char *s) {
	int r=0,i,j,p=0,q;
	char t[1000];
	while(sscanf(s+p,"%999s%n",t,&q)==1) {
		p+=q;
		for(i=j=0;t[i];i++) if(isalpha(t[i])) t[j++]=tolower(t[i]);
		t[j]=0;
		for(i=0;i<WORDS;i++) if(!strcmp(t,w[i])) r+=sc[i];
	}
	return r;
}

char caesarshift(char c) {
	if(c=='z') return 'a';
	if(c=='Z') return 'A';
	if(c>='a' && c<'z') return c+1;
	if(c>='A' && c<'Z') return c+1;
	return c;
}

int getix(char c) {
	if(c>='a' && c<='z') return c-'a';
	if(c>='A' && c<='Z') return c-'A';
	return -1;
}

int compd(const void *A,const void *B) {
	const double *a=A,*b=B;
	if(*a<*b) return 1;
	if(*a<*b) return -1;
	return 0;
}

void caesar() {
	static char t[MAXS];
	int i,j,best=-1,bestr=-1,cur;
	strcpy(t,s);
	for(i=0;i<26;i++) {
		cur=score(t);
		if(best<cur) best=cur,bestr=i;
		for(j=0;t[j];j++) t[j]=caesarshift(t[j]);
	}
	for(i=0;s[i];i++) for(j=0;j<bestr;j++) s[i]=caesarshift(s[i]);
}

void vigeneredecrypt(char *s,char *t,int *key,int len) {
	int i=0,j=0;
	for(;s[i];i++) {
		if(!isalpha(s[i])) t[i]=s[i];
		else {
			if(s[i]>='A' && s[i]<='Z') t[i]=(s[i]-'A'+26-key[j])%26+'A';
			if(s[i]>='a' && s[i]<='z') t[i]=(s[i]-'a'+26-key[j])%26+'a';
			j++;
		}
		if(j==len) j=0;
	}
	t[i]=0;
}

/* extremely stupid vigenere cracker */
void vigenere() {
	static char t[MAXS];
	int len,i,best=-1,cur;
	int key[100];
	for(len=1;;len++) {
		for(i=0;i<len;i++) key[i]=0;
		do {
			vigeneredecrypt(s,t,key,len);
			cur=score(t);
			if(best<cur) {
				best=cur;
				printf("best so far: score %d keylen %d key ",best,len);
				for(i=0;i<len;i++) printf("%c",key[i]+'A');
				printf(":\n\n");
				puts(t);
				puts("-----------------------------------------------------------------------");
			}
			for(i=0;i<len;i++) {
				key[i]++;
				if(key[i]<26) break;
				key[i]=0;
			}
		} while(i<len);
	}
}

int main() {
	int q=0,i,j;
	while(fgets(s+q,999,stdin)) q+=strlen(s+q);
	caesar();
	puts(s);
	puts("-----------------------------------------------------------------------");
	/* remove first paragraph which is decrypted */
	for(i=0;s[i];i++) if(s[i]=='\n' && s[i+1]=='\n') {
		for(i+=2,j=0;s[i];) s[j++]=s[i++];
		s[j]=0;
	}
	vigenere();
	return 0;
}
