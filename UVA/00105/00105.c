#include <stdio.h>

int top[10000];

int main()
{
   int i,l,h,r,mr,ml;
   char s[100];

   for(i=0;i<10000;i++) top[i]=0;
   mr=0; ml=10000;
   do {
      if(gets(s)==NULL) break;
      sscanf(s,"%d %d %d",&l,&h,&r);
      for(i=l;i<r;i++)
         if(top[i]<h) top[i]=h;
      if(r>mr) mr=r;
      if(l<ml) ml=l;
   } while(1);
   h=0;
   for(i=ml;i<mr;i++)
      if(h!=top[i]) {
         h=top[i];
         printf("%d %d ",i,top[i]);
      }
   printf("%d 0\n",mr);
}
