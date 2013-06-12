#include <stdio.h>

const int p[10]={1,2,4,5,6,7,8,9,10};

char s[100];
int n[10];
int d;
int r[10];

int main()
{
   int i,j,last,first=1;

   while(1) {
      scanf("%s %d",s,&d);
      if(!strcmp(s,"0000000000") && d==0) break;
      j=0;
      for(i=0;i<10;i++) r[i]=0;
      for(i=0;i<10;i++) {
         n[j++]=s[i]-'0';
         if(i==1) i++;
      }
      last=-1;
      for(i=0;i<9;i++) {
         if(d==3) {
            r[s[2]-'0']*=10;
            r[s[2]-'0']+=n[i];
         } else if(p[i]==d) {
            for(j=0;j<n[i];j++) r[j]++;
            last=n[i];
         } else if(last!=-1) {
            for(j=0;j<10;j++) r[j]*=10;
            r[last]+=n[i];
         } else {
            for(j=0;j<10;j++) r[j]*=10;
            for(j=0;j<10;j++) r[j]+=n[i];
         }
      }
      if(s[2]=='0' && d!=3) r[0]--;
      else if(s[2]=='0' && d==3) r[s[2]-'0']--;
      if(!first) printf("\n");
      else first=0;
      for(i=0;i<10;i++) printf("%11d\n",r[i]);
   }
}
