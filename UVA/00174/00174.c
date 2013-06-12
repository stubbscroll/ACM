#include <stdio.h>
#define TRADE 1
#define CHEAT 2
#define EQUAL 1
#define DIFF 2
#define AND 1
#define OR 2

char s[1000],pr[10][10000];
int prn=0;
int p;
int score[10];

int last[2][12];
int curplr;
int curgame;
int curprg;

int match(char *r)
{
   int l;

   while(isspace(pr[curprg][p])) p++;
   l=strlen(r);
   if(!strncmp(pr[curprg]+p,r,l)) {
      p+=l;
      return 1;
   }
   return 0;
}

int statement();

int command()
{
   if(match("TRADE")) return TRADE;
   else if(match("CHEAT")) return CHEAT;
}

int memory()
{
   int my;
   int num;

   if(match("MY")) my=10;
   else if(match("YOUR")) my=20;
   match("LAST");
   if(match("1")) return my+1;
   else if(match("2")) return my+2;
   else return 1/0;
}

int op()
{
   if(match("AND")) return AND;
   else if(match("OR")) return OR;
   else return -1;
}

int cond()
{
   int mem,eq,cmp,num,plr;

   mem=memory();
   if(match("=")) eq=EQUAL;
   else if(match("#")) eq=DIFF;
   if(match("NULL")) cmp=-1;
   else cmp=command();
   num=mem%10;
   mem/=10;
   if(mem==1 && curplr==0) plr=0;
   else if(mem==1 && curplr==1) plr=1;
   else if(mem==2 && curplr==0) plr=1;
   else if(mem==2 && curplr==1) plr=0;
   if(eq==EQUAL) return last[plr][curgame-num]==cmp;
   else return last[plr][curgame-num]!=cmp;
}

int res[1000];
int ope[1000];
int resn;

int condition()
{
   int oper,i;

   resn=0;
   res[resn++]=cond();
again:
   oper=op();
   if(oper==AND) ope[resn-1]=AND;
   else if(oper==OR) ope[resn-1]=OR;
   if(oper==-1) {
      if(resn==1) return res[0];
      /* forward */
/*      for(i=0;i<=resn-2;i++) {
         if(ope[i]==AND) res[i+1]&=res[i];
         else if(ope[i]==OR) res[i+1]|=res[i];      
      }
      return res[i];*/
      /* backwards */
      for(i=resn-2;i>=0;i--) {
         if(ope[i]==AND) res[i]&=res[i+1];
         else if(ope[i]==OR) res[i]|=res[i+1];
      }
      return res[0];
   }
   res[resn++]=cond();
   goto again;
}

int ifstat()
{
   int i;

   i=condition();
   match("THEN");
   if(i) {
      i=statement();
      match("ELSE");
      statement();
      return i;
   } else {
      statement();
      match("ELSE");
      return statement();
   }
}

int statement()
{
   if(match("IF")) {
      return ifstat();
   } else
      return command();
}

int program()
{
   int i;

   p=0;
   i=statement();
   if(s[p]=='.') p++;
   return i;
}

int main()
{
   int i,j;
/*   freopen("i9.txt","r",stdin);*/

   while(1) {
      pr[prn][0]=0;
      while(gets(s)) {
         if(s[0]=='#') goto begin;
         strcat(pr[prn],s);
         i=strlen(s)-1;
         while(isspace(s[i]) && i) i--;
         if(s[i]=='.') break;
      }
      prn++;
   }
begin:
   for(i=0;i<prn;i++) score[i]=0;
   for(i=0;i<prn-1;i++) {
      for(j=i+1;j<prn;j++) {
         last[0][0]=last[0][1]=last[1][1]=last[1][0]=-1;
         for(curgame=2;curgame<12;curgame++) {
            curplr=0; curprg=i;
            last[0][curgame]=program();
            curplr++; curprg=j;
            last[1][curgame]=program();
            if(last[0][curgame]==TRADE && last[1][curgame]==TRADE) {
               score[i]++; score[j]++;
            } else if(last[0][curgame]==CHEAT && last[1][curgame]==CHEAT) {
               score[i]--; score[j]--;
            } else if(last[0][curgame]==TRADE && last[1][curgame]==CHEAT) {
               score[i]-=2; score[j]+=2;
            } else if(last[0][curgame]==CHEAT && last[1][curgame]==TRADE) {
               score[i]+=2; score[j]-=2;
            }
         }
      }
   }
   for(i=0;i<prn;i++) printf("%3d\n",score[i]);
}
