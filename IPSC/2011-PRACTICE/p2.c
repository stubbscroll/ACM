/* solution to pancakes!, hard input
   let banana=1, strawberry=1/30, chocolate=1/25, walnut=1/10.
   then costs are:
   banana pancake with chocolate: 1.15
   walnut pancake with chocolate: 1.1
   grand mix pancake: 1
   observation 1: banana pancakes with chocolate and walnut pancakes with
   chocolate are expensive indeed, and grand mix pancake costs the same as
   a regular one.
   claim: we never need many of the starred pancakes.
   case 1: 8 banana pancakes with chocolate cost 6 bananas and 80 g chocolate
   spread. with the same ingredients we can make 6 banana pancakes and 3
   chocolate pancakes, hence we never need to make as many as 8 of this type.
   case 2: 10 walnut pancakes with chocolate cost 70 walnuts and 100 g
   chocolate spread, which also yields 7 walnut pancakes and 4 chocolate
   pancakes. hence, never make 10 or more.
   case 3: we will show that there is no point in making huge amounts of
   grand mix pancakes. 30 grand mix pancakes cost 10 bananas, 90 walnuts,
   150 g strawberry jam and 150 g chocolate spread. with these we can make
   10 banana pancakes, 9 walnut pancakes, 5 strawberry pancakes and 6 chocolate
   pancakes, 30 in total. hence we don't need to consider making 30 or more,
   as making regular pancakes ties for optimal.
   algorithm: try all ways of making up to 7 banana pancakes with chocolate,
   up to 9 walnut pancakes with chocolate, up to 29 grand mix pancakes and
   use trivial greedy on the remaining ingredients. */

#include <stdio.h>

int main() {
	int T,c,y,su,sa,f,b,gs,gc,w,r,i,j,k,best,cur;
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d %d %d %d",&c,&y,&su,&sa,&f);
		scanf("%d %d %d %d",&b,&gs,&gc,&w);
		r=c*2; f*=16;
		if(r>y*2) r=y*2;
		if(r>su*4) r=su*4;
		if(r>sa*16) r=sa*16;
		if(r>f/9) r=f/9;

		/* avoid fractions, multiply bananas with lcm(banana cost denominators) */
		b*=12;
		best=0;
		for(i=0;i<8;i++) for(j=0;j<10;j++) for(k=0;k<30;k++) {
			if(i*9+k*4>b || j*7+k*3>w || k*5>gs || i*10+j*10+k*5>gc) continue;
			cur=i+j+k+(b-i*9-k*4)/12+(gs-k*5)/30+(gc-i*10-j*10-k*5)/25+(w-j*7-k*3)/10;
			if(best<cur) best=cur;
		}
		printf("%d\n",r<best?r:best);
	}
	return 0;
}
