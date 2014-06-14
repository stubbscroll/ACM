/* solution to find the meaning, hard input
   algorithm: peek in editorial.
   usage: run this program with < f2.in, pipe output to a file
   in gnuplot:
     set pointsize 0.4
     plot [:][300:0]"f2.txt" with points
   we then get the standard lorem ipsum text. spot the difference, then
   interpret the difference (or duckduckgo it). */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double conv(char *s) {
	int i,p=0;
	char t[100];
	for(i=0;s[i];i++) {
		if(s[i]=='.') t[p++]='.';
		if(s[i]>='A' && s[i]<='Z') p+=sprintf(t+p,"%d",s[i]-'A');
	}
	t[p]=0;
	return strtod(t,0);
}

int main() {
	char s[50],t[50];
	double x,y;
	char u[1000];
	/* somehow reading just tokens broke parity */
	while(fgets(u,999,stdin)) {
		if(scanf("%s %s",s,t)==2) {
			x=conv(s);
			y=conv(t);
			printf("%.2f %.2f\n",x,y);
		}
	}
	return 0;
}
