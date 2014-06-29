/* solution for hashsets, both inputs
   we know from before that java uses lo^hi, so we can break that with any
   multiple of (1<<32)+1.
   by peeking in the editorial (because reading c++ code is impossible) we
   learn that c++ hashes by taking modulo the current hash table size, which
   is 62233 most of the time.
   algorithm: we have 34508 positive multiplies of 62233*((1<<32)+1) until we
   overflow. first, insert 5000-34508 other multiples of (1<<32)+1 to fill
   the c++ hash table, then insert our 34508 numbers that break both hash
   tables simultaneously.
*/

#include <stdio.h>

int main() {
	int i;
	for(i=0;i<50000-34508;i++) printf("%I64d\n",4294967297LL*(i*62233+1));
	for(i=0;i<34508;i++) printf("%I64d\n",4294967297LL*i*62233);
	return 0;
}
