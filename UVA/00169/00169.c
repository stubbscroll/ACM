#include <stdio.h>
#define MAXW 10000

char m[2000];
int ml;
char s[100];
int f[26];

struct w_s {
   int p; /* position of word */
   int l; /* length of word */
   int end;
   int f[26];
   int equal;
   int overlap;
} w[MAXW];
int n;

int isequal(int i,int j)
{
   int k;

   for(k=0;k<26;k++) if(w[i].f[k]!=w[j].f[k]) return 0;
   return 1;
}

int compw(struct w_s *a,struct w_s *b)
{
   return (a->end>b->end)-(a->end<b->end);
}

int compw2(struct w_s *a,struct w_s *b)
{
   return (a->p>b->p)-(a->p<b->p);
}

int main()
{
   int i,j,k,sl,n2;

   while(1) {
      ml=0;
      do {
         gets(s);
         if(s[0]=='#' && !s[1]) return;
         sl=strlen(s);
         for(i=0;i<sl;i++) if(s[i]>='a' && s[i]<='z') m[ml++]=s[i];
      } while(s[sl-1]=='-');
      m[ml]=0;
      n=0;
      memset(f,0,104);
      for(i=0;i<ml-1;i++) {
         if(i>1 && f[m[i]-'a']==0) {
            for(k=0;k<26;k++) w[n].f[k]=f[k];
            w[n].end=i;
            w[n].p=0; w[n++].l=i;
         }
         f[m[i]-'a']++;
      }
      for(i=1;i<ml-1;i++) {
         memset(f,0,104);
         for(j=i;j<ml;j++) {
            if(m[j]==m[i-1]) break;
            f[m[j]-'a']++;
         }
         k=j-i;
         if(k<2 || k>250) continue;
         w[n].l=k;
         w[n].end=j;
         for(k=0;k<26;k++) w[n].f[k]=f[k];
         w[n++].p=i;
      }
      for(i=0;i<n;i++) w[i].overlap=w[i].equal=0;
      for(i=0;i<n-1;i++)
         for(j=i+1;j<n;j++) {
            if(w[i].l==w[j].l && isequal(i,j)) {
               if(w[i].equal!=2) w[i].equal=1;
               w[j].equal=2;
            }
         }
      n2=0;
      for(i=0;i<n;i++) {
         if(n2!=i && w[i].equal) {
            memcpy(w+n2,w+i,sizeof(w[0]));
         }
         if(w[i].equal) n2++;
      }
      n=n2;
      for(i=0;i<n-1;i++)
         for(j=i+1;j<n;j++)
            if(w[j].p<w[i].p+w[i].l && !isequal(i,j))
               w[i].overlap=w[j].overlap=1;
      for(i=0;i<n-1;i++)
         for(j=i+1;j<n;j++)
            if(w[i].l==w[j].l && isequal(i,j) && (w[i].overlap || w[j].overlap))
               w[i].overlap=w[j].overlap=1;
      qsort(w,n,sizeof(w[0]),compw);
      for(i=0;i<n;i++)
         if(w[i].equal==1 && w[i].overlap) {
            for(j=0;j<w[i].l;j++) printf("%c",m[w[i].p+j]);
            printf("\n");
         }
      printf("*\n");
   }
}
