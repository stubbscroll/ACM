#include <stdio.h>
#include <stdlib.h>

#define MAX 131072

/*  red-black tree (with order statistics)
    NB, nodes start at index 1, index 0 is a sentinel node */

int value[MAX];
int p[MAX];
int left[MAX];
int right[MAX];
int count[MAX];
char col[MAX];
int root;
int n;
int rbq[MAX],rbqn;  /*  queue for reusing deleted nodes */

int rbindex[MAX];   /*  given value, find index in tree */

void printtree() {
  int i;
  printf("root %d\n",root);
  for(i=0;i<n;i++) printf("node %d value %d parent %d left %d right %d count %d col %d\n",i,value[i],
    p[i],left[i],right[i],count[i],col[i]);
}

int sanitytell;

void sanitycount(int at,int found) {
  if(!at) {
    if(sanitytell<0) sanitytell=found;
    else if(sanitytell!=found) printf("error, path with %d (%d) nodes\n",found,sanitytell);
  } else {
    sanitycount(left[at],found+(col[at]==0));
    sanitycount(right[at],found+(col[at]==0));
  }
}

void sanity() {
  int i;
  for(i=1;i<n;i++) if(count[i]) {
    if(col[i] && col[p[i]]) printf("error, two red nodes adjacent\n");
/*    if(left[i] && value[left[i]]>value[i]) printf("error, %d is left child of %d\n",value[left[i]],value[i]);
    if(right[i] && value[right[i]]<value[i]) printf("error, %d is right child of %d\n",value[right[i]],value[i]);*/
    if(count[i]!=1+count[left[i]]+count[right[i]]) printf("error, node %d has count %d (%d %d)\n",i,count[i],count[left[i]],count[right[i]]);
  }
  sanitytell=-1;
  if(col[root]) puts("error, root is red");
  if(col[0]) puts("error, sentinel is red");
  sanitycount(root,0);
}

void rbinit() {
  n=1;
  rbqn=root=p[0]=left[0]=right[0]=col[0]=count[0]=0;
}

int rblev[32];

int rbbtr(int lo,int hi,int prev,int depth) {
  int mid=(hi+lo)>>1;
  count[mid]=hi-lo+1;
  col[mid]=rblev[depth];
  p[mid]=prev;
  left[mid]=mid>lo?rbbtr(lo,mid-1,mid,depth+1):0;
  right[mid]=mid<hi?rbbtr(mid+1,hi,mid,depth+1):0;
  return mid;
}

/*  build a perfectly balanced tree with N nodes. assume that rbinit() is
    called, and that value[] is filled in. */
/*  also initialize rbindex[] yourself whenever needed */
void rbbuildtree(int N) {
  int sum=0,lev;
  for(lev=0;sum<N;lev++) {
    sum+=1<<lev;
    rblev[lev]=lev&1;
    if(sum>N) rblev[lev]=1,rblev[lev-1]=0;
  }
  root=rbbtr(1,N,0,0);
  n=N+1;
}

void rbleftrotate(int x) {
  int y=right[x];
  right[x]=left[y];
  if(left[y]) p[left[y]]=x;
  p[y]=p[x];
  if(!p[x]) root=y;
  else if(x==left[p[x]]) left[p[x]]=y;
  else right[p[x]]=y;
  left[y]=x;
  p[x]=y;
  count[y]=count[x];
  count[x]=1+count[left[x]]+count[right[x]];
}

void rbrightrotate(int x) {
  int y=left[x];
  left[x]=right[y];
  if(right[y]) p[right[y]]=x;
  p[y]=p[x];
  if(!p[x]) root=y;
  else if(x==right[p[x]]) right[p[x]]=y;
  else left[p[x]]=y;
  right[y]=x;
  p[x]=y;
  count[y]=count[x];
  count[x]=1+count[left[x]]+count[right[x]];
}

int rbnewnode(int val) {
  int ix;
  if(rbqn) ix=rbq[--rbqn];
  else ix=n++;
  value[ix]=val;
  count[ix]=1;
  rbindex[val]=ix;    /*  added for by-value lookup */
  return ix;
}

void rbinsertfixup(int z) {
  int y;
  while(col[p[z]]) {
    if(p[z]==left[p[p[z]]]) {
      y=right[p[p[z]]];
      if(col[y]) col[p[z]]=col[y]=0,col[p[p[z]]]=1,z=p[p[z]];
      else {
        if(z==right[p[z]]) z=p[z],rbleftrotate(z);
        col[p[z]]=0;
        col[p[p[z]]]=1;
        rbrightrotate(p[p[z]]);
      }
    } else {
      y=left[p[p[z]]];
      if(col[y]) col[p[z]]=col[y]=0,col[p[p[z]]]=1,z=p[p[z]];
      else {
        if(z==left[p[z]]) z=p[z],rbrightrotate(z);
        col[p[z]]=0;
        col[p[p[z]]]=1;
        rbleftrotate(p[p[z]]);
      }
    }
  }
  col[root]=0;
}

