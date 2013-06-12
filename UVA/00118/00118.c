#include <stdio.h>

char scent[51][51];
/* directions: 0=north, 1=east, 2=south, 3=west */
int dirx[4]={0,1,0,-1};
int diry[4]={1,0,-1,0};
char face[5]="NESW";
char s[1000];

int main()
{
   int i,j,l,maxx,maxy,x,y,dir,lost;
   char c;

   for(i=0;i<=50;i++)
      for(j=0;j<=50;j++)
         scent[i][j]=0;
   scanf("%d %d\n",&maxx,&maxy);
   while(1) {
      if(scanf("%d %d %c\n",&x,&y,&c)!=3) break;
      switch(c) {
      case 'N':
         dir=0; break;
      case 'E':
         dir=1; break;
      case 'S':
         dir=2; break;
      case 'W':
         dir=3; break;
      default:
         printf("this shouldn't happen\n");
         i=i-i; j=x/i;
      }
      gets(s);
      l=strlen(s);
      lost=0;
      for(i=0;i<l;i++)
         if(s[i]=='L')
            dir=(dir-1)&3;
         else if(s[i]=='R')
            dir=(dir+1)&3;
         else if(s[i]=='F') {
            x+=dirx[dir];
            y+=diry[dir];
            if(x<0 || x>maxx || y<0 || y>maxy) {
               x-=dirx[dir];
               y-=diry[dir];
               if(!scent[x][y]) {
                  scent[x][y]=1;
                  lost=1;
                  break;
               }
            }
         } else {
            printf("this shouldn't happen\n");
            while(1);
         }
      printf("%d %d %c",x,y,face[dir]);
      if(lost) printf(" LOST");
      printf("\n");
   }
}
