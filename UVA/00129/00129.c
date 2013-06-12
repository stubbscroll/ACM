#include <stdio.h>

char seq[200];
int sn;

int islegal()
{
   int i,j,l,eq;

   l=strlen(seq);
   for(i=1;i<=l/2;i++) {
      eq=1;
      for(j=1;j<=i;j++)
         if(seq[sn-j]!=seq[sn-j-i]) {
            eq=0; break;
         }
      if(eq==1) return 0;
   }
   return 1;
}

int gennext(int l)
{
   int i,c;

   sn++;
   seq[sn]=0;
   if(sn==81) goto again;
   for(i=0;i<l;i++) {
      seq[sn-1]='A'+i;
      if(islegal()==1)
         return;
   }
again:
   seq[sn-1]=0;
   sn--;
   c=seq[sn-1];
   if(sn==1 && seq[sn-1]=='A'+l-1) i=1/0;
   for(i=seq[sn-1]-'@';i<l;i++) {
      seq[sn-1]='A'+i;
      if(islegal()==1)
         return;
   }
   goto again;
}

int main()
{
   int n,l,i;

   while(1) {
      scanf("%d %d",&n,&l);
      if(n==0 && l==0) break;
      sn=0;
      while(n--)
         gennext(l);
      for(i=0;i<sn;i++) {
         printf("%c",seq[i]);
         if(i<sn-1 && i%4==3 && i%64!=63) printf(" ");
         if(i<sn-1 && i%64==63) printf("\n");
      }
      printf("\n");
      printf("%d\n",sn);
   }
}
