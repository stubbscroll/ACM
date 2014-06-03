/* poll problem statement from web regularly and assemble it. takes around
   an hour to reach readable state. i don't know if it is a coincidence, but
   it took longer for me to get enough characters for the paragraph describing
   how to solve the hard variant. */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>
#include <curl/easy.h>
typedef long long ll;
#define BUF 1000000

char addr[]="http://ipsc.ksp.sk/2011/practice/problems/q.html";

char t[32768];
char buffer[BUF];

int bptr;

/* need to collect everything in one huge buffer, as data can be split in the
   middle of a line */
size_t webline(void *ptr,size_t size,size_t n,void *userdata) {
	int i;
	char *t=(char *)ptr;
	for(i=0;t[i];i++) buffer[bptr++]=t[i];
	buffer[bptr]=0;
	return n;
}

void loadwebpage(char *url) {
	CURL *curl=curl_easy_init();
	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,webline);
	bptr=0;
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
}

int main() {
	ll tid;
	int i,change;
	memset(t,0,sizeof(t));
	loadwebpage(addr);
	memcpy(t,buffer,32767);
	while(1) {
		tid=clock();
		while(clock()-tid<30*CLOCKS_PER_SEC);
		loadwebpage(addr);
		change=0;
		for(i=0;buffer[i];i++) {
			if((t[i]==32 || t[i]==0) && buffer[i]!=t[i]) {
				change=1;
				t[i]=buffer[i];
			}
		}
		if(change) puts(t);
	}
	return 0;
}
