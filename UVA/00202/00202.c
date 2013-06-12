#include <stdio.h>

char s[9010];
int r;

int main()
{
   int i,j,k,c,n,d;

   while(scanf("%d %d",&n,&d)==2) {
      r=n/d; c=n%d;
      for(i=0;i<d*3;i++) {
         s[i]=(c*10)/d+'0';
         c=(c*10)%d;
      }
      /* loop on sequence length */
      for(i=1;i<d;i++) {
         /* length of sequence will always be a multiple of (d-1) */
         for(j=0;j<10;j++) {
            /* loop on sequence pos */
            for(k=i;k<d*3-j;k++)
               if(s[j+k]!=s[j+k%i]) break;
            if(k==d*3-j) goto yes;
         }
      }
   yes:
      printf("%d/%d = %d.",n,d,r);
      for(k=0;k<j;k++) printf("%c",s[k]);
      printf("(");
      for(k=0;k<i && k<50;k++) printf("%c",s[k+j]);
      if(i>50) printf("...");
      printf(")\n");
      printf("   %d = number of digits in repeating cycle\n\n",i);
   }
}
