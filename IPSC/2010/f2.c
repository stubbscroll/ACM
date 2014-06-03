/* solution for flawed code, hard input
   same properties as f1.c, but in addition breaks chermi's solution since he
   will put 490 and 510 in different towers when X is at least 510. hence, he
   will only use the 50's, getting a too low answer. */

#include <stdio.h>

int main() {
	puts("25");
	puts("490 510 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 1 2 4");
	return 0;
}
