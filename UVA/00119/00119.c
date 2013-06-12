#include <stdio.h>

char name[10][13];
int  money[10];
int  n;

char s[100];

int findname(char *s)
{
   int i;

   for(i=0;i<n;i++)
      if(!strcmp(s,name[i])) return i;
   printf("this shouldn't happen, %s\n",s);
   i=1/0;
}

int main()
{
   int i,j,k,l,a,first=1;

   while(1) {
      if(scanf("%d\n",&n)!=1) break;
      for(i=0;i<n;i++) {
         scanf("%s",&name[i]);
         money[i]=0;
      }
      for(i=0;i<n;i++) {
         scanf("%s %d %d",&s,&a,&j);
         k=findname(s);
         if(j==0) continue;
         money[k]-=a-(a%j);
         for(l=0;l<j;l++) {
            scanf("%s",&s);
            k=findname(s);
            money[k]+=a/j;
         }
      }
      if(!first) printf("\n");
      first=0;
      for(i=0;i<n;i++)
         printf("%s %d\n",name[i],money[i]);
   }
}
