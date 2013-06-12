#include <stdio.h>
#define MAXL 51
#define MAXF 250
#define MAX 1000

char vn[MAX][MAXL];    /* variable name */
char vf[MAX][MAXF];    /* variable formula */
int vp[MAX];           /* start of formula */
int n;                 /* number of variables */
int taken[MAX];
int def;

char s[1000],t[1000],u[1000];

int findname(char *s)
{
   int i;

   for(i=0;i<n;i++) if(!strcmp(vn[i],s)) return i;
   return -1;
}

int createname(char *s)
{
   return n++;
}

int expression(char *s,int *start,int *end);
int eval(char *s);

int factor(char *s,int *start,int *end)
{
   int i,j,k;

   if(s[*start]=='(') {
      (*start)++;
      while(isspace(s[*start])) (*start)++;
      i=expression(s,start,end);
      if(s[*start]==')') (*start)++;
      while(isspace(s[*start])) (*start)++;
      return i;
   } else if(isalpha(s[*start])) {
      j=0;
      while(isalnum(s[*start])) {
         t[j++]=s[(*start)++];
      }
      t[j]=0;
      while(isspace(s[*start])) (*start)++;
      return eval(t);
   } else if(isdigit(s[*start]) || s[*start]=='-') {
      j=0; k=1;
      if(s[*start]=='-') {
         k=-1; (*start)++;
      }
      while(isdigit(s[*start])) j=j*10+s[(*start)++]-'0';
      while(isspace(s[*start])) (*start)++;
      j*=k;
      return j;
   }
   i=1/0;
}

int term(char *s,int *start,int *end)
{
   int i,j;

   i=factor(s,start,end);
mulop:
   if(s[*start]!='*') return i;
   (*start)++;
   while(isspace(s[*start])) (*start)++;
   j=factor(s,start,end);
   i*=j;
   goto mulop;
}

int expression(char *s,int *start,int *end)
{
   int i,j;
   char op;

   i=term(s,start,end);
addop:
   if(s[*start]!='+' && s[*start]!='-') return i;
   op=s[(*start)++];
   while(isspace(s[*start])) (*start)++;
   j=term(s,start,end);
   if(op=='+') i+=j;
   if(op=='-') i-=j;
   goto addop;
}

int eval(char *s)
{
   int i,j,start,end;

   i=findname(s);
   if(i==-1 || taken[i]) {
      def=0;
      return 0;
   }
   taken[i]=1;
   start=vp[i]; end=strlen(vf[i]);
   j=expression(vf[i],&start,&end);
   taken[i]=0;
   return j;
}

int main()
{
   int i,j,sl;

   while(1) {
      if(gets(s)==NULL) break;
      sl=strlen(s);
      i=j=0;
      while(isspace(s[i])) i++;
      while(isalnum(s[i])) t[j++]=s[i++];
      t[j]=0;
      for(i=0;i<sl;i++) if(s[i]==':') break;
      if(i<sl) {
         j=findname(t);
         if(j==-1) j=createname(t);
         strcpy(vn[j],t);
         strcpy(vf[j],s);
         i++;
         if(s[i]=='=') i++;
         while(isspace(s[i])) i++;
         vp[j]=i;
      } else if(!strcmp(t,"RESET")) n=0;
      else {
         sscanf(s,"%s %s",t,u);
         if(!strcmp(t,"PRINT")) {
            def=1;
            i=eval(u);
            if(!def) printf("UNDEF\n");
            else printf("%d\n",i);
         }
      }
   }
}
