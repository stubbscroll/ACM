#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define SWAP(a,b) t=a; a=b; b=t;

int p[2000],q[2000],t,n;


int a[2000],b[2000],c[2000],d[2000];
char pos[2000][2000];
char meet[2000][2000]; /* boy i has met girl j */
int test() {
  int i,j;
  for(i=0;i<n;i++) for(j=0;j<n;j++) meet[i][j]=pos[i][j]=0;
  for(i=0;i<n;i++) a[i]=b[i]=i;
  for(i=0;i<n;i++) {
    for(j=0;j<n;j++) {
      if(pos[j][a[j]]) return 0;
      pos[j][a[j]]=1;
    }
    for(j=0;j<n;j++) {
      if(meet[a[j]][b[j]]) return 0;
      meet[a[j]][b[j]]=1;
    }
    /* apply */
    for(j=0;j<n;j++) {
      /* boy at position i (a[i]) goes to position p[i] */
      c[p[j]-1]=a[j];
      d[q[j]-1]=b[j];
    }
    memcpy(a,c,sizeof(int)*n);
    memcpy(b,d,sizeof(int)*n);
  }
  return 1;
}

int main() {
  int cases,i,first=1;
  scanf("%d",&cases);
  while(cases--) {
    scanf("%d",&n);
    if(!first) puts("");
    else first=0;
    if(n==1) puts("1\n1");
    else if(n==2 || n%2==0) puts("Impossible");
    else if(n&1) {
      for(i=0;i<n;i++) printf("%d%c",(i+1)%n+1,i==n-1?'\n':' ');
      for(i=0;i<n;i++) printf("%d%c",(i+n-1)%n+1,i==n-1?'\n':' ');
    } else {
      for(i=0;i<n;i++) p[i]=(n-i+n-2)%n+1;
      for(i=0;i<n;i++) q[i]=(i+n-1)%n+1;
      for(i=0;i<n;i++) printf("%d%c",p[i],i==n-1?'\n':' ');
      for(i=0;i<n;i++) printf("%d%c",q[i],i==n-1?'\n':' ');
    }
  }
  return 0;
}
