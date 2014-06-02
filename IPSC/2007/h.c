#include <stdio.h>

char b[1024][1024];
int dp[1024][1024];
int d,n;
int q[2000000],qs,qe;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

void gen(int x,int y,int size)
{
   if(size==1) return;
   int i,j,s3=size/3;
   // big block in middle
   for(i=0;i<s3;i++) for(j=0;j<s3;j++) b[x+i+s3][y+j+s3]=1;
   for(i=0;i<3;i++) for(j=0;j<3;j++) if(i!=1 || j!=1) gen(x+i*s3,y+j*s3,s3);
}

int main()
{
   int cases,x1,y1,x2,y2,x,y,moves,i,j;
   scanf("%d",&cases);
   while(cases--) {
      scanf("%d %d %d %d %d",&d,&x1,&x2,&y1,&y2);
      if(x1==x2 && y1==y2) {
         puts("0");
         continue;
      }
      n=1;
      while(d--) n*=3;
      memset(b,0,sizeof(b));
      gen(0,0,n);
      memset(dp,-1,sizeof(dp));
      x1--; y1--; x2--; y2--;
      dp[x1][y1]=0;qs=qe=0;
      q[qe++]=x1; q[qe++]=y1;
      while(qs<qe) {
         x=q[qs++];
         y=q[qs++];
         moves=dp[x][y]+1;
         for(i=0;i<4;i++) {
            x1=x+dx[i];
            y1=y+dy[i];
            if(x1<0 || y1<0 || x1>=n || y1>=n) continue;
            if(b[x1][y1]) continue;
            if(dp[x1][y1]>-1 && dp[x1][y1]<=moves) continue;
            dp[x1][y1]=moves;
            if(x1==x2 && y1==y2) {
               printf("%d\n",moves);
               goto end;
            }
            q[qe++]=x1;
            q[qe++]=y1;
         }
      }
      printf("error\n");
   end:;
   }
}
