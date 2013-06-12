#include <stdio.h>
#define OCOST 0
#define OTIME 1

struct f_s {
   int from,to;
   int f1,f2,t1,t2;
   int f,t;
   int price;
   char f3,t3;
   char fs[20],ts[20];
   char p[20];
} fl[60];
int fn;

char c[25][100];        /* cities */
int nc;
int taken[25];

char s[1000],t[1000],u[1000],v[1000];

int optimize;
int besttime;
int bestprice;
int bestlen;
int bestpath[100];
int path[100];

void dfs(int v,int end,int p)
{
   int i,price,len,days;

   if(v==end) {
      price=len=days=0;
      for(i=0;i<p;i++) {
         price+=fl[path[i]].price;
         if(len>fl[path[i]].f) {
            days++; len=fl[path[i]].t;
         } else len=fl[path[i]].t;
         if(fl[path[i]].t<fl[path[i]].f) days++;
      }
      len+=days*1440;
      len-=fl[path[0]].f;
      if((optimize==OTIME && len<besttime || (len==besttime && price<bestprice)) ||
         (optimize==OCOST && price<bestprice || (price==bestprice && len<bestlen))) {
         bestprice=price; bestlen=p; besttime=len;
         for(i=0;i<p;i++) bestpath[i]=path[i];
      }
      return;
   }
   taken[v]=1;
   for(i=0;i<fn;i++) {
      if(fl[i].from==v && !taken[fl[i].to]) {
         path[p]=i;
         dfs(fl[i].to,end,p+1);
      }
   }
   taken[v]=0;
}

int findcity(char *s)
{
   int i;

   for(i=0;i<nc;i++) if(!strcmp(c[i],s)) return i;
   strcpy(c[nc],s);
   return nc++;
}

int hours(char a)
{
   if(a=='A') return 0;
   else return 720;
}

int main()
{
   int tr,i,j,k,l,m,n,tl,ul,vl,first=1,f2=1;
   char a,b;

   while(1) {
      if(gets(s)==NULL) break;
      sscanf(s,"%s %d",t,&tr);
      nc=0; fn=0;
      while(1) {
         if(gets(s)==NULL) return;
         if(s[0]=='#') break;
         sscanf(s,"%s %s %d:%d%c %d:%d%c %d.%d",t,u,&i,&j,&a,&k,&l,&b,&m,&n);
         tl=strlen(t); ul=strlen(u);
         t[0]=toupper(t[0]); u[0]=toupper(u[0]);          
         sprintf(fl[fn].fs,"%d:%02d%c",i,j,a);
         sprintf(fl[fn].ts,"%d:%02d%c",k,l,b);
         sprintf(fl[fn].p,"$%d.%02d",m,n);
         fl[fn].f1=i; fl[fn].f2=j; fl[fn].f3=a;
         fl[fn].t1=j; fl[fn].t2=k; fl[fn].t3=b;
         fl[fn].f=i*60+j+hours(a);
         fl[fn].t=k*60+l+hours(b);
         for(i=1;i<tl;i++) t[i]=tolower(t[i]);
         for(i=1;i<ul;i++) u[i]=tolower(u[i]);
         fl[fn].from=findcity(t);
         fl[fn].to=findcity(u);
         fl[fn++].price=m*100+n;
      }
      if(!first) printf("\n\n");
      else first=0;
      printf("Requests and optimal routes for travel %d\n",tr);
      printf("------------------------------------------\n\n");
      f2=1;
      while(1) {
         if(gets(s)==NULL) return;
         if(s[0]=='#') break;
         if(!f2) putchar('\n');
         else f2=0;
         for(i=0;i<25;i++) taken[i]=0;
         sscanf(s,"%s %s %s",t,u,v);
         tl=strlen(t); ul=strlen(u); vl=strlen(v);
         t[0]=toupper(t[0]); u[0]=toupper(u[0]); v[0]=toupper(v[0]);
         for(i=1;i<tl;i++) t[i]=tolower(t[i]);
         for(i=1;i<ul;i++) u[i]=tolower(u[i]);
         for(i=1;i<vl;i++) v[i]=tolower(v[i]);
         i=findcity(t);
         j=findcity(u);
         if(!strcmp(v,"Cost")) optimize=OCOST;
         else optimize=OTIME;
         besttime=1e9;
         bestprice=1e9;
         if(i==j) {
            printf("You are already in %s.\n",c[i]);
            continue;
         }
         dfs(i,j,0);
         if(bestprice==1e9) {
            printf("There is no route from %s to %s.\n",c[i],c[j]);
            continue;
         }
         printf("From: %-21sTo: %-21sOptimize: %s\n",c[i],c[j],v);
         printf("==================================================================\n");
         printf("From                To                     Leave   Arrive     Cost\n");
         printf("==================================================================\n");
         for(i=0;i<bestlen;i++) {
            printf("%-20s%-23s%-8s%-7s%8s\n",c[fl[bestpath[i]].from],
               c[fl[bestpath[i]].to],fl[bestpath[i]].fs,fl[bestpath[i]].ts,
               fl[bestpath[i]].p);
         }
         printf("                                           -----------------------\n");
         strcpy(s,"");
         if(besttime>=1440) {
            sprintf(s,"%d day",besttime/1440);
            if(besttime>=2880) strcat(s,"s");
            strcat(s," ");
         }
         sprintf(t,"%d:%02d",besttime/60%24,besttime%60);
         strcat(s,t);
         sprintf(t,"$%d.%02d",bestprice/100,bestprice%100);
         printf("                                     %20s%9s\n",s,t);
      }
   }
}
