/* solution for judging programs, easy input
   algorithm: study the programs, guess the answer, submit output, and then
   try all submissions consistent with the first server response.
   j1_01.py: this is a well-known formula for n choose k, so this program is
             correct.
   j1_02.py: this program calculates the number of paths from (0,0) to (k,n-k)
             that need n steps. this is known to be equivalent to (n choose k),
             as there are k ways to arrange the UP steps in a string of n
             directions of UP and RIGHT. hence, this program is correct.
   j1_03.py: the step thing looks strange, but the program gives correct
             answer for all small cases.
   j1_04.py: a different recurrence that i don't recognise on the spot, but
             the program gives correct answer for all small cases.
   j1_05.py: the loop up to 20 looks fishy, and program does indeed fail
             input like (22 choose 3), so the program is wrong.
   j1_06.py: this program is very slow, but it returns the correct answer for
             all small cases.
   j1_07.py: the function recurses on n+1, which never reaches an initial
             condition. hence the program will overflow the stack and is
             therefore incorrect.
   j1_08.py: another formula that i don't recognise on the spot, gives correct
             answer for all small cases.
   j1_09.py: this program uses floating point numbers, and returns inaccurate
             anwers (for example (1 choose 0)=0.0), so it is wrong.
   j1_10.py: this program returns (1 choose 0)=0, which is wrong.
   j1_11.py: this program uses the well-known formula for the next term on a
             line in pascal's triangle, so it looks correct.
   a sensible way of proceeding is to mark all provably wrong programs as
   "bad", and let the remaining ones be "good".
*/

#include <stdio.h>

int main() {
	puts("good");
	puts("good");
	puts("good");
	puts("good");
	puts("bad");
	puts("good");
	puts("bad");
	puts("good");
	puts("bad");
	puts("bad");
	puts("good");
	return 0;
}
