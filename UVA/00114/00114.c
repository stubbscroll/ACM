#include <stdio.h>

int grid[51][51];      /* 1=wall, 2=bumper */
int bumperval[51][51];
int bumpercost[51][51];
int wallcost;
const int dirx[4]={1,0,-1,0};
const int diry[4]={0,1,0,-1};

int main()
{
   int xsize,ysize;
   int i,j,x,y,newx,newy,val,cost;
   int dir,life,points,tot;

   scanf("%d %d",&xsize,&ysize);
   for(i=0;i<xsize;i++)
      for(j=0;j<ysize;j++)
         grid[i][j]=0;
   for(i=0;i<xsize;i++)
      grid[i][0]=grid[i][ysize-1]=1;
   for(j=0;j<ysize;j++)
      grid[0][j]=grid[xsize-1][j]=1;
   scanf("%d",&wallcost);
   scanf("%d",&j);
   for(i=0;i<j;i++) {
      scanf("%d %d %d %d",&x,&y,&val,&cost);
      grid[x-1][y-1]=2;
      bumperval[x-1][y-1]=val;
      bumpercost[x-1][y-1]=cost;
   }
   tot=0;
   while(1) {
      points=0;
      if(scanf("%d %d %d %d",&x,&y,&dir,&life)!=4) break;
      x--; y--;
      while(--life>0) {
         newx=x+dirx[dir]; newy=y+diry[dir];
         if(grid[newx][newy]==1) {
            dir=(dir-1)&3;
            life-=wallcost;
         } else if(grid[newx][newy]==2) {
            dir=(dir-1)&3;
            points+=bumperval[newx][newy];
            life-=bumpercost[newx][newy];
         } else {
            x=newx; y=newy;
         }
/*         printf("%d %d %d %d\n",x,y,life,dir);*/
      }
      printf("%d\n",points);
      tot+=points;
   }
   printf("%d\n",tot);
}
