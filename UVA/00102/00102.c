#include <stdio.h>

int b[9];
int m[6];
const char g[6][4]={"BCG","BGC","CBG","CGB","GBC","GCB"};

int main()
{
   int i,sm;

   do {
      for(i=0;i<9;i++)
         if(scanf("%d",&b[i])==EOF)
            return;
      m[0]=b[3]+b[6]+b[1]+b[4]+b[2]+b[8];
      m[1]=b[3]+b[6]+b[1]+b[7]+b[2]+b[5];
      m[2]=b[0]+b[6]+b[1]+b[4]+b[5]+b[8];
      m[3]=b[0]+b[3]+b[1]+b[7]+b[5]+b[8];
      m[4]=b[0]+b[6]+b[4]+b[7]+b[2]+b[5];
      m[5]=b[0]+b[3]+b[4]+b[7]+b[2]+b[8];
      sm=0;
      for(i=1;i<6;i++)
         if(m[i]<m[sm])
            sm=i;
      printf("%s %d\n",g[sm],m[sm]);
   } while(1);
}
