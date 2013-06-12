#include <stdio.h>
#include <stdlib.h>

short dist[1000000];

int main(int argc, char *argv[])
{
  long p,q,i,j,m,n,r;
  
  for(i=0;i<1000000;i++) dist[i]=0;
  while(scanf("%ld %ld",&p,&q)!=EOF) {
    if(p>q) { i=q; r=p; } else { i=p; r=q; }
    m=0;
    for(;i<=r;i++) {
      if(dist[i]) { n=dist[i]; goto ferdig; }
      j=i;
      n=1;
      while(j>1) {
        if(j<1000000 && dist[j]) {
          n+=dist[j];
          dist[i]=n;
          break;
        }
        if(j&1) j=j*3+1; else j>>=1;
        n++;
      }
ferdig:
      if(m<n) m=n;
    }
    printf("%ld %ld %ld\n",p,q,m);
  }
  return 0;
}
