#include <stdio.h>

int deck[52];
int pilen[16];
int top[16];
int nextpile;

char s[3];

int tocover[3];
int tn;

int value(char c)
{
   if(c=='K') return 13;
   else if(c=='Q') return 12;
   else if(c=='J') return 11;
   else if(c=='T') return 10;
   else if(c=='A') return 1;
   else if(c>='2' && c<='9') return c-'0';
   else return 1/0;
}

int istriple(int a,int b,int c)
{
   if(a==11 && b==12 && c==13) return 1;
   else if(a==11 && b==13 && c==12) return 1;
   else if(a==12 && b==11 && c==13) return 1;
   else if(a==12 && b==13 && c==11) return 1;
   else if(a==13 && b==11 && c==12) return 1;
   else if(a==13 && b==12 && c==11) return 1;
   else return 0;
}

int main()
{
   int i,j,k,l,dn=1;

   while(1) {
      for(i=0;i<52;i++) {
         scanf("%s",s);
         if(s[0]=='#') return;
         deck[i]=value(s[0]);
      }
      printf("%3d:",dn++);
      tn=nextpile=0;
      for(i=0;i<16;i++) top[i]=pilen[i]=0;
      for(i=0;i<52;i++) {
         if(!tn) {
            for(j=0;j<nextpile-1;j++)
               for(k=j+1;k<nextpile;k++) {
                  if(top[j]+top[k]==11) {
                     tn=2; tocover[0]=j; tocover[1]=k;
                     goto next;
                  }
                  for(l=k+1;l<nextpile;l++)
                     if(istriple(top[j],top[k],top[l])) {
                        tocover[0]=j; tocover[1]=k; tocover[2]=l;
                        tn=3; goto next;
                     }
               }
         }
      next:
         if(tn) {
            pilen[tocover[0]]++;
            top[tocover[0]]=deck[i];
            for(j=0;j<tn-1;j++) tocover[j]=tocover[j+1];
            tn--;
            continue;
         }
         if(nextpile==16) {
            nextpile=20; break;
         }
         pilen[nextpile]++;
         top[nextpile++]=deck[i];
      }
      if(nextpile==20)
         printf(" Overflowed on card no %d",i+1);
      else
         for(i=0;i<16;i++)
            if(pilen[i])
               printf("%3d",pilen[i]);
      printf("\n");
   }
}
