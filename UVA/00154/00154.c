#include <stdio.h>

char c[100][5]; /* 0:red 1:orange 2:yellow 3:green 4:blue */
char s[1000];

int main()
{
   int n,i,j,k,best,min,val;

   while(1) {
      n=0;
      while(1) {
         gets(s);
         if(s[0]=='#') return;
         if(s[0]=='e') break;
         for(i=0;i<5;i++)
            switch(s[i*4]) {
            case 'r':
               c[n][0]=s[i*4+2]; break;
            case 'o':
               c[n][1]=s[i*4+2]; break;
            case 'y':
               c[n][2]=s[i*4+2]; break;
            case 'g':
               c[n][3]=s[i*4+2]; break;
            case 'b':
               c[n][4]=s[i*4+2]; break;
            }
         n++;
      }
      best=-1; min=999999999;
      for(i=0;i<n;i++) {
         val=0;
         for(j=0;j<n;j++)
            for(k=0;k<5;k++)
               if(c[i][k]!=c[j][k]) val++;
         if(val<min) {
            min=val; best=i;
         }
      }
      printf("%d\n",best+1);
   }
}
