#include <stdio.h>

const int dirx[8]={0,1,1,1,0,-1,-1,-1};
const int diry[8]={-1,-1,0,1,1,1,0,-1};
const char dirc[8][3]={"N","NE","E","SE","S","SW","W","NW"};
const int and[8]={1,2,4,8,16,32,64,128};

int legal[101][101];
int bol[101][101];

char s[1000],t[100][100];
int tn,nt;

int posx,posy,dir;

void move(int n)
{
   posx+=dirx[dir];
   posy+=diry[dir];
}

void backup(int n)
{
   posx-=dirx[dir];
   posy-=diry[dir];
}

/* check if direction faced is legal */
int facelegal(int posx,int posy,int dir)
{
   return (legal[posx+50][posy+50]&and[dir])>0;
}

int isbol(int posx,int posy,int dir)
{
   return (bol[posx+50][posy+50]&and[dir])>0;
}

int main()
{
   int i,j,num,sl,cdir,ndir,bdir,x,y;
/*   freopen("i5.txt","r",stdin);*/

   memset(legal,0,101*101);
   memset(bol,0,101*101);
   /* set north */
   for(i=-50;i<=50;i++)
      for(j=-49;j<=50;j++)
         legal[i+50][j+50]|=and[0];
   /* set south */
   for(i=-50;i<=50;i++)
      for(j=-50;j<=49;j++)
         legal[i+50][j+50]|=and[4];
   /* set east */
   for(i=-50;i<=49;i++)
      for(j=-50;j<=50;j++)
         legal[i+50][j+50]|=and[2];
   /* set west */
   for(i=-49;i<=50;i++)
      for(j=-50;j<=50;j++)
         legal[i+50][j+50]|=and[6];
   /* define boulevards */
   for(i=0;i<50;i++) {
      j=50-i;
      legal[i][i]|=and[3];
      legal[i+1][i+1]|=and[7];
      legal[i+50][i+50]|=and[3];
      legal[i+51][i+51]|=and[7];
      legal[i+50][j]|=and[1];
      legal[i+51][j-1]|=and[5];
      legal[i][j+50]|=and[1];
      legal[i+1][j+49]|=and[5];
      bol[i][i]|=and[3];
      bol[i+1][i+1]|=and[7];
      bol[i+50][i+50]|=and[3];
      bol[i+51][i+51]|=and[7];
      bol[i+50][j]|=and[1];
      bol[i+51][j-1]|=and[5];
      bol[i][j+50]|=and[1];
      bol[i+1][j+49]|=and[5];
      legal[i][i+50]|=and[3];
      legal[i+1][i+51]|=and[7];
      legal[i+50][i]|=and[3];
      legal[i+51][i+1]|=and[7];
      legal[i][j]|=and[1];
      legal[i+1][j-1]|=and[5];
      legal[i+50][j+50]|=and[1];
      legal[i+51][j+49]|=and[5];
   }
   for(i=-50;i<=49;i++) {
      bol[i+50][0]|=and[2];
      bol[i+50][50]|=and[2];
      bol[i+50][100]|=and[2];
   }
   for(i=-49;i<=50;i++) {
      bol[i+50][0]|=and[6];
      bol[i+50][50]|=and[6];
      bol[i+50][100]|=and[6];   
   }
   for(i=-50;i<=49;i++) {
      bol[0][i+50]|=and[4];
      bol[50][i+50]|=and[4];
      bol[100][i+50]|=and[4];
   }
   for(i=-49;i<=50;i++) {
      bol[0][i+50]|=and[0];
      bol[50][i+50]|=and[0];
      bol[100][i+50]|=and[0];   
   }
/*   for(i=0;i<101;i++) {
      for(j=0;j<101;j++) printf("%3d",legal[i][j]);
      printf("\n");
   }
   printf("\n");
   for(i=0;i<101;i++) {
      for(j=0;j<101;j++) printf("%3d",bol[i][j]);
      printf("\n");
   }
   return;*/
   while(1) {
      gets(s);
      if(!strcmp(s,"END")) break;
      if(sscanf(s,"%s %s %s",t[0],t[1],t[2])<3) continue;
      if(!strcmp(t[2],"N")) dir=0;
      else if(!strcmp(t[2],"NE")) dir=1;
      else if(!strcmp(t[2],"E")) dir=2;
      else if(!strcmp(t[2],"SE")) dir=3;
      else if(!strcmp(t[2],"S")) dir=4;
      else if(!strcmp(t[2],"SW")) dir=5;
      else if(!strcmp(t[2],"W")) dir=6;
      else if(!strcmp(t[2],"NW")) dir=7;
      for(i=0;i<2;i++) {
         j=1; num=0;
         while(isdigit(t[i][j])) num=num*10+t[i][j++]-'0';
         if(t[i][j]=='N' || t[i][j]=='W') num*=-1;
         if(t[i][0]=='A') posx=num;
         else if(t[i][0]=='S') posy=num;
      }
      while(1) {
         gets(s);
/*         printf("->%s\n",s);*/
         tn=nt=0; sl=strlen(s);
         for(i=0;i<=sl;i++) {
            if(isalnum(s[i])) {
               t[tn][nt++]=s[i];
            } else {
               if(nt>0) t[tn++][nt]=0; nt=0;
            }
         }
         nt=0;
         if(nt<tn && !strcmp(t[nt],"TURN")) {
            nt++; cdir=2;
            if(nt<tn && !strcmp(t[nt],"SHARP")) {
               cdir=3; nt++;
            } else if(nt<tn && !strcmp(t[nt],"HALF")) {
               cdir=1; nt++;
            }
            if(nt<tn && !strcmp(t[nt],"LEFT")) {
               cdir*=-1; nt++;
            } else if(nt<tn && !strcmp(t[nt],"RIGHT"))
               nt++;
            else continue;
            if(nt<tn) continue;
            ndir=(dir+cdir+8)%8;
            x=posx; y=posy; bdir=dir;
            move(1);
            if(!facelegal(posx,posy,ndir)) {
               backup(1); continue;
            }
            if((posx==0 || abs(posx)==50) && (posy==0 || abs(posy)==50)) {
               dir=ndir; continue;
            }
            if(isbol(x,y,bdir)==1 && abs(posx)==25 && abs(posy)==25 && cdir==-2) {
               backup(1); continue;
            }
            if(isbol(posx,posy,ndir)==1 && abs(posx)==25 && abs(posy)==25 && cdir==-2) {
               backup(1); continue;
            }
            if(isbol(posx,posy,ndir)!=isbol(x,y,bdir)) {
               if(cdir!=-2 && cdir!=-3) {
                  backup(1); continue;
               }
            }
            dir=ndir;
         } else if(nt<tn && !strcmp(t[nt],"GO")) {
            nt++;
            if(nt<tn && !strcmp(t[nt],"STRAIGHT")) nt++;
            if(nt<tn) sscanf(t[nt++],"%d",&j);
            if(nt<tn) continue;
            x=posx; y=posy;
            for(i=0;i<j;i++) {
               move(j);
               if(!facelegal(posx,posy,dir)) {
                  posx=x; posy=y;
                  break;
               }
            }
         } else if(nt<tn && !strcmp(t[nt],"STOP")) break;
/*         printf("    -> %d %d %s\n",posx,posy,dirc[dir]);*/
      }
      if(isbol(posx,posy,dir)==1) printf("Illegal stopping place\n");
      else {
         printf("A%d",abs(posx));
         if(posx<0) putchar('W');
         else if(posx>=0) putchar('E');
         printf(" S%d",abs(posy));
         if(posy<=0) putchar('N');
         else if(posy>0) putchar('S');
         printf(" %s\n",dirc[dir]);
      }
   }
}
