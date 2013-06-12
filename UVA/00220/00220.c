#include <stdio.h>

char board[8][8];
char tomove;
char other;

void setother()
{
   if(tomove=='W') other='B'; else other='W';
}

void changeplayer()
{
   if(tomove=='W') tomove='B'; else tomove='W';
   setother();
}

int legaldir(int i,int j,int dx,int dy)
{
   if(i+dx<0 || i+dx>=8) return 0;
   if(j+dy<0 || j+dy>=8) return 0;
   i+=dx; j+=dy;
   if(i+dx<0 || i+dx>=8) return 0;
   if(j+dy<0 || j+dy>=8) return 0;
   if(board[i][j]!=other) return 0;
   do {
      i+=dx; j+=dy;
      if(i<0 || i>7 || j<0 || j>7) return 0;
   } while(board[i][j]==other);
   if(board[i][j]==tomove) return 1;
   return 0;
}

int legalmove(int i,int j)
{
   if(legaldir(i,j,-1,-1)) return 1;
   if(legaldir(i,j,-1,0)) return 1;
   if(legaldir(i,j,-1,1)) return 1;
   if(legaldir(i,j,0,-1)) return 1;
   if(legaldir(i,j,0,1)) return 1;
   if(legaldir(i,j,1,-1)) return 1;
   if(legaldir(i,j,1,0)) return 1;
   if(legaldir(i,j,1,1)) return 1;
   return 0;
}

void swapdir(int i,int j,int dx,int dy)
{
   do {
      i+=dx; j+=dy;
      if(board[i][j]==tomove) break;
      if(board[i][j]==other) board[i][j]=tomove;
   } while(1);
}

void makemove(int sq)
{
   int i,j,b=0,w=0;

   /* check if move is legal by the current player */
   i=sq%10-1; j=sq/10-1;
   if(!legalmove(i,j)) changeplayer();
   if(legaldir(i,j,-1,-1)) swapdir(i,j,-1,-1);
   if(legaldir(i,j,-1,0)) swapdir(i,j,-1,0);
   if(legaldir(i,j,-1,1)) swapdir(i,j,-1,1);
   if(legaldir(i,j,0,-1)) swapdir(i,j,0,-1);
   if(legaldir(i,j,0,1)) swapdir(i,j,0,1);
   if(legaldir(i,j,1,-1)) swapdir(i,j,1,-1);
   if(legaldir(i,j,1,0)) swapdir(i,j,1,0);
   if(legaldir(i,j,1,1)) swapdir(i,j,1,1);
   board[i][j]=tomove;
   changeplayer();
   for(i=0;i<8;i++)
      for(j=0;j<8;j++)
         if(board[i][j]=='W') w++;
         else if(board[i][j]=='B') b++;
   printf("Black - %2d White - %2d\n",b,w);
}

void printlegalmoves()
{
   int i,j,first=1;

   for(j=0;j<8;j++)
      for(i=0;i<8;i++)
         if(board[i][j]=='-')
            if(legalmove(i,j)) {
               if(first==0) printf(" ");
               printf("(%d,%d)",j+1,i+1);
               first=0;
            }
   if(first==1) printf("No legal move.\n");
   else printf("\n");
}

int main()
{
   char s[100];
   int n,i,j;

   gets(s);
   sscanf(s,"%d",&n);
   while(n--) {
      for(i=0;i<8;i++) {
         gets(s);
         for(j=0;j<8;j++) {
            board[j][i]=s[j];
         }
      }
      gets(s);
      tomove=s[0];
      setother();
      do {
         gets(s);
         if(s[0]=='Q') break;
         else if(s[0]=='L') printlegalmoves();
         else if(s[0]=='M') {
            sscanf(s+1,"%d",&i);
            makemove(i);
         }
      } while(1);
      for(j=0;j<8;j++) {
         for(i=0;i<8;i++)
            printf("%c",board[i][j]);
         printf("\n");
      }
      if(n>0) printf("\n");
   }
}
