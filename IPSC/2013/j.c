/* solution for just a single gate, both inputs
   algorithm: try all gates, and generate all expressions for a
   single gate. the program will find all gates, and will therefore solve
   both inputs. */

#include <stdio.h>

char seen[256];

void add(int gate,int a,int b,int c) {
	int x,y,z,res=0,i,u,v,w,q;
	for(i=x=0;x<2;x++) for(y=0;y<2;y++) for(z=0;z<2;z++,i++) {
		switch(a) { case 0: u=x; break; case 1: u=y; break; default: u=z; }
		switch(b) { case 0: v=x; break; case 1: v=y; break; default: v=z; }
		switch(c) { case 0: w=x; break; case 1: w=y; break; default: w=z; }
		q=u*4+v*2+w;
		if(gate&(1<<q)) res|=1<<i;
	}
	seen[res]=1;
}

int eval(int gate,int xyz) {
	return (gate&(1<<xyz))>0;
}

void gen(int gate,int ix,int iy,int iz) {
	int i,res=0;
	for(i=0;i<8;i++) if(eval(gate,eval(ix,i)*4+eval(iy,i)*2+eval(iz,i))) res|=1<<i;
	seen[res]=1;
}

int try(int gate) {
	int i,j,k,a,b,c,prev=0,cur;
	for(i=0;i<256;i++) seen[i]=0;
	/* add all input combinations of gate */
	for(a=0;a<3;a++) for(b=0;b<3;b++) for(c=0;c<3;c++) add(gate,a,b,c);
	/* we always have gate(a,b,c) for some a,b,c where each of the is possibly
	   another expression. at the start of the following routine, a,b,c are
	   different input combinations of gate. for each gate(a,b,c), return new
	   gates and try them recursively until we cannot create more gates. */
	while(1) {
		for(cur=i=0;i<256;i++) if(seen[i]) cur++;
		if(cur==prev) break;
		for(i=0;i<256;i++) if(seen[i]) for(j=0;j<256;j++) if(seen[j]) for(k=0;k<256;k++) if(seen[k]) gen(gate,i,j,k);
		prev=cur;
	}
	/* check if we created all possible gates */
	return cur==256;
}

void brute() {
	int i,j;
	/* try all gates */
	for(i=0;i<256;i++) if(try(i)) {
		for(j=0;j<8;j++) if(i&(1<<j)) printf("1 "); else printf("0 ");
		printf("\n");
	}
}

int main() {
	brute();
	return 0;
}
