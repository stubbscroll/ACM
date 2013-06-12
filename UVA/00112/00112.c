#include <stdio.h>

struct bst_s {
   int n;
   int l;
   int r;
} bst[1000];
int numbst;

char s[100000];
int p,found,sum;

void null()
{
   while(iswspace(s[p])) p++;
   while(s[p]==0) {
      gets(s);
      p=0;
      while(iswspace(s[p])) p++;
   }
}

int tree()
{
   int cur,i,j,k;

   cur=numbst;
   null();
   if(s[p]!='(') while(1) printf("error ");
   p++;
   null();
   if(isdigit(s[p]) || s[p]=='-') { /* read subtree */
      numbst++;
      sscanf(s+p,"%d",&i);
      bst[cur].n=i;
      p++;
      while(isdigit(s[p])) p++;
      null();
      bst[cur].l=tree();
      bst[cur].r=tree();
   } else {
      if(s[p]!=')') while(1) printf("error ");
      p++;
      return -1;
   }
   null();
   if(s[p]!=')') while(1) printf("error %s %d %d \n",s,s[p],p);
   p++;
   return cur;
}

void traverse(int n,int s)
{
   if(found) return;
   s+=bst[n].n;
   if(bst[n].l!=-1)
      traverse(bst[n].l,s);
   if(bst[n].r!=-1)
      traverse(bst[n].r,s);
   if(bst[n].l==-1 && bst[n].r==-1 && s==sum) {
      found=1;
   }
}

int main()
{
   int i;

   do {
      if(gets(s)==NULL) break;
      p=0;
      while(iswspace(s[p])) p++;
      sscanf(s,"%d",&sum);
      p++;
      while(isdigit(s[p])) p++;
      null();
      numbst=0;
      tree();
      if(numbst==0) goto fail;
      found=0;
      traverse(0,0);
      if(!found) goto fail;
      printf("yes\n");
      goto done;
fail:
      printf("no\n");
done:
      ;
   } while(1);
}
