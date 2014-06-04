/* solution to plus one, both inputs
   algorithm: solve integers normally and text manually */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char s[10000],t[10000];
char a[][2][40]={
/* easy input */
{"fourteen","fifteen"},
{"ninety","ninety-one"},
{"zero","one"},
{"forty-seven","forty-eight"},
{"fifty","fifty-one"},
{"three","four"},
{"fifty-four","fifty-five"},
{"forty-one","forty-two"},
{"minus one","zero"},
{"sixty-five","sixty-six"},
{"twenty-two","twenty-three"},
{"ninety-six","ninety-seven"},
{"thirty-eight","thirty-nine"},
{"sixty-six","sixty-seven"},
{"sixty-two","sixty-three"},
{"fifty-three","fifty-four"},
{"one","two"},
{"eight","nine"},
{"fifty-nine","sixty"},
/* hard input, here be strange numbers */
{"minus seven","minus six"},
{"two","three"},
{"evil matching","fair coin toss"}, /* ipsc 2012 problem */
{"saturn","uranus"},                /* planet */
{"nine","ten"},
{"eleven","twelve"},
{"iiiiiiiiiiiiiiiiiiiiiiiiiiiii","iiiiiiiiiiiiiiiiiiiiiiiiiiiiii"}, /* unary roman number */
{"ekans","arbok"},                  /* ?? pokemon */
{"thirty-two","thirty-three"},
{"treinta y cuatro","treinta y cinco"}, /* spanish number (34) */
{"di-di-di-di-dah dah-dah-dah-dah-dit","di-di-di-di-dit dah-dah-dah-dah-dah"}, /* morse code (49) */
{"one-one-zero-one-one-one","one-one-one-zero-zero-zero"}, /* binary in text */
{"neves-ytfif","thgie-ytfif"},      /* english backwards */
{"abcdefghijklmnopqrstuxyzwv","abcdefghijklmnopqrstuxzvwy"}, /* next permutation */
{"51x7y-n1n3","53v3n7y"},           /* leetspeak */
{"dreiundsiebzig","vierundsiebzig"}, /* german (73) */
{"soixante-quatorze","soixante-quinze"}, /* french (74) */
{"lxxviii","lxxix"},                /* roman numerals */
{"gold","mercury"},                 /* chemical elements by atomic numbers */
{"osemdesiatdevat","devatdesiat"},  /* slovak number (89) */
{"",""},
};

int main() {
	int n,i;
	while(fgets(s,9999,stdin)) {
		n=strlen(s);
		while(n && (s[n-1]=='\n' || s[n-1]=='\r')) s[--n]=0;
		n=strtol(s,0,10);
		sprintf(t,"%d",n);
		if(!strcmp(s,t)) printf("%d\n",n+1);
		else {
			for(i=0;a[i][0][0];i++) if(!strcmp(a[i][0],s)) { puts(a[i][1]); break; }
			if(!a[i][0][0]) { printf("error, [%s] not found\n",s); return 0; }
		}
	}
	while(scanf("%d",&n)==1) printf("%d\n",n+1);
	return 0;
}
