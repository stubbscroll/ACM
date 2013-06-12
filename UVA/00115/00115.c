#include <stdio.h>
#define MAXNAME 32
#define MAXTREE 310

struct tree_s {
   char name[MAXNAME];
   int parent;     /* -1 = no parent */
} tree[MAXTREE];
int n;             /* number of nodes */

int trav[MAXTREE];     /* marked during traversal with number of generations away */

char s[40],t[40];

int findname(char *s)
{
   int i;

   for(i=0;i<n;i++)
      if(strcmp(s,tree[i].name)==0) return i;
   return -1;
}

int createname(char *s)
{
   strcpy(tree[n].name,s);
   tree[n].parent=-1;
   return n++;
}

int findtop(int i)
{
   while(tree[i].parent!=-1)
      i=tree[i].parent;
   return i;
}

int main()
{
   int ch,pa;
   int p[2];      /* persons for which to check relation */
   int top[2];    /* top ancestor for persons */
   int h[2];      /* distance from top ancestor to persons */
   int i,j,k;

   n=0;
   while(1) {
      scanf("%s %s",s,t);
      if(strcmp(s,"no.child")==0) break;
      ch=findname(s); pa=findname(t);
      if(ch==-1) ch=createname(s);
      if(pa==-1) pa=createname(t);
      tree[ch].parent=pa;
   }
   while(1) {
      if(scanf("%s %s",s,t)!=2) break;
      p[0]=findname(s); p[1]=findname(t);
      /* one of the persons don't exist in the tree, can't be relatives */
      if(p[0]==-1 || p[1]==-1) {
         printf("no relation\n");
         continue;
      }
      for(i=0;i<2;i++) {
         h[i]=0;
         j=p[i];
         while(tree[j].parent!=-1) {
            j=tree[j].parent;
            h[i]++;
         }
         top[i]=j;
      }
      if(top[0]!=top[1]) {
         printf("no relation\n");
      } else {
         /* unmark tree */
         for(i=0;i<n;i++)
            trav[i]=0;
         /* follow top person up the tree */
         j=h[0]<h[1] ? 0 : 1;
         k=h[j];
         i=p[j];
         trav[i]=k+1;
         while(tree[i].parent!=-1) {
            i=tree[i].parent;
            k--;
            trav[i]=k+1;
         }
         /* follow the other person up the tree and find the first common
            ancestor */
         j=1-j;
         i=p[j];
         while(tree[i].parent!=-1) {
            i=tree[i].parent;
            if(trav[i]>0) break;
         }
         if(h[0]==h[1] && trav[i]==h[0])
            printf("sibling\n");
         else if(h[0]+1==h[1] && trav[i]==h[1])
            printf("parent\n");
         else if(h[0]==h[1]+1 && trav[i]==h[0])
            printf("child\n");
         else if(trav[i]-1==h[0]) {
            for(j=0;j<h[1]-h[0]-2;j++)
               printf("great ");
            printf("grand parent\n");
         }
         else if(trav[i]-1==h[1]) {
            for(j=0;j<h[0]-h[1]-2;j++)
               printf("great ");
            printf("grand child\n");
         }
         else {
            printf("%d cousin",h[1-j]-trav[i]);
            if(abs(h[0]-h[1])>0) printf(" removed %d",abs(h[0]-h[1]));
            printf("\n");
         }
      }
   }
}
