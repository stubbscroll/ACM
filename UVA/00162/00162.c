#include <stdio.h>

struct c_s {
   char v,s;
} plr[2][53],table[53];
int ptop[2],ntop;
int pbot[2],nbot;

char s[10];

int isface(char v)
{
   if(v=='J') return 1;
   else if(v=='Q') return 2;
   else if(v=='K') return 3;
   else if(v=='A') return 4;
   return 0;
}

int main()
{
   int i,j,k,face,playedface;

   while(1) {
      for(i=0;i<52;i++) {
         scanf("%s",s);
         if(s[0]=='#') return;
         plr[i&1][25-(i>>1)].v=s[1];
         plr[i&1][25-(i>>1)].s=s[0];
      }
      pbot[0]=pbot[1]=26;
      ntop=nbot=ptop[0]=ptop[1]=0;
      i=0;
      while(1) {
         if(ptop[i]==pbot[i]) goto out;
         ntop--; if(ntop<0) ntop+=53;
         table[ntop]=plr[i][ptop[i]];
         ptop[i]++; if(ptop[i]==53) ptop[i]=0;
         face=isface(table[ntop].v);
         i=(i+1)&1;
         if(!face) continue;
      phase:
         for(j=0;j<face;j++) {
            if(ptop[i]==pbot[i]) goto out;
            ntop--; if(ntop<0) ntop+=53;
            table[ntop]=plr[i][ptop[i]];
            ptop[i]++; if(ptop[i]==53) ptop[i]=0;
            playedface=isface(table[ntop].v);
            if(playedface) {
               i=(i+1)&1; face=playedface; goto phase;
            }
         }
         i=(i+1)&1;
         do {
            nbot--; if(nbot==-1) nbot=52;
            plr[i][pbot[i]]=table[nbot];
            pbot[i]++; if(pbot[i]==53) pbot[i]=0;
         } while(nbot!=ntop);
         ntop=nbot=0;
      }
   out:
      j=2-i;
      k=pbot[1-i]-ptop[1-i];
      if(k<0) k+=53;
      printf("%d%3d\n",i+1,k);
   }
}
