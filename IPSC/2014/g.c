/* solution for hashsets, easy input
   observation: java hashes with something equivalent to (val^(val>>32)),
   so we can easily make the hash zero by making sure the lower 32 bits are
   equal to the upper 32 bits.
   algorithm: output first 50000 multiples of 1+(1<<32). */

#include <stdio.h>

int main() {
	int i;
	for(i=0;i<50000;i++) printf("%I64d\n",(1+(1LL<<32))*i);
	return 0;
}
