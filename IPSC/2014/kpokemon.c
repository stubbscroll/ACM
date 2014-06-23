/* parse https://en.wikipedia.org/wiki/List_of_Pok%C3%A9mon (to be
   fed as standard input) and output data structure to insert into solution.
   warning, this program may fail horribly when/if the wikipedia article
   changes */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char s[100000];

int main() {
	char *p;
	int a,at=1;
	while(fgets(s,99999,stdin) && strcmp(s,"<td>001</td>\n"));
	while(1) {
		if(!(p=strstr(s,"<td>"))) break;
		a=strtol(p+4,0,10);
		if(a!=at) break;
		if(!fgets(s,99999,stdin)) break;
		if(!(p=strstr(s,"title=\""))) break;
		if(!(p=strstr(p,">"))) break;
		p++;
		printf("\t{\"");
		while(isspace(*p)) p++;
		while(isalpha(*p)) putchar(tolower(*(p++)));
		printf("\",\"");
		if(!fgets(s,99999,stdin)) break;
		if(!fgets(s,99999,stdin)) break;
		if(!fgets(s,99999,stdin)) break;
		if(!fgets(s,99999,stdin)) break;
		if(!fgets(s,99999,stdin)) break;
		if(!fgets(s,99999,stdin)) break;
		if(!fgets(s,99999,stdin)) break;
		if(!fgets(s,99999,stdin)) break;
		if(!fgets(s,99999,stdin)) break;
		if(!(p=strstr(s,"</span>"))) {
			if((p=strstr(s,"<td>"))) {
				p+=4;
				while(isspace(*p)) p++;
				while(isalpha(*p)) putchar(tolower(*(p++)));
			}
		} else {
			p+=7;
			/* <i> is egg, don't parge */
			if(!strstr(p,"<i>")) {
				while(isspace(*p)) p++;
				while(isalpha(*p)) putchar(tolower(*(p++)));
			}
		}
		printf("\"},\n");
		if(!fgets(s,99999,stdin)) break;
		if(!fgets(s,99999,stdin)) break;
		if(!fgets(s,99999,stdin)) break;
		at++;
	}
	return 0;
}
