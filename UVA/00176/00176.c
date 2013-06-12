#include <stdio.h>
#define H 7500000

char ts[50][5000];
char ta[50][5000];
char es[50][5000];
char ea[50][5000];

int bfs[H];
int bn,br;

char s[100],t[100];
int start,goal;
int starts,goals;

int main()
{
   int i,j,k;
   int sa,snr,pos,moves,spos,hnr,dir;
   int nsa,nsnr,npos,nspos,nhnr;
   int canturn;
   int count;

/*   freopen("i5.txt","r",stdin);*/

   memset(es,0,5000*50);
   memset(ea,0,5000*50);
   while(1) {
      scanf("%s",s);
      if(s[0]=='#') break;
      scanf("%d %d",&i,&j);
      if(i>j) {
         k=i; i=j; j=k;
      }
      k=strtol(s+1,NULL,10);
      if(s[0]=='A') for(;i<=j+1;i++) ea[k][i]=2;
      else for(;i<=j+1;i++) es[k][i]=2;
   }
   while(scanf("%s %d %s %d",s,&starts,t,&goals)==4) {
      if(!strcmp(s,t) && starts==goals) {
         printf("0\n"); continue;
      }
      start=strtol(s+1,NULL,10);
      goal=strtol(t+1,NULL,10);
      memcpy(ts,es,5000*50);
      memcpy(ta,ea,5000*50);
      br=bn=0;
      bfs[bn++]=s[0];   /* are we in street or avenue */
      bfs[bn++]=start;  /* street/avenue no. */
      bfs[bn++]=starts; /* house no. */
      bfs[bn++]=-1;      /* number of moves */
      count=0;
      while(br<bn) {
/*         if(count==938)
            printf("tellare");*/
         sa=bfs[br++]; snr=bfs[br++]; pos=bfs[br++]; moves=bfs[br++]+1;
/*         if(ts[49][4798]==1 && count<1000000) {
            printf("%d\n",count);
            count=1000000;
         } count++;*/
/*         printf("%d: %c%d %d\n",moves,sa,snr,pos);*/
/*         if(sa=='S' && snr==49 && pos==4798) {
            printf("dar");
         }*/
/*         if(sa=='S' && snr==49 && pos>4797) printf("%c%d %d\n",sa,snr,pos);*/
         spos=pos%100; hnr=pos/100;
         if(spos==0 || spos==99) {
            /* intersection */
            canturn=0;
            nsnr=hnr;
            if(spos==99) nsnr++;
            if(sa=='A') nsa='S';
            else nsa='A';
            npos=snr*100+1;
            if(((nsa=='A' && ta[nsnr][npos]!=2) || (nsa=='S' && ts[nsnr][npos]!=2)) && npos<4900) canturn=1;
            if(((nsa=='A' && !ta[nsnr][npos]) || (nsa=='S' && !ts[nsnr][npos])) && npos<4900) {
               if(nsa=='A') ta[nsnr][npos]=1;
               else ts[nsnr][npos]=1;
               if(nsa==t[0] && nsnr==goal && npos==goal) goto won;
               bfs[bn++]=nsa; bfs[bn++]=nsnr; bfs[bn++]=npos; bfs[bn++]=moves;
            }
            npos-=3;
            if(((nsa=='A' && ta[nsnr][npos]!=2) || (nsa=='S' && ts[nsnr][npos]!=2)) && npos>=0) canturn=1;
            if(((nsa=='A' && !ta[nsnr][npos]) || (nsa=='S' && !ts[nsnr][npos])) && npos>=0) {
               if(nsa=='A') ta[nsnr][npos]=1;
               else ts[nsnr][npos]=1;
               if(nsa==t[0] && nsnr==goal && npos==goal) goto won;
               bfs[bn++]=nsa; bfs[bn++]=nsnr; bfs[bn++]=npos; bfs[bn++]=moves;
            }
            /* try forward */
            if(spos&1) dir=2;
            else dir=-2;
            npos=pos+dir; nsnr=snr;
            if(canturn && (npos<0 || npos>=4900)) continue;
            if(!canturn && (npos<0 || npos>=4900)) npos=pos^1;
            if(sa=='A' && ta[nsnr][npos]==1) continue;
            else if(sa=='S' && ts[nsnr][npos]==1) continue;
            /* check for u-turn */
            if(sa=='A' && ta[nsnr][npos]==2) {
               if(canturn) continue;
               npos=pos^1;
               if(ta[nsnr][npos]==1) continue;
            } else if(sa=='S' && ts[nsnr][npos]==2) {
               if(canturn) continue;
               npos=pos^1;
               if(ts[nsnr][npos]==1) continue;
            }
            if(sa=='A') ta[nsnr][npos]=1;
            else ts[nsnr][npos]=1;
            if(sa==t[0] && nsnr==goal && npos==goals) goto won;
            bfs[bn++]=sa; bfs[bn++]=nsnr; bfs[bn++]=npos; bfs[bn++]=moves;
         } else {
            /* no intersection */
            if(spos&1) dir=2;
            else dir=-2;
            npos=pos+dir; nsnr=snr;
            if(sa=='A' && ta[nsnr][npos]==1) continue;
            else if(sa=='S' && ts[nsnr][npos]==1) continue;
            /* check for u-turn */
            if(sa=='A' && ta[nsnr][npos]==2) {
               npos=pos^1;
               if(ta[nsnr][npos]==1) continue;
            } else if(sa=='S' && ts[nsnr][npos]==2) {
               npos=pos^1;
               if(ts[nsnr][npos]==1) continue;
            }
            if(sa=='A') ta[nsnr][npos]=1;
            else ts[nsnr][npos]=1;
            if(sa==t[0] && nsnr==goal && npos==goals) goto won;
            bfs[bn++]=sa; bfs[bn++]=nsnr; bfs[bn++]=npos; bfs[bn++]=moves;
         }
      }
      printf("bleah, no win ");
   won:
      printf("%d\n",moves);
   }
}
