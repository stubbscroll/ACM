#include <stdio.h>

int v[256];
char s[100],r[3][25];
int nr[3];

int t[256];
char let[7];
int per[7];
int val[7];
int ln;
int tall[10];

int main()
{
   int i,j,k,sols;

   v['I']=1; v['V']=5; v['X']=10; v['L']=50; v['C']=100; v['D']=500; v['M']=1000;
   while(1) {
      gets(s);
      if(s[0]=='#') break;
      sscanf(s,"%[^+]+%[^=]=%s",r[0],r[1],r[2]);
      for(i=0;i<3;i++) {
         nr[i]=0;
         for(j=0;j<strlen(r[i]);j++)
            if(v[r[i][j]]<v[r[i][j+1]])
               nr[i]-=v[r[i][j]];
            else
               nr[i]+=v[r[i][j]];
      }
      if(nr[0]+nr[1]==nr[2]) printf("Correct ");
      else printf("Incorrect ");
      for(i='C';i<='X';i++) t[i]=0;
      for(i=0;i<3;i++)
         for(j=0;j<strlen(r[i]);j++)
            t[r[i][j]]=1;
      ln=0;
      for(i='C';i<='X';i++)
         if(t[i]) {
            let[ln]=i;
            t[i]=ln;
            ln++;
         }
      for(i=0;i<ln;i++) per[i]=i;
      for(i=0;i<ln;i++) val[i]=0;
      for(i=0;i<3;i++) {
         k=i==2 ? -1 : 1;
         for(j=strlen(r[i])-1;j>=0;j--) {
            val[t[r[i][j]]]+=k; k*=10;
         }
      }
      sols=0;
      while(1) {
         j=0;
         for(i=0;i<ln;i++) j+=val[i]*per[i];
         if(j) goto next;
         for(i=0;i<3;i++)
            if(per[t[r[i][0]]]==0) goto next;
         sols++;
         if(sols>1) break;
      next:
         j=ln-1;
      lopp:
         per[j]++;
         for(i=0;i<j-1;i++) if(per[j]==per[i]) goto lopp;
         if(per[j]<10) goto out;
         j--;
         if(j>=0) goto lopp;
      out:
         if(j==-1) break;
         for(i=0;i<10;i++) tall[i]=0;
         for(i=0;i<=j;i++) tall[per[i]]=1;
         k=0;
         for(i=j+1;i<ln;i++) {
            while(tall[k]) k++;
            per[i]=tall[k++];
         }
      }
      if(sols==0) printf("impossible\n");
      else if(sols==1) printf("valid\n");
      else printf("ambiguous\n");
   }
}
