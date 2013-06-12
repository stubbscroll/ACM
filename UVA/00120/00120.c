#include <stdio.h>

int pancake[30];
int sorted[30];
int pancakes;
char s[1000];
int first;

int compint (int *a,int *b)
{
   return (*a>*b)-(*a<*b);
}

void flip(int n)
{
   int i;
   int pan[30];

   if(!first) printf(" ");
   first=0;
   printf("%d",n+1);
   for(i=0;i<pancakes-n;i++)
      pan[i]=pancake[i];
   for(i=0;i<=pancakes-n;i++)
      pancake[pancakes-n-i-1]=pan[i];
}

int main()
{
   int i,j,m;

   do {
      if(gets(s)==NULL) break;
      j=0;
      while(iswspace(s[j])) j++;
      for(i=0;i<30;i++) {
         sscanf(s+j,"%d",&pancake[i]);
         while(isdigit(s[j])) j++;
         while(iswspace(s[j])) j++;
         if(s[j]==0) break;
      }
      pancakes=i+1;
      first=1;
      for(i=0;i<pancakes;i++) {
         printf("%d",pancake[i]);
         if(i<pancakes-1) printf(" ");
         sorted[i]=pancake[i];
      }
      printf("\n");
      qsort(sorted,pancakes,sizeof(int),compint);
loop:
      for(i=pancakes-1;i>=0;i--)
         if(sorted[i]!=pancake[i])
            goto change;
      goto solved;
change:
      i++;
      m=0;
      for(j=0;j<i;j++)
         if(pancake[j]>pancake[m])
            m=j;
      if(m==0)
         flip(pancakes-i);
      else {
         flip(pancakes-m-1);
         flip(pancakes-i);
      }
/*      printf("\n");
      for(i=0;i<pancakes;i++) {
         printf("%d",pancake[i]);
         if(i<pancakes-1) printf(" ");
      }
      printf("\n");*/
      goto loop;
solved:
      if(!first) printf(" ");
      printf("0\n");
   } while(1);
}
