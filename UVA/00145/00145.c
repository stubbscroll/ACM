#include <stdio.h>

int rates[5][3]={{10,6,2},{25,15,5},{53,33,13},{87,47,17},{144,80,30}};

int check(int t1,int t2,int b1,int b2)
{
   if(t2<=b1 || t1>b2) return 0;
   if(t1<b1) t1=b1;
   if(t2>b2) t2=b2;
   return t2-t1;
}

int main()
{
   char s[200];

   char cs,num[10];
   int dr,er,nr,tot;
   int t1,m1,t2,m2,time1,time2,i;

   do {
      gets(s);
      if(s[0]=='#') break;
      sscanf(s,"%c %s %d %d %d %d",&cs,num,&t1,&m1,&t2,&m2);
      time1=t1*60+m1;
      time2=t2*60+m2;
      if(time2<=time1) time2+=1440;
      nr=check(time1,time2,0,480);
      dr=check(time1,time2,480,1080);
      er=check(time1,time2,1080,1320);
      nr+=check(time1,time2,1320,1920);
      dr+=check(time1,time2,1920,2520);
      nr+=check(time1,time2,2520,2880);
      i=cs-'A';
      tot=dr*rates[i][0]+er*rates[i][1]+nr*rates[i][2];
      printf("  %s %5d %5d %5d  %c %4d.%02d\n",num,dr,er,nr,cs,tot/100,tot%100);
   } while(1);
}
