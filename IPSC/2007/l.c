#include <stdio.h>

int R,H,T;

double dp[1024][1024];
typedef long long ll;

#define SUM(a,b) (((b)*((b)+1)-((a)*((a)-1)))/2)

double E(int r,int t)
{
   double avg=0,r1,r2;
   int i,h;
   if(dp[r][t]>-50) return dp[r][t];
   if(t==0) return 0.0;
   for(i=1;i<=r;i++) for(h=1;h<=H;h++) {
      /* take */
      r1=h+E(i,t-1);
      /* don't take */
      r2=E(r,t-1);
      avg+=(r1>r2)?r1:r2;
//      printf("for (%d %d) %d %d: best is %s (%f %f)\n",r,t,i,h,r1>r2?"r1":"r2",r1,r2);
   }
   /* add all those with too large radius */
   avg+=E(r,t-1)*H*(R-r);
//   printf("%d %d: %f\n",r,t,avg/(H*R));
   return dp[r][t]=avg/(H*R);
}

double E2(int r,int t)
{
   double avg=0,r1,r2,r0;
   int i,h1;
   if(dp[r][t]>-50) return dp[r][t];
   if(t==0) return 0.0;
   for(i=1;i<=r;i++) {
      r0=E2(i,t-1);
      r2=E2(r,t-1);
      /* least height it's good to take */
      h1=(int)(ceil(1e-9+r2-r0));
      if(h1<1) h1=1;
      if(h1>H) h1=H+1;
//      if(r==2 && t==2) printf("%d %d %d: %d %f %f\n",r,t,i,h1,r0,r2);
      avg+=(h1-1)*E2(r,t-1);
      /* sum from h1 to H */
      if(h1<=H) avg+=SUM((ll)h1,(ll)H)+E2(i,t-1)*(H-h1+1);
//      printf("%d %d: %d: %f %d %f\n",r,t,i,r2-r0,h1,avg);
   }
   /* add all those with too large radius */
   avg+=E(r,t-1)*(ll)H*(R-r);
//if(r==1 && t==1)   printf("%d %d: %f\n",r,t,avg/((ll)H*R));
   return dp[r][t]=avg/((ll)H*R);
}

int main()
{
   int cases,i,j;

   scanf("%d",&cases);
   while(cases--) {
      scanf("%d %d %d",&R,&H,&T);
//      for(i=0;i<=R;i++) for(j=0;j<=T;j++) dp[i][j]=-100;      printf("%.6f\n",E(R,T));
      for(i=0;i<=R;i++) for(j=0;j<=T;j++) dp[i][j]=-100;      printf("%.6f\n",E2(R,T));
   }
}
