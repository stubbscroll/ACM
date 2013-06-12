#include <stdio.h>

int x,y,occ;

int backtrack(int k,int a,int b)
{
   int j;

   if(x>=a-k && x<=a+k && y>=b-k && y<=b+k)
      occ++;
   if(k==1) return;
   j=k/2;
/*   printf("%d %d %d\n",k,a,b);*/
   backtrack(j,a-k,b-k);
   backtrack(j,a+k,b-k);
   backtrack(j,a-k,b+k);
   backtrack(j,a+k,b+k);
}

int main()
{
   int k;

   while(scanf("%d %d %d",&k,&x,&y)==3) {
      if(k==0 && x==0 && y==0) break;
      occ=0;
      backtrack(k,1024,1024);
      printf("%3d\n",occ);
   }
}
