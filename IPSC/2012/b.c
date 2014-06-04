/* solution for (blank), easy input
   this problem is fun. here is a sample session with this problem and my
   musings:
   [i have no idea, so i just submit: sdfas]

   Wrong answer: Not a space-separated sequence of positive integers.
   (Note: You may make at most 30 submissions for this subproblem.)
   [okay, so we submit: 1]

   Wrong answer: Sum of the sequence is not 123456789.
   [now we submit: 123456789]

   Wrong answer: Sequence contains less than 6 numbers.
   [take the easy way out and submit: 123456784 1 1 1 1 1]

   Wrong answer: Element #1 must be smaller than element #2.
   [exchange #1 and #2 and submit: 1 123456784 1 1 1 1]

   Wrong answer: Element #2 must be smaller than element #3.
   [do some changes and submit: 1 2 123456783 1 1 1]

   Wrong answer: Element #3 must be smaller than element #4.
   [i think i see a system here. anticipate that the entire sequence must be
    strictly increasing, and submit: 1 2 3 4 5 123456774]

   Wrong answer: Element #3 must be a multiple of element #2.
   [a non-trivial condition. let's convert to binary:
    111010110111100110100010101. let's be bold and anticipate that element
    #n must be a multiple of element #n-1. if we take the 5 first elements
    to be the 5 least significant 1's in the binary representation of
    123456789 and let the 6th element be the rest, we clearly satisfy the
    multiplicity stuff. submit: 1 4 16 256 1024 123455488]

   OK
   [yay!]

   the code below is my old code submitted during the competition, while
   i did the session above just now, while trying to forget how i solved
   the problem originally.
*/
	 
#include <stdio.h>
#include <stdlib.h>

int a[16];

int main() {
	int i,z,t=0;
	while(1) {
		t++;
		if(t%1000000==0) printf(".");
		a[0]=rand()%10+1;
		z=123456789-a[0];
		for(i=1;i<5;i++) a[i]=a[i-1]*(rand()%5+2),z-=a[i];
		if(z%a[4]) continue;
		if(z/a[4]<=a[4]) continue;
		a[5]=z;
		for(i=0;i<6;i++) printf("%d ",a[i]);
		break;
	}
	return 0;
}
