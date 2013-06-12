#include <stdio.h>

const int dx[4]={1,0,-1,0};
const int dy[4]={0,-1,0,1};
const char dc[5]="_|_|";

const int p2[16]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
int f[16385];
char m[400][400];

int main()
{
   int minx,miny,maxx,maxy,x,y;
   int size,i,fs,j,dir,farx;

   while(1) {
      scanf("%d",&i);
      if(i==0) break;
      size=p2[i];
      fs=p2[i-1];
      f[fs]=1;
      while(fs>1) {
         dir=1;
         for(i=fs/2;i<size;i+=fs) {
            f[i]=dir;
            dir*=-1;
         }
         fs/=2;
      }
      memset(m,' ',400*400);
      maxx=minx=x=200;maxy=miny=y=200;dir=0;
      for(i=1;i<=size;i++) {
         if(dir==3) {
            y++;
            m[x][y]=dc[dir];
            if(maxx<x) maxx=x;
            if(maxy<y) maxy=y;
            if(minx>x) minx=x;
            if(miny>y) miny=y;
            y--;
         } else {
            m[x][y]=dc[dir];
            if(maxx<x) maxx=x;
            if(maxy<y) maxy=y;
            if(minx>x) minx=x;
            if(miny>y) miny=y;
         }
         x+=dx[dir]; y+=dy[dir]; dir=(dir+4+f[i])%4;
         if(dir!=1 && dir!=3) {
            x+=dx[dir]; y+=dy[dir]; 
         }
      }
      for(j=miny;j<=maxy;j++) {
         farx=0;
         for(i=minx;i<=maxx;i++) if(m[i][j]!=' ') farx=i;
         for(i=minx;i<=farx;i++) putchar(m[i][j]);
         printf("\n");
      }
      printf("^\n");
   }
}
