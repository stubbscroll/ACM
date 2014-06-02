/* solution for begin 4 7 add, easy input
   algorithm: convert blindly to c and run, takes 1667 seconds */

#include <stdio.h>

int stack[1000],sp;

void roll() {
	int dir=stack[--sp],depth=stack[--sp],ar[1000],i;
	for(i=0;i<depth;i++) ar[i]=stack[sp-depth+i];
	for(i=0;i<depth;i++) stack[sp-depth+i]=ar[(i+depth-dir)%depth];
}

void exch() {
	int t=stack[sp-1];
	stack[sp-1]=stack[sp-2]; stack[sp-2]=t;
}

void indeks() {
	int k=stack[--sp];
	stack[sp]=stack[sp-k-1];
	sp++;
}

void copy() {
	int n=stack[--sp],i;
	for(i=0;i<n;i++) stack[sp+i]=stack[sp+i-n];
	sp+=n;
}

void dup() {
	int a=stack[sp-1];
	stack[sp++]=a;
}

void solve() {
	int loop,i;
	sp=0;
	stack[sp++]='o'; stack[sp++]='a'; stack[sp++]='e'; stack[sp++]='t';
	stack[sp++]='c'; stack[sp++]='c'; stack[sp++]='r'; stack[sp++]='_';
	stack[sp++]='_'; stack[sp++]='t'; stack[sp++]='_'; stack[sp++]='e';
	stack[sp++]='n'; stack[sp++]='w'; stack[sp++]='_'; stack[sp++]='r';
	stack[sp++]='o'; stack[sp++]='e'; stack[sp++]='s'; stack[sp++]='i';
	stack[sp++]='h'; stack[sp++]='u'; stack[sp++]='e'; stack[sp++]='c';
	stack[sp++]='d'; stack[sp++]='i'; stack[sp++]='r'; stack[sp++]='c';
	stack[sp++]='i'; stack[sp++]='s'; stack[sp++]='r'; stack[sp++]='e';
	for(loop=0;loop<1608168553;loop++) {
		stack[sp++]=32; stack[sp++]=-3; roll();
		exch();
		stack[sp++]=2; indeks();
		stack[sp++]=32; stack[sp++]=3; roll();
		sp--;
		stack[sp++]=17; stack[sp++]=5; roll();
		stack[sp++]=3; copy();
		stack[sp++]=7; stack[sp++]=2; roll();
		sp-=3;
		stack[sp++]=28; stack[sp++]=-5; roll();
		stack[sp++]=30; stack[sp++]=2; roll();
		stack[sp++]=15; stack[sp++]=5; roll();
		exch();
		stack[sp++]=15; stack[sp++]=-4; roll();
		dup();
		stack[sp++]=9; stack[sp++]=1; roll();
		sp--;
		stack[sp++]=6; indeks();
		stack[sp++]=8; stack[sp++]=-1; roll();
		sp--;
		stack[sp++]=20; stack[sp++]=-5; roll();
		stack[sp++]=5; stack[sp++]=-1; roll();
		exch();
		stack[sp++]=5; stack[sp++]=1; roll();
		stack[sp++]=20; stack[sp++]=5; roll();
	}
	for(i=0;i<sp;i++) putchar(stack[i]);
	putchar('\n');
}

int main() {
	solve();
	return 0;
}
