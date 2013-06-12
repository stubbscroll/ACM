#include <stdio.h>
#define MAX 50
#define M 923673411

int n;
char board[MAX][MAX];
char b[MAX*9][MAX][MAX];
int h[MAX*9];
int p;

void copyp(int p)
{
   int i,j,v;

   v=0;
   for(i=0;i<n;i++) 
      for(j=0;j<n;j++) {
         b[p][i][j]=board[i][j];
         v=(v*2+board[i][j])%M;
      }
   h[p]=v;
}

void rotate(int p,int q)
{
   int i,j,v;

   for(i=0;i<n;i++)
      for(j=0;j<n;j++)
         b[q][n-j-1][i]=b[p][i][j];
   v=0;
   for(i=0;i<n;i++) 
      for(j=0;j<n;j++) {
         v=(v*2+b[q][i][j])%M;
      }
   h[q]=v;
}

int compare(int p,int q)
{
   int i,j;

   if(h[p]!=h[q]) return 0;
   return 1;
   for(i=0;i<n;i++)
      for(j=0;j<n;j++)
         if(b[p][i][j]!=b[q][i][j]) return 0;
   return 1;
}

int main()
{
   int i,x,y,j;
   char s[100],c;

   while(1) {
      if(scanf("%d",&n)!=1) break;
      if(n==0) break;
      for(x=0;x<n;x++)
         for(y=0;y<n;y++)
            board[x][y]=0;
      p=0;
      copyp(p++);
      for(i=0;i<2*n;i++) {
         scanf("%d %d %s",&x,&y,s);
         c=s[0];
         x--; y--;
         if(c=='+') board[x][y]=1;
         else if(c=='-') board[x][y]=0;
         copyp(p);
         for(j=0;j<p;j++) if(compare(j,p)) goto spool;
         rotate(p,p+1);
         rotate(p+1,p+2);
         rotate(p+2,p+3);
         p+=4;
      }
      printf("Draw\n");
      goto done;
   spool:
      printf("Player %d wins on move %d\n",((i+1)&1)+1,i+1);
      for(i++;i<2*n;i++) scanf("%d %d %s",&x,&y,s);
   done:
      ;
   }
}
