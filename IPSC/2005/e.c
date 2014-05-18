/* solution for exact? approximate! easy input.
   algorithm: try all denominators up to given precision (10^digits),
   which can mean up to 10^9.
   uses integer arithmetic, couldn't get correct answer with doubles */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

void solve(char *s) {
	ll lim=1;
	ll teller,nevner,val=strtol(s+2,0,10);
	ll lo1=val*10-5,lo2=10;
	ll hi1=val*10+5,hi2=10;
	double v=strtod(s,0);
	int d=strlen(s)-2,i;
	for(i=0;i<d;i++) lim*=10;
	lo2*=lim; hi2*=lim;
	for(nevner=1;;nevner++) {
		teller=(int)(v*nevner);
		if(teller*lo2>=nevner*lo1 && teller*hi2<nevner*hi1) break;
		teller++;
		if(teller*lo2>=nevner*lo1 && teller*hi2<nevner*hi1) break;
	}
	printf("%d %d\n",(int)teller,(int)nevner);
}

int main() {
	char s[20];
	while(scanf("%19s",s)==1) solve(s);
	return 0;
}
