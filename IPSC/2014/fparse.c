/* parse file downloaded from
   https://archive.org/stream/Pi_to_100000000_places/pi.txt
   (saved as pi.html) and output it as plain text file
*/

#include <stdio.h>
#include <ctype.h>

int main() {
	int i,j;
	char s[100000];
	while(fgets(s,99999,stdin)) {
		for(i=j=0;s[i];i++) if(isdigit(s[i])) j++;
		if(j>=50 && j<62) {
			for(i=j=0;j<50;i++) if(isdigit(s[i])) putchar(s[i]),j++;
		}
	}
	return 0;
}
