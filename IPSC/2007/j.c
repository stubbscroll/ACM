#include <stdio.h>

int bmp[1024][1024];
int sizex,sizey;
int q[10000000],qs,qe;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

void draw_line(int x1, int y1, int x2, int y2)
{
        int x_middle = (x1+x2)/2;
        int y_middle = (y1+y2)/2;

   bmp[x_middle][y_middle]=2; // 2=grey

        if((x1!=x2) || (y1!=y2))
        {
                if(abs(x1-x2) > abs(y1-y2))
                {
                        if(x1<x2)
                        {
                                draw_line(x1, y1, x_middle, y_middle);
                                draw_line(x_middle+1, y_middle, x2, y2);
                        }
                        else // x1>x2
                        {
                                draw_line(x1, y1, x_middle+1, y_middle);
                                draw_line(x_middle, y_middle, x2, y2);
                        }
                }
                else
                {
                        if(y1<y2)
                        {
                                draw_line(x1, y1, x_middle, y_middle);
                                draw_line(x_middle, y_middle+1, x2, y2);
                        }
                        else // y1>y2
                        {
                                draw_line(x1, y1, x_middle, y_middle+1);
                                draw_line(x_middle, y_middle, x2, y2);
                        }
                }
        }
}

int main()
{
   int cases,n,x1,y1,x2,y2,x,y,i,j,col[3];

   scanf("%d",&cases);
   while(cases--) {
      scanf("%d %d",&sizex,&sizey);
      memset(bmp,0,sizeof(bmp));
      scanf("%d",&n);
      while(n--) {
         scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
         draw_line(x1,y1,x2,y2);
      }
      qs=qe=0;
      q[qe++]=0;
      q[qe++]=0;
      bmp[0][0]=1; // 1=black
      while(qs<qe) {
         x=q[qs++];
         y=q[qs++];
         for(i=0;i<4;i++) {
            x1=x+dx[i];
            y1=y+dy[i];
            if(x1<0 || y1<0 || x1>=sizex || y1>=sizey) continue;
            if(bmp[x1][y1]) continue;
            bmp[x1][y1]=1;
            q[qe++]=x1;
            q[qe++]=y1;
         }
      }
      for(i=0;i<3;i++) col[i]=0;
      for(i=0;i<sizex;i++) for(j=0;j<sizey;j++) col[bmp[i][j]]++;
      printf("%d %d %d\n",col[0],col[2],col[1]);
   }
}
