/* solution for disk space eater, easy input (in windows)
   download bzip2 for windows by following the link in the problem statement.
   then rename d1.in to d1.bzip2, unpack it (by running "bunzip d1.bzip2"),
   which results in the file d1. then run "bzcat d1 | d1.exe" (d1.exe is this
   program). you will get an error message when the file is processed, but
   only after the solution has been output. submit this output.
   this method takes 78 minutes on my machine.
*/

#include <stdio.h>

#define BLOCK 1000000

char c[BLOCK];

int main() {
	int i;
	while(fread(c,1,BLOCK,stdin)) for(i=0;i<BLOCK;i++) if(c[i]) putchar(c[i]);
	return 0;
}
