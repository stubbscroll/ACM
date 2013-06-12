#include <stdio.h>
#define MAXF 10000
#define MAXFL 500
#define MAXX 18279
#define MAXY 1000
#define MAXS 5000000

char t[MAXS]; /* 0:value, 1=formula */
int  r[MAXS];
char f[MAXF][MAXFL];
int  fn;
int  x,y,xy;

char s[100000];

int eval(char *fn)
{
   int l,i,p,num,num2,mul,val;

   l=strlen(fn);
   p=1;
   val=0;
   while(fn[p]) {
      num=0;
      while(isalpha(fn[p])) num=(num)*26+(fn[p++]-'@');
      num--;
/*      printf("(%d)",num);*/
      num2=0;
      while(isdigit(fn[p])) num2=num2*10+(fn[p++]-'0');
      i=num+(num2-1)*x;
      if(t[i]==0) val+=r[i];
      else {
         t[i]=0;
         r[i]=eval(f[r[i]]);
         val+=r[i];
      }
      if(fn[p]=='+') p++;
   }
   return val;
}

int main()
{
   int n,i,j,k,l;

   scanf("%d",&n);
   while(n--) {
      scanf("%d %d",&x,&y);
      if(x*y>MAXS) while(1) { s[i]=12; i+=123123; }
      fn=0;
      for(j=0;j<y;j++)
         for(i=0;i<x;i++) {
            scanf("%s",s);
            if((l=strlen(s))>=MAXFL) while(1) printf("error");
            if(s[0]=='=') goto form;
            r[i+j*x]=strtol(s,NULL,10);
            t[i+j*x]=0;
            continue;
         form:
            if(fn==MAXF) i=1/0;
            t[i+j*x]=1;
            r[i+j*x]=fn;
            strcpy(f[fn++],s);
         }
      xy=x*y;
      for(i=j=0;i<xy;i++) {
         if(t[i]==0) printf("%d",r[i]);
         else {
            t[i]=0;
            r[i]=eval(f[r[i]]);
            printf("%d",r[i]);
         }
         j++;
         if(j<x) printf(" ");
         if(j==x) {
            printf("\n");
            j=0;
         }
      }
   }
}
