/* solution for coins, both inputs
   algorithm tries every way to pick one coin, then uses greedy.
   make algorithm stuck by having an input that needs two non-greedy
   choices: make 66, can use 50 20 20 20 5 2 2 2, cannot pick 50 or 5,
   but one of the will end up getting picked.
*/

#include <stdio.h>

int main() {
	puts("0 3 1 0 3 1 0 0 0 0 66");
	return 0;
}
