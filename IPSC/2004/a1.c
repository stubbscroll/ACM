/* solution to andrew's revenge, easy input.
   reads output, uses stupid brute force to find input.
   solution needs 441 seconds */

#include <stdio.h>

long long mex(long long a, long long b, long long c) {
  long long d;
  if (b==0) return 1;
  if (b==1) return a%c;
  d=mex(a,b/2,c); d*=d; d%=c; d*=(b&1)?a%c:1; d%=c;
  return d;
}

int main() {
  long long x,y,z,w;
	while(scanf("%I64d %I64d %I64d",&x,&z,&w)==3) {
		for(y=0;y<=z;y++) if(mex(x,y,z)==w) {
			printf("%I64d %I64d %I64d\n",x,y,z);
			break;
		}
	}
	return 0;
}
