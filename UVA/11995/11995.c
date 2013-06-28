#include <stdio.h>

int n;
int a[1001],b[1001];

int stack() {
	static int st[1111];
	int sp=0,i;
	for(i=0;i<n;i++) if(a[i]==1) st[sp++]=b[i];
	else if(b[i]!=st[--sp]) return 0;
	return 1;
}

int queue() {
	static int q[1111];
	int qs=0,qe=0,i;
	for(i=0;i<n;i++) if(a[i]==1) q[qe++]=b[i];
	else if(q[qs++]!=b[i]) return 0;
	return 2;
}

#include <stdio.h>

#define MAXH 1111

int heap[MAXH];   /*  heap value (on which it is sorted)  */
int heapn;        /*  (number of elements in heap)+1 */

/*  insert a new value to the heap */
/*  warning, function will choke if heap is full */
void heapinsert(int val) {
  int pos=heapn++;
  /*  change to val> for maxheap */
  while(pos>1 && val>heap[pos>>1]) {
    heap[pos]=heap[pos>>1];
    pos>>=1;
  }
  heap[pos]=val;
}

/*  remove a value from the heap and put it in *val,*id */
/*  don't call if heap is empty! */
int heapremove() {
  int pos=1,next=1,newval,val=heap[1];
  newval=heap[--heapn];
  while((pos<<1)<=heapn) {
    /*  take lowest of left and right children */
    if((pos<<1)==heapn) next=pos<<1;
    /*  change to <heap[...] for maxheap */
    else next=(pos<<1)+(heap[pos<<1]<heap[(pos<<1)+1]);
    /*  change to <=newval for maxheap */
    if(heap[next]<=newval) break;
    heap[pos]=heap[next];
    pos=next;
  }
  heap[pos]=newval;
	return val;
}

int pqueue() {
	int i;
	heapn=1;
	for(i=0;i<n;i++) if(a[i]==1) heapinsert(b[i]);
	else if(heapremove()!=b[i]) return 0;
	return 4;
}

int main() {
	int i,m;
	while(scanf("%d",&n)==1) {
		for(i=0;i<n;i++) scanf("%d %d",&a[i],&b[i]);
		m=queue()|stack()|pqueue();
		if(!m) puts("impossible");
		else if(m==2) puts("queue");
		else if(m==1) puts("stack");
		else if(m==4) puts("priority queue");
		else puts("not sure");
	}
	return 0;
}
