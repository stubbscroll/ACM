/* solution for just a single gate, both inputs
   algorithm: check the 5 properties mentioned in the editorial (also,
   see comments below) */

#include <stdio.h>

int eval(int gate,int xyz) {
	return (gate&(1<<xyz))>0;
}

int try(int gate) {
	int x,y,z,e,i,ax=0,nx=0,ay=0,ny=0,az=0,nz=0;
	/* check truth preservation: gate(1,1,1)=1 */
	if(gate&128) return 1;
	/* check falsehood preservation: gate(0,0,0)=0 */
	if(!(gate&1)) return 1;
	/* check monotonicity: changing input from 0 to 1 never changes output
	   from 1 to 0 */
	for(x=0;x<2;x++) for(y=0;y<2;y++) for(z=0;z<2;z++) {
		e=eval(gate,x*4+y*2+z);
		if(!x && e && !eval(gate,1*4+y*2+z)) goto ok;
		if(!y && e && !eval(gate,x*4+1*2+z)) goto ok;
		if(!z && e && !eval(gate,x*4+y*2+1)) goto ok;
	}
	return 1;
	/* check self-duality: negating all inputs always negates output */
ok:
	for(i=0;i<4;i++) if(((gate>>i)&1)==((gate>>(7-i))&1)) goto next;
	return 1;
next:
	/* check affinity: each input either never influences result, or always
	   influences result */
	for(x=0;x<2;x++) for(y=0;y<2;y++) {
		if(eval(gate,0*4+z*2+y)==eval(gate,1*4+z*2+y)) nx=1; else ax=1;
		if(eval(gate,x*4+0*2+y)==eval(gate,x*4+1*2+y)) ny=1; else ay=1;
		if(eval(gate,x*4+y*2+0)==eval(gate,x*4+y*2+1)) nz=1; else az=1;
	}
	return ax+nx==1 && ay+ny==1 && az+nz==1;
}

int main() {
	int gate,i;
	for(gate=0;gate<256;gate++) if(!try(gate)) {
		for(i=0;i<8;i++) if(gate&(1<<i)) printf("1 "); else printf("0 ");
		printf("\n");
	}
	return 0;
}
