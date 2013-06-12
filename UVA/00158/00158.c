#include <stdio.h>

const int days[12]={0,31,59,90,120,151,181,212,243,273,304,334};

struct e_s {
   int d,m;     /* date, month */
   int days;    /* days from 1.1 */
   int w;       /* how many days before to warn */
   int p;       /* place in input file */
   int imp;     /* importance */
   char s[257];
} list[10000],e[10000];
int l;

int year;

char s[300];

int compevent(struct e_s *a,struct e_s *b)
{
   if(a->days < b->days) return -1;
   if(a->days > b->days) return 1;
   if(a->imp > b->imp) return -1;
   if(a->imp < b->imp) return 1;
   return (a->p > b->p)-(a->p < b->p);
}

int leap(int y)
{
   return (y%4==0);
}

int main()
{
   int i,j,k,d,m,imp,first=1;

   gets(s);
   sscanf(s,"%d",&year);
   gets(s);
   l=0;
   while(s[0]=='A') {
      sscanf(s,"A %d %d %d%n",&d,&m,&list[l].w,&i);
      while(s[i]==' ') i++;
      strcpy(list[l].s,s+i);
      j=days[m-1]+d;
      if(m>=3 && leap(year)) j++;
      list[l].d=d;
      list[l].m=m;
      list[l].days=j;
      list[l].p=l;
      l++;
      gets(s);
   }
   while(s[0]=='D') {
      sscanf(s,"D %d %d",&d,&m);
      j=days[m-1]+d;
      if(m>=3 && leap(year)) j++;
      if(!first) printf("\n");
      else first=0;
      printf("Today is: %2d %2d\n",d,m);
      k=0;
      for(i=0;i<l;i++) {
         m=list[i].days;
         if(m<j) {
            m+=365+leap(year);
         }
         if(j<=m && j>=m-list[i].w) {
            e[k]=list[i];
            e[k].days=m;
            if(j==m) e[k].imp=10;
            else e[k].imp=e[k].w-m+j+1;
            k++;
         }
      }
      qsort(e,k,sizeof(e[0]),compevent);
      for(i=0;i<k;i++) {
         printf(" %2d %2d ",e[i].d,e[i].m);
         imp=e[i].imp;
         if(imp==10) printf("*TODAY* ");
         else if(imp==7) printf("******* ");
         else if(imp==6) printf("******  ");
         else if(imp==5) printf("*****   ");
         else if(imp==4) printf("****    ");
         else if(imp==3) printf("***     ");
         else if(imp==2) printf("**      ");
         else if(imp==1) printf("*       ");
         else printf("ERROR%2d ",imp);
         printf("%s\n",e[i].s);
      }
      gets(s);
   }
}
