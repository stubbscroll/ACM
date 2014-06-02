#include <stdio.h>
#include <string.h>

char s[1000000];

void prosess() {
   int i,j,n;
   n=strlen(s);
   i=j=0;
   puts(s);
   while(i<n) {
      s[j]=s[i];
      if(s[i]=='(' && s[i+1]==')') {
         if(j>0 && s[j-1]=='*') {
            s[j]='-'; j++;
         }
         s[j]='*';
         i++;
      }
      j++;
      i++;
   }
   s[j]=0;
   i=j=0;
   while(i<n) {
      s[j]=s[i];
      i++, j++;
   }
   puts(s);
}

int match[1000000];
int stack[500000];

typedef long long ll;

typedef struct { ll x,y; ll svarte,hvite;} s_res;

s_res resstack[1000000];
ll tallstack[1000000];
int ressp;
int tallsp;

#define PUSH { tallstack[tallsp++]=left; tallstack[tallsp++]=right; \
  tallstack[tallsp++]=bredde; tallstack[tallsp++]=hoyde; \
  tallstack[tallsp++]=svart;  tallstack[tallsp++]=hvit; \
  tallstack[tallsp++]=i; \
  resstack[ressp++]=res; }

#define PULL {  i=tallstack[--tallsp]; \
  hvit=tallstack[--tallsp]; svart=tallstack[--tallsp]; \
  hoyde=tallstack[--tallsp]; bredde=tallstack[--tallsp]; \
  right=tallstack[--tallsp]; left=tallstack[--tallsp]; \
  res=resstack[--ressp]; }

s_res btr2(int left,int right) {
   ll i,j;
   ll bredde=0,hoyde=0,svart=0,hvit=0;
   s_res temp;
start:
   bredde=0;
   hoyde=0;
   svart=0;
   hvit=0;
   s_res res;
   if(left+1==right) {
      temp.x=1; temp.y=1;
      temp.svarte=1; temp.hvite=0;
      if(ressp==0) return temp;
      goto BTRACK;
   }
   i=left+1;
   bredde=1;
   hoyde=0;
   while(i<right-1) {
      PUSH
      left=i; right=match[i];
      goto start;
BTRACK:
      PULL
      // here temp is the return value from prev
      i=match[i]+1;
      
      if(temp.y+1>hoyde) hoyde=temp.y+1;
      bredde+=temp.x+1;
      hvit+=temp.svarte;
   }
   if(left==0 && right==strlen(s)-1) {
      bredde-=2;
      hoyde--;
   }
   svart=bredde*hoyde-hvit;
   res.x=bredde;
   res.y=hoyde;
   res.svarte=svart;
   res.hvite=hvit;
   if(left==0 && right==strlen(s)-1) 
      return res;

   temp=res;
   goto BTRACK;
}

void process2() {
   int sp=0;
   int i,j,k;
   int n=strlen(s);
   int lev=0;
   int pos;
   s_res res;
   for(i=0;i<n;i++) {
      
      if(s[i]=='(') {
         stack[sp++]=i;
         lev++;
      }
      if(s[i]==')') {
         lev--;
         pos=stack[--sp];
         match[pos]=i;
         match[i]=pos;
      }
   }
   ressp=0;
   tallsp=0;

   res=btr2(0,n-1);
   printf("%I64d\n",res.hvite);
}

int main() {
   int cases;
   int x;
   scanf("%d",&cases);
   while(cases--) {
      s[0]='(';
      scanf("%s",s+1);
      x=strlen(s);
      s[x]=')';
      s[x+1]=0;
      process2();
   }
   return 0;
}