void rbinsert(int val) {
  int z=rbnewnode(val),y=0,x=root;
  while(x) y=x,x=value[z]<value[x]?left[x]:right[x];
  p[z]=y;
  if(!y) root=z;
  else if(value[z]<value[y]) left[y]=z;
  else right[y]=z;
  left[z]=right[z]=0;
  col[z]=1;
  x=p[z];
  while(x) count[x]++,x=p[x];
  rbinsertfixup(z);
}

int rbtreeminimum(int x) {
  while(left[x]) x=left[x];
  return x;
}

void rbdeletefixup(int x) {
  int w;
  while(x!=root && !col[x]) {
    if(x==left[p[x]]) {
      w=right[p[x]];
      if(col[w]) {
        col[w]=0;
        col[p[x]]=1;
        rbleftrotate(p[x]);
        w=right[p[x]];
      }
      if(!col[left[w]] && !col[right[w]]) col[w]=1,x=p[x];
      else {
        if(!col[right[w]]) col[left[w]]=0,col[w]=1,rbrightrotate(w),w=right[p[x]];
        col[w]=col[p[x]];
        col[p[x]]=col[right[w]]=0;
        rbleftrotate(p[x]);
        x=root;
      }
    } else {
      w=left[p[x]];
      if(col[w]) {
        col[w]=0;
        col[p[x]]=1;
        rbrightrotate(p[x]);
        w=left[p[x]];
      }
      if(!col[right[w]] && !col[left[w]]) col[w]=1,x=p[x];
      else {
        if(!col[left[w]]) col[right[w]]=0,col[w]=1,rbleftrotate(w),w=left[p[x]];
        col[w]=col[p[x]];
        col[p[x]]=col[left[w]]=0;
        rbrightrotate(p[x]);
        x=root;
      }
    }
  }
  col[x]=0;
}

int rbtreesuccessor(int x) {
  int y;
  if(right[x]) return rbtreeminimum(right[x]);
  y=p[x];
  while(y && x==right[y]) x=y,y=p[y];
  return y;
}

/*  delete node with index z */
/*  the space taken by node z might be reoccupied by another node,
    so that another index actually gets freed */
void rbdelete(int z) {
  int y=!left[z]||!right[z]?z:rbtreesuccessor(z);
  int x=left[y]?left[y]:right[y];
  p[x]=p[y];
  if(!p[y]) root=x;
  else if(y==left[p[y]]) left[p[y]]=x;
  else right[p[y]]=x;
  if(y!=z) {
    value[z]=value[y];
    rbindex[value[z]]=z;  /*  added for by-value lookup */
  }
  rbq[rbqn++]=y;
  count[y]=0;
  z=p[y];
  while(z) count[z]--,z=p[z];
  if(!col[y]) rbdeletefixup(x);
}

/*  find index of k-th element in subtree rooted at at (k is 0-indexed) */
int rbfindrank(int k,int at) {
  while(k!=count[left[at]]) {
    if(k>count[left[at]]) k-=count[left[at]]+1,at=right[at];
    else at=left[at];
  }
  return at;
}

/*  given index to node, find its rank in tree */
int rbfindrankbyindex(int y) {
  int r=count[left[y]];
  while(y!=root) {
    if(y==right[p[y]]) r+=count[left[p[y]]]+1;
    y=p[y];
  }
  return r;
}

/*  insert element such that it gets rank k (0-indexed) */
void rbinsertrank(int val,int k) {
  int z=rbnewnode(val),y=0,x=root;
  while(x) {
    y=x;
    if(k<=count[left[x]]) x=left[x];
    else x=right[x],k-=1+count[left[x]];
  }
  p[z]=y;
  if(!y) root=z;
  else if(k) right[y]=z;
  else left[y]=z;
  left[z]=right[z]=0;
  col[z]=1;
  x=p[z];
  while(x) count[x]++,x=p[x];
  rbinsertfixup(z);
}

int process(int val) {
  int ix=rbindex[val];
  int r=rbfindrankbyindex(ix);
  rbdelete(ix);
  rbinsertrank(val,0);
  return r;
}

int main() {
  int i,N,q,a;
  int cases;
  scanf("%d",&cases);
  while(cases--) {
    scanf("%d %d",&N,&q);
    rbinit();
    for(i=1;i<=N;i++) value[i]=i,rbindex[i]=i;
    rbbuildtree(N);
/*    for(i=1;i<=N;i++) rbinsert(i);*/
    q--;
    scanf("%d",&a);
    printf("%d",process(a));
    while(q--) {
      scanf("%d",&a);
      printf(" %d",process(a));
    }
    putchar('\n');
  }
  return 0;
}
