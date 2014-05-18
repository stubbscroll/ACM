/* solution to alpha centauri tennis, both inputs.
   the one who won the last ball won */

#include <stdio.h>
#include <string.h>

char s[50000];

int main() {
	int z;
	while(scanf("%d %s",&z,s)==2) printf("%c\n",s[strlen(s)-1]);
	return 0;
}
