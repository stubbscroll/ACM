#include <stdio.h>
#include <string.h>

char dict[1001][21];
char dica[1001][21];

int main()
{
   char s[21];
   int n,i,j,f;

   n=0;
   do {
      scanf("%s",s);
      if(s[0]=='#') break;
      strcpy(dict[n++],s);
   } while(1);
   qsort(dict,n,21,strcmp);
   for(i=0;i<n;i++) {
      strcpy(dica[i],dict[i]);
      for(j=0;j<strlen(dica[i]);j++)
         dica[i][j]=tolower(dica[i][j]);
      do {
         f=0;
         for(j=0;j<strlen(dica[i])-1;j++)
            if(dica[i][j]>dica[i][j+1]) {
               f=dica[i][j]; dica[i][j]=dica[i][j+1]; dica[i][j+1]=f; f=1;
            }
      } while(f);
   }
   for(i=0;i<n;i++) {
      f=0;
      for(j=0;j<n;j++)
         if(i!=j && strcmp(dica[i],dica[j])==0)
            f=1;
      if(f==0)
         printf("%s\n",dict[i]);
   }
}
