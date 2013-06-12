#include <stdio.h>

struct tree_s {
   char s[260];
   int v;
   int l;
} tree[260];
int n;

char s[200],t[200];
int v;

int comptree(struct tree_s *a,struct tree_s *b)
{
   if(a->l < b->l) return -1;
   if(a->l > b->l) return 1;
   return strcmp(a->s,b->s);
}

int main()
{
   int i,j,sl,tl;

   while(1) {
      n=0;
      while(1) {
         if(scanf("%s",s)!=1) return;
         sl=strlen(s);
         if(sl==2) break;
         sscanf(s,"(%d,%s",&v,t);
         tl=strlen(t);
         if(t[tl-1]==')') t[--tl]=0;
         tree[n].v=v;
         strcpy(tree[n].s,t);
         tree[n++].l=tl;
      }
      qsort(tree,n,sizeof(tree[0]),comptree);
      for(i=n-1;i>=0;i--) {
         if(i>0 && strcmp(tree[i].s,tree[i-1].s)==0) goto notok;
         sl=strlen(tree[i].s)-1;
         if(sl<0) continue;
         for(j=0;j<sl;j++)
            s[j]=tree[i].s[j];
         s[j]=0;
         for(j=i-1;j>=0;j--) {
            if(tree[j].l<sl) break;
            if(strcmp(tree[j].s,s)==0) goto ok;
         }
         goto notok;
ok:
         ;
      }
      for(i=0;i<n-1;i++)
         printf("%d ",tree[i].v);
      printf("%d\n",tree[i].v);
      goto done;
notok:
      printf("not complete\n");
done:
      ;
   }
}
