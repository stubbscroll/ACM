#include <stdio.h>

int stud[25];
int left;
int mon,place;
int leftover;

int main()
{
   int n,k,i;

   while(1) {
      scanf("%d %d",&n,&k);
      if(n==0 && k==0) break;
      for(i=0;i<n;i++) stud[i]=0;
      left=n; mon=1; place=0; leftover=0;
      i=0;
      do {
         while(stud[i]==40) i=(i+1)%n;
         if(leftover) {
            if(leftover>40-stud[i]) {
               leftover=leftover-(40-stud[i]);
               stud[i]=40;
               printf("%3d",i+1);
               left--;
            } else {
               stud[i]+=leftover;
               if(stud[i]==40) {
                  left--;
                  printf("%3d",i+1);
               }
               leftover=0;
               mon++;
               if(mon>k) mon=1;
            }
         } else if(mon>40-stud[i]) {
            leftover=mon-(40-stud[i]);
            stud[i]=40;
            printf("%3d",i+1);
            left--;
         } else {
            stud[i]+=mon;
            if(stud[i]==40) {
               left--;
               printf("%3d",i+1);
            }
            mon++;
            if(mon>k) mon=1;
         }
         i=(i+1)%n;
      } while(left);
      printf("\n");
   }
}
