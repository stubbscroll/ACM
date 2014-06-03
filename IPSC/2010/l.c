#include <stdio.h>
#include <string.h>
#define MAKS(a,b) ((a)>(b)?(a):(b))
typedef long long ll;

ll pascal[2048][2048];

void genpascal(int n,ll P) {
  int i,j;
  memset(pascal,0,sizeof(pascal));
  for(i=0;i<=n;i++) {
    pascal[i][0]=pascal[i][i]=1;
    for(j=1;j<i;j++) pascal[i][j]=(pascal[i-1][j-1]+pascal[i-1][j])%P;
  }
}

inline ll antall(int n,int k) {
  if(n==0 && k==0) return 1;
  if(n==0) return 0;
  return pascal[n+k-1][k];
}

int main() {
  int cases;
  ll K,ans;
  int N,M,P,toere;
  scanf("%d",&cases);
  while(cases--) {
    scanf("%d %d %I64d %d",&N,&M,&K,&P);
    ans=0;
    genpascal(K+MAKS(N,M),P);
    for(toere=0;toere<=K/2;toere++) {
      ans=(ans+antall(M,toere)*antall(N,K-toere*2))%P;
    }
    printf("%I64d\n",ans);
  }
  return 0;
}
