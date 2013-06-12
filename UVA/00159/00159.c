#include <stdio.h>
#define MAX(x,y) (x>y)?(x):(y)

char s[4][100];
int sl[4];
int f[4][128];
int p[4];      /* horizontal pos w1, vertical pos w2, same for w3+w4 */
char c;

char o[25][25];

int main()
{
   int i,j,first=1,y,x,yp;

   while(1) {
      scanf("%s",s[0]);
      if(s[0][0]=='#') break;
      scanf("%s %s %s",s[1],s[2],s[3]);
      if(!first) printf("\n");
      else first=0;
      for(i=0;i<4;i++) {
         sl[i]=strlen(s[i]);
         for(j='A';j<='Z';j++) f[i][j]=0;
         for(j=0;j<sl[i];j++) f[i][s[i][j]]++;
      }
      for(i=0;i<2;i++) {
         for(j='A';j<='Z';j++)
            if(f[i*2][j]>0 && f[i*2+1][j]>0) goto cont;
         printf("Unable to make two crosses\n"); 
         goto end;
      cont:
         ;
      }
      for(i=0;i<2;i++) {
         /* find first common letter in horizontal word */
         for(j=0;j<sl[i*2];j++)
            if(f[i*2+1][s[i*2][j]]) {
               p[i*2]=j; break;
            }
         c=s[i*2][p[i*2]];
         /* find the first occurence of this letter in the vertical word */
         for(j=0;j<sl[i*2+1];j++)
            if(s[i*2+1][j]==c) {
               p[i*2+1]=j; break;
            }
      }
      memset(o,0,625);
      y=MAX(p[1],p[3]);
      for(i=0;i<sl[0];i++) o[y][i]=s[0][i];
      x=sl[0]+3;
      for(i=0;i<sl[2];i++) o[y][x+i]=s[2][i];
      yp=y-p[1];
      for(i=0;i<sl[1];i++) o[yp+i][p[0]]=s[1][i];
      yp=y-p[3];
      for(i=0;i<sl[3];i++) o[yp+i][x+p[2]]=s[3][i];
      y=0;
      for(i=0;i<25;i++) {
         j=23;
         while(!o[i][j] && j>=0) j--;
         if(j>=0) {
            y=i;
            for(;j>=0;j--)
               if(!o[i][j]) o[i][j]=' ';
         }
      }
      for(i=0;i<=y;i++) printf("%s\n",o[i]);
   end:
      ;
   }
}
