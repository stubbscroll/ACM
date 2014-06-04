/* solution for (blank), hard input
   i'll do what i did for the easy input: present a sample session along with
   my ramblings.
   [since i don't know anything, i just have to submit something: hellige jul]

   Wrong answer: Not a string of six digits (0-9).
   (Note: You may make at most 30 submissions for this subproblem.)
   [next try. submit: 000000]

   Wrong answer: "000000" is not the correct answer (badness 207).
   [ok, so now the error messages aren't as nice any more. try another
    random number and see what happens. submit: 000001]

   Wrong answer: "000001" is not the correct answer (badness 204).
   [so, it seems that a smaller badness number means that our last submission
    was less bad than the one before. let's submit: 000002]

   Wrong answer: "000002" is not the correct answer (badness 203).
   [better, but apparently still very bad since we only managed to decrease the
    badness by 1 out of 204. submit: 000003]

   Wrong answer: "000003" is not the correct answer (badness 204).
   [...and we managed to make things worse again. however, now we can commence
    wild conjecturing. if we assume that 203 is the best we can get by changing
    the last digit, we notice that the badness for this digit is the square of
    of the difference to our best one, 3. so now we can jump straight into it
    and submit random 6-digit strings and collecting badness values until we
    have enough (string,badness) pairs to find a unique 6-digit string
    consistent with the badness values we already got. the solver sayeth that
    we have 490 matches, so we submit: 100000]

   Wrong answer: "100000" is not the correct answer (badness 198).
   [improvement, but most importantly another data point, bringing the number
    of solutions down to 54. submit: 010000]

   Wrong answer: "010000" is not the correct answer (badness 194).
   [9 matches now, all of the form 57(1|4|7|8)(1|4|7|8)(1|4|7|8)2.
    submit: 001000]

   Wrong answer: "001000" is not the correct answer (badness 192).
   [narrowing it down to 4 matches. submit: 000100]

   Wrong answer: "000100" is not the correct answer (badness 200).
   [the solver outputs one match. submit it: 578472]

   OK
   [yay!]

   the implementation below is from the contest itself, except that i have
   replaced the string,badness pairs with the ones above
*/

#include <stdio.h>

int num[110][2]={
{     0, 207},
{     1, 204},
{     2, 203},
{     3, 204},
{100000, 198},
{ 10000, 194},
{  1000, 192},
{   100, 200},
{-1, -1}};

int badness(int a,int b) {
	int i,bad=0,d;
	for(i=0;i<6;i++) {
		d=(a%10)-(b%10);
		bad+=d*d;
		a/=10;
		b/=10;
	}
	return bad;
}

int badnessok(int n) {
	int i;
	for(i=0;num[i][0]>-1;i++) if(badness(n,num[i][0])!=num[i][1]) return 0;
	return 1;
}

int main() {
	int i,c;
	for(c=i=0;i<1000000;i++) if(badnessok(i)) c++,printf("%d\n",i);
	printf("%d matches\n",c);
	return 0;
}
