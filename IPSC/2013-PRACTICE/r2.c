/* solution for rearranged alphabet, hard input.
   uses adleman constuction from editorial with 628 characters. */

#include <stdio.h>

int main() {
	int i,n=26,t=0,block=0;
	for(i=0;i<n*n-2*n+4;i++) {
		if(i<n) printf("%c",i+'a');
		else {
			if(block%(n-1)==0) putchar('a');
			else putchar('b'+t),t=(t+1)%(n-1);
			block++;
		}
	}
	return 0;
}
