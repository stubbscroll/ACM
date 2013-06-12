#include <stdio.h>

char t[100];
char s[100],v[100];
int w,sl,vl;

int gettoken()
{
   while(isspace(s[w])) w++;
   vl=0;
   if(s[w]=='"') {
      v[vl++]=s[w++];
      while(s[w] && s[w]!='"') v[vl++]=s[w++];
      if(s[w]=='"') v[vl++]=s[w++];
      else return 0;
      v[vl]=0; return 1;
   } else if(isdigit(s[w])) {
      while(isdigit(s[w])) v[vl++]=s[w++];
      v[vl]=0; return 1;
   } else if(isalpha(s[w])) {
      while(isalpha(s[w])) v[vl++]=s[w++];
      v[vl]=0; return 1;
   } else {
      v[vl++]=s[w++];
      v[vl]=0; return 1;
   }
}

int isualpha(char c)
{
   return c>='A' && c<='Z';
}

int match(char *u)
{
   int i,w2=w;

   if(!gettoken()) return 0;
   if(!strcmp(v,u)) return 1;
   w=w2; return 0;
}

int cas()
{
   if(match("CAS")) {
      strcat(t,"CAS ");
      return 1;
   }
   if(!match("CHANGE")) return 0;
   if(!match("AVERAGE")) return 0;
   if(!match("SPEED")) return 0;
   strcat(t,"CHANGE AVERAGE SPEED ");
   return 1;
}

int record()
{
   if(!match("RECORD")) return 0;
   if(!match("TIME")) return 0;
   strcat(t,"RECORD TIME ");
   return 1;
}

int change()
{
   int w2=w;
   char bt[100];

   strcpy(bt,t);
   if(!cas()) {
      w=w2; strcpy(t,bt);
      return 0;
   }
   if(!match("TO")) {
      w=w2; strcpy(t,bt);
      return 0;
   }
   gettoken();
   if(!isdigit(v[0])) {
      w=w2; strcpy(t,bt);
      return 0;
   }
   strcat(t,"TO ");
   strcat(t,v);
   if(!match("KMH")) {
      w=w2; strcpy(t,bt);
      return 0;
   }
   strcat(t," KMH ");
   return 1;
}

int timekeeping()
{
   int w2=w;
   char bt[100];

   strcpy(bt,t);
   if(record()) return 1;
   w=w2; strcpy(bt,t);
   if(change()) return 1;
   w2=w; strcpy(t,bt);
   return 0;
}

int when()
{
   if(match("FIRST")) {
      strcat(t,"FIRST "); return 1;
   } else if(match("SECOND")) {
      strcat(t,"SECOND "); return 1;
   } else if(match("THIRD")) {
      strcat(t,"THIRD "); return 1;
   }
   return 0;
}

int how()
{
   if(match("GO")) {
      strcat(t,"GO ");
      when();
      return 1;
   } else if(match("KEEP")) {
      strcat(t,"KEEP ");
      return 1;
   }
   return 0;
}

int sign()
{
   int i;
   gettoken();
   if(v[0]=='"' && v[vl-1]=='"') {
      i=1;
      while(i<vl) {
         if(isualpha(v[i]) || v[i]=='.') while(isualpha(v[i]) || v[i]=='.') i++;
         else return 0;
         if(isspace(v[i])) {
            while(isspace(v[i])) i++;
            if(v[i]=='"') return 0;
         } else if(v[i]=='"') break;
      }
      strcat(t,v);
      strcat(t," ");
      return 1;
   }
   return 0;
}

int where()
{
   if(match("AT")) {
      strcat(t,"AT ");
      return sign();
   }
   return 0;
}

int direction()
{
   if(match("RIGHT")) {
      strcat(t,"RIGHT ");
      return 1;
   } else if(match("LEFT")) {
      strcat(t,"LEFT ");
      return 1;
   }
   return 0;
}

int directional()
{
   int w2=w;
   char bt[100];

   strcpy(bt,t);
   if(!how()) {
      w=w2; strcpy(t,bt);
      return 0;
   }
   w2=w; 
   strcpy(bt,t);
   if(!direction()) {
      w=w2; strcpy(t,bt);
      return 0;
   }
   w2=w; strcpy(bt,t);
   if(!where()) {
      strcpy(t,bt);
      w=w2;
   }
   return 1;
}

int navigational()
{
   int w2=w;
   char bt[100];

   strcpy(bt,t);
again:
   if(!directional()) return 0;
   w2=w;
   strcpy(bt,t);
   if(!match("AND")) return 1;
   if(!match("THEN")) {
      w=w2; strcpy(t,bt);
      return 1;
   }
   strcat(t,"AND THEN ");
   goto again;
}

int instruction()
{
   int w2=w;
   char bt[100];

   strcpy(bt,t);
   if(navigational()) {
      if(!match("AND")) return !s[w];
      strcat(t,"AND ");
      timekeeping();
      return !s[w];
   }
   w=w2;
   strcpy(t,bt);
   timekeeping();
   return !s[w];
}

int main()
{
   int line=1;

   while(1) {
      gets(s);
      if(s[0]=='#' && !s[1]) break;
      sl=strlen(s); strcpy(t,""); w=0;
      if(sl==0) printf("%3d. Trap!\n",line++);
      else {
         if(!instruction()) printf("%3d. Trap!\n",line++);
         else {
            t[strlen(t)-1]=0;
            printf("%3d. %s\n",line++,t);
         }
      }
   }
}
