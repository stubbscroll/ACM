#include <stdio.h>

const int pip[7][7]={
   {1,2,3,4,5,6,7},{2,8,9,10,11,12,13},{3,9,14,15,16,17,18},
   {4,10,15,19,20,21,22},{5,11,16,20,23,24,25},{6,12,17,21,24,26,27},
   {7,13,18,22,25,27,28}};
char m[8][7];
char pt[28];
int  b[8][7];

int sols;

void btrack(int x,int y,int p)
{
   int x1,y1,pp;

   x1=x; y1=y;
   if(p==28) {
      for(y1=0;y1<7;y1++) {
         printf(" ");
         for(x1=0;x1<8;x1++) printf("%4d",b[x1][y1]);
         printf("\n");
      }
      printf("\n");
      sols++;
      return;
   }
   if(x1==8) {
      x1=0; y1++;
      if(y1==7) return;
   }
   while(b[x1][y1]) {
      x1++;
      if(x1==8) {
         x1=0; y1++;
         if(y1==7) return;
      }
   }
   if(x1<7 && !b[x1+1][y1]) {
      pp=pip[m[x1][y1]][m[x1+1][y1]];
      if(!pt[pp]) {
         pt[pp]=1;
         b[x1][y1]=b[x1+1][y1]=pp;
         btrack(x1+1,y1,p+1);
         b[x1][y1]=b[x1+1][y1]=0;
         pt[pp]=0;
      }
   }
   if(y1<6 && !b[x1][y1+1]) {
      pp=pip[m[x1][y1]][m[x1][y1+1]];
      if(!pt[pp]) {
         pt[pp]=1;
         b[x1][y1]=b[x1][y1+1]=pp;
         btrack(x1+1,y1,p+1);
         b[x1][y1]=b[x1][y1+1]=0;
         pt[pp]=0;
      }
   }
}

int main()
{
   int layout=1,i,j,first=1,k;

   while(1) {
      memset(b,0,7*8*sizeof(int));
      memset(pt,0,28);
      for(j=0;j<7;j++)
         for(i=0;i<8;i++) {
            if(scanf("%d",&k)!=1) return;
            m[i][j]=k;
         }
      if(!first) printf("\n\n\n");
      else first=0;
      printf("Layout #%d:\n\n",layout);
      for(j=0;j<7;j++) {
         printf(" ");
         for(i=0;i<8;i++) printf("%4d",m[i][j]);
         printf("\n");
      }
      printf("\nMaps resulting from layout #%d are:\n\n",layout);
      sols=0;
      btrack(0,0,0);
      printf("There are %d solution(s) for layout #%d.\n",sols,layout++);
   }
}
