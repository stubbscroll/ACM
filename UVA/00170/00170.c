#include <stdio.h>

int piles[13][5];
char suits[13][5];
int pilen[13];

const char card[15]=" A23456789TJQK";

char s[100];

int val(char c)
{
   if(c=='A') return 1;
   else if(c>='2' && c<='9') return c-'0';
   else if(c=='T') return 10;
   else if(c=='J') return 11;
   else if(c=='Q') return 12;
   else if(c=='K') return 13;
   c=1/0;
}

int main()
{
   int i,j,n,k,l,c;

   while(1) {
      for(i=3;i>=0;i--) {
         gets(s);
         if(s[0]=='#') return;
         for(j=0;j<13;j++) {
            piles[12-j][i]=val(s[j*3]);
            suits[12-j][i]=s[j*3+1];
         }
      }
      for(i=0;i<13;i++) pilen[i]=4;
      n=1;
      i=k=piles[12][3];
      c=suits[12][3];
      pilen[12]--;
      while(pilen[k-1]) {
         n++;
/*         printf("%c%c ",card[k],c);*/
         pilen[k-1]--;
         j=piles[k-1][pilen[k-1]];
         c=suits[k-1][pilen[k-1]];
         k=j;
      }
      printf("%02d,%c%c\n",n,card[k],c);
   }
}
