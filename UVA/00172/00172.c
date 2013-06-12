#include <stdio.h>

int val[26];
int oval[26];
int nv;

char t[100][100];
int nt;

char s[200];

int getval(int p)
{
   if(isalpha(t[p][0])) return val[t[p][0]-'A'];
   else return strtol(t[p],NULL,10);
}

int evalat(int p)
{
   int i;

   if(t[p+1][0]=='=') {
      i=t[p][0]-'A';
      return val[i]=getval(p+2);
   } else if(t[p+1][0]=='*') {
      return getval(p)*getval(p+2);
   } else if(t[p+1][0]=='/') {
      return getval(p)/getval(p+2);
   } else if(t[p+1][0]=='+') {
      return getval(p)+getval(p+2);
   } else if(t[p+1][0]=='-') {
      return getval(p)-getval(p+2);
   }
}

int main()
{
   int i,j,sl,from,to,first,start,end;

   for(i=0;i<26;i++) val[i]=0;
   while(1) {
      gets(s);
      if(s[0]=='#') break;
      sl=strlen(s);
      nt=0; j=0;
      for(i=0;i<=sl;i++) {
         if(isalnum(s[i]) || s[i]=='_') t[nt][j++]=s[i];
         else if(s[i]=='*' || s[i]=='/' || s[i]=='+' || s[i]=='-' ||
            s[i]=='=' || s[i]=='(' || s[i]==')') {
            if(j) {
               t[nt++][j]=0; j=0;
            }
            t[nt][j]=s[i]; t[nt++][j+1]=0;
         } else if(j) {
            t[nt++][j]=0; j=0;
         }
      }
      for(i=0;i<26;i++) oval[i]=val[i];
      for(i=0;i<nt;i++) if(t[i][0]=='_') t[i][0]='-';
      while(nt>1) {
         i=-1;
         for(j=0;j<nt;j++) {
            if(t[j][0]=='(') i=j;
            if(t[j][0]==')') {
               start=i;
               end=j;
               if(end-start>4) goto beguin;
               if(end-start==2) {
                  strcpy(t[start],t[start+1]);
                  from=start+3; to=start+1;
                  goto retract;               
               }
               if(end-start==4) {
                  j=evalat(start+1);
                  sprintf(t[start],"%d",j);
                  from=start+5; to=start+1;
                  goto retract;
               
               }
            }
         }
         end=nt;
         start=-1;
         for(i=nt-1;i>=0;i--) {
            if(t[i][0]==')' || t[i][0]=='+' || (t[i][0]=='-' && !t[i][1])
               || t[i][0]=='*' || t[i][0]=='/') {
               start=i;
            }
            if(t[i][0]=='=') {
               if(start!=-1) break;
               j=evalat(i-1);
               sprintf(t[i-1],"%d",j);
               from=i+2; to=i;
               goto retract;
            }
         }
      beguin:
         for(i=end-1;i>=start;i--)
            if(t[i][0]=='*' || t[i][0]=='/') {
               j=evalat(i-1);
               sprintf(t[i-1],"%d",j);
               from=i+2; to=i;
               goto retract;
            }
         for(i=end-1;i>=start;i--)
            if(t[i][0]=='+' || (t[i][0]=='-' && !t[i][1])) {
               j=evalat(i-1);
               sprintf(t[i-1],"%d",j);
               from=i+2; to=i;
               goto retract;
            }
         for(i=end-1;i>=start;i--)
            if(t[i][0]=='=') {
               j=evalat(i-1);
               sprintf(t[i-1],"%d",j);
               from=i+2; to=i;
               goto retract;
            }
      retract:
         for(;from<nt;from++)
            strcpy(t[to++],t[from]);
         nt=to;
/*         for(i=0;i<nt;i++) printf("%s ",t[i]);
         printf("\n");*/
      }
      first=1;
      for(i=0;i<26;i++) {
         if(val[i]!=oval[i]) {
            if(!first) printf(", ");
            else first=0;
            printf("%c = %d",i+'A',val[i]);
         }
      }
      if(first==1) printf("No Change\n");
      else printf("\n");
   }
}
