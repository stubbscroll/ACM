#include <stdio.h>

char b[200][200];

char s[2000];
int maxx,maxy;
char f;
int i,l;

void dread(int x1,int y1,int x2,int y2)
{
   int x,y;
   char c;

   if(i==l) {
      scanf("%s",s);
      i=0; l=strlen(s);
   }
   c=s[i++];
   if(c=='0' || c=='1') {
      for(x=x1;x<x2;x++)
         for(y=y1;y<y2;y++)
            b[x][y]=c;
   } else if(c=='D') {
      dread(x1,y1,x1+(x2-x1+1)/2,y1+(y2-y1+1)/2);
      if(x1+(x2-x1+1)/2<x2) dread(x1+(x2-x1+1)/2,y1,x2,y1+(y2-y1+1)/2);
      if(y1+(y2-y1+1)/2<y2) dread(x1,y1+(y2-y1+1)/2,x1+(x2-x1+1)/2,y2);
      if(x1+(x2-x1+1)/2<x2 && y1+(y2-y1+1)/2<y2) dread(x1+(x2-x1+1)/2,y1+(y2-y1+1)/2,x2,y2);
   }
}

void dprint(int x1,int y1,int x2,int y2)
{
   int x,y;

   for(x=x1;x<x2;x++)
      for(y=y1;y<y2;y++)
         if(b[x1][y1]!=b[x][y])
            goto fail;
   printf("%c",b[x1][y1]);
   if(i%50==49) printf("\n"); i++;
   return;
fail:
   printf("D");
   if(i%50==49) printf("\n"); i++;
   dprint(x1,y1,x1+(x2-x1+1)/2,y1+(y2-y1+1)/2);
   if(x1+(x2-x1+1)/2<x2) dprint(x1+(x2-x1+1)/2,y1,x2,y1+(y2-y1+1)/2);
   if(y1+(y2-y1+1)/2<y2) dprint(x1,y1+(y2-y1+1)/2,x1+(x2-x1+1)/2,y2);
   if(x1+(x2-x1+1)/2<x2 && y1+(y2-y1+1)/2<y2) dprint(x1+(x2-x1+1)/2,y1+(y2-y1+1)/2,x2,y2);
}

int main()
{
   int x,y;

   while(scanf("%s %d %d",s,&maxy,&maxx)==3) {
      f=s[0];
      if(f=='B') {
         x=y=0;
         while(y<maxy) {
            scanf("%s",s); l=strlen(s);
            for(i=0;i<l;i++) {
               b[x++][y]=s[i];
               if(x==maxx) {
                  x=0; y++;
               }
            }
         }
      } else if(f=='D') {
         i=l=0;
         dread(0,0,maxx,maxy);
      } else if(f=='#') break;
      printf("%c%4d%4d\n",f=='D' ? 'B' : 'D',maxy,maxx);
      if(f=='D') {
         i=0;
         for(y=0;y<maxy;y++)
            for(x=0;x<maxx;x++) {
               printf("%c",b[x][y]);
               if(i%50==49) printf("\n"); i++;
            }
      } else if(f=='B') {
         i=0;
         dprint(0,0,maxx,maxy);
      }
      if(i%50) printf("\n");
   }
}
