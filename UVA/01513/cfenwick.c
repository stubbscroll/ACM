#include <stdio.h>
#include <string.h>

/*  binary index (fenwick) tree code, 1-indexed tree[] */
/*  store frequencies f[1]..f[n]
    update frequency f[i] in O(log n)
    read cumulative frequency sum i=1 to k f[i] in O(log n)
    find kth smallest element in O(log n)
    read single frequency by doing read(i)-read(i-1)
    set frequency f[i]=a by doing update(a-read(i),i))
    delete element: update(-1,ix) */
/*  WARNING: don't use index 0. this case can happen if you want
    to count values in a range. instead, shift the range. */
int tree[250001],n;   /*  warning, array must be of size n+1 */
/*  initialize structure with n elements */
void deltree() {
  memset(tree,0,sizeof(int)*(n+1));
}
/*  add a to frequency with index ix */
void update(int a,int ix) {
  while(ix<=n) tree[ix]+=a,ix+=(ix&-ix);
}
/*  read cumulative frequency from 1..ix */
int read(int ix) {
  int r=0;
  while(ix) r+=tree[ix],ix-=(ix&-ix);
  return r;
}

int where[100000];
int q;

int process() {
  int a,ix,f;
  scanf("%d",&a);
  ix=where[a-1];
  f=read(ix-1);
  update(-1,ix-1);
  where[a-1]=--q;
  update(1,q);
  return f;
}

int main() {
  int cases,N,r,i;
  scanf("%d",&cases);
  while(cases--) {
    scanf("%d %d",&N,&r);
    n=r+N+2;
    deltree();
    q=r+2;
    for(i=0;i<N;i++) where[i]=i+r+2,update(1,i+r+2);
    r--;
    printf("%d",process());
    while(r--) printf(" %d",process());
    putchar('\n');
  }
  return 0;
}
