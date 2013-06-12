#include <stdio.h>

int p[70];

int compi(int *a,int *b)
{
   return (*a<*b)-(*a>*b);
}

int main(int argc,char **argv)
{
   int n=100,i,k,l,ama,plr,lower,upper,disc,disked,madecut;
   char s[21];

   if(argc>1) n=strtol(argv[1],NULL,10);
   printf("%d\n",n);
   while(n--) {
      ama=rand()%10+2;
      if(rand()%20==0) ama=1;
   again2:
      lower=rand()%82+18;
      upper=rand()%82+18;
      if(lower>=upper) goto again2;
      disc=rand()%20+6;

      printf("\n");
   again:
      l=rand()%32767*100;
      k=1000000;
      for(i=0;i<69;i++) {
         p[i]=rand()%32767;
         k-=p[i];
      }
      p[69]=k;
      if(p[69]<1) goto again;
      qsort(p,70,sizeof(int),compi);
      printf("%d.00\n",l);
      for(i=0;i<70;i++) printf("%d.%04d\n",p[i]/10000,p[i]%10000);
      /* players */
      plr=rand()%74+70;
      printf("%d\n",plr);
      madecut=0;
      while(plr--) {
         for(i=0;i<21;i++) s[i]=0;
         l=rand()%15+4;
         for(i=0;i<l;i++) s[i]=rand()%26+'A';
         if(rand()%ama==0) s[i]='*';
         printf("%-20s",s);
         disked=0;
         for(i=0;i<4;i++) {
            if(disked) printf("   ");
            else if(rand()%disc==0 && madecut+plr>=70) {
               disked=1;
               printf(" DQ");
            } else {
               printf(" %02d",rand()%(upper-lower+1)+lower);
               if(i==1) madecut++;
            }
         }
         printf("\n");
      }
   }
}
