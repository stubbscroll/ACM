#include <stdio.h>

char table[128]={
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,
   31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,
   0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,
   32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62
};

int main()
{
   char s[1000],x;
   int n,j,k,l,len;

   scanf("%d",&n);
   s[0]=1;
   while(n) {
      scanf("%s",s+1);
      k=l=1;
      while(k<strlen(s)) {
         if((s[k]>='A' && s[k]<='Z') || (s[k]>='a' && s[k]<='z')) {
            s[l]=s[k];
            l++;
         }
         k++;
      }
      s[l]=0;
      len=strlen(s+1);
      do {
         l=0;
         for(j=1;j<len;j++)
            if(table[s[j]]>table[s[j+1]]) {
               x=s[j]; s[j]=s[j+1]; s[j+1]=x; l=1;
            }
      } while(l);
      do {
         printf("%s\n",s+1);
         j=len-1;
         while(j>=0 && table[s[j]]>=table[s[j+1]])
            j--;
         if(j==0)
            break;
         l=len;
         while(table[s[j]]>=table[s[l]])
            l--;
         x=s[j]; s[j]=s[l]; s[l]=x;
         k=j+1;
         l=len;
         while(k<l) {
            x=s[k]; s[k]=s[l]; s[l]=x;
            k++;
            l--;
         }
      } while(1);
done:
      n--;
   }
}
