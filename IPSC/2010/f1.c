/* solution for flawed code, easy input
   both test cases break alla's solution which only looks at the 15 lowest
   cubes and outputs 350, 350 instead of 1000, 900.
   both test cases break bob's solution, as it isn't possible to build two
   towers of equal height with all cubes except up to two, so it outputs 0.
   both test cases break dominika's solution which uses some cubes twice,
   outputting 1003, 903 instead of 1000, 900.
*/

#include <stdio.h>

int main() {
	puts("24");
	puts("1000 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 1 2 4");
	puts("22");
	puts("900 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 1 2 4");
	return 0;
}