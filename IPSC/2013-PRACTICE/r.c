/* solution to rearranged alphabet, easy input
   the first idea is to append 26 copies of the alphabet, but this is
   26*26=676 letters, which is more than the allowed 660. however, the
   only way to actually use anything from the 26th alphabet is to pick
   letters in reverse order, as two letters picked in regular order can
   be taken from the same alphabet copy. hence, only the a is used in the
   last alphabet. hence, it suffices to have 25 copies of the alphabet plus
   an "a", which is 25*26+1=651 letters.
   on the problem of how to grade this problem, see ipsc 2013 D.
*/

#include <stdio.h>

int main() {
	int i;
	for(i=0;i<25;i++) printf("abcdefghijklmnopqrstuvwxyz");
	puts("a");
	return 0;
}
