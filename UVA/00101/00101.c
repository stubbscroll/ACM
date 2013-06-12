#include <stdio.h>

int bl[25][26]; /* first dimension is position, second dimension is stack,
                  0=bottom, a value of -1 means end of blocks */
int pos[25];   /* where each block is */

int topof(int s)
{
   int i;

   for(i=0;i<26;i++)
      if(bl[s][i]==-1)
         return i;
}

void put(int b,int s)
{
   int i;

   i=topof(s);
   bl[s][i]=b;
   bl[s][i+1]=-1;
   pos[b]=s;
}

int main()
{
   char s[100];
   int n;
   int i,i2,j,k,k2;
   int a,b,o2,o;

   gets(s);
   sscanf(s,"%d",&n);
   for(i=0;i<n;i++) {
      bl[i][0]=i;
      bl[i][1]=-1;
      pos[i]=i;
   }
   do {
      gets(s);
      if(strlen(s)>=4 && strncmp(s,"quit",4)==0)
         break;
      else {
         o2=0;
         if(strlen(s)>=4 && !strncmp(s,"move",4))
            o2=1;
         if(strlen(s)>=4 && !strncmp(s,"pile",4))
            o2=2;
         if(!o2)
            continue;
         sscanf(s+4,"%d",&a);
         i=5;
         while(i<strlen(s) && s[i]>='0' && s[i]<='9')
            i++;
         while(i<strlen(s) && s[i]==' ')
            i++;
         o=0;
         if(strlen(s+i)>=4 && !strncmp(s+i,"onto",4))
            o=1;
         else if(strlen(s+i)>=4 && !strncmp(s+i,"over",4))
            o=2;
         if(!o)
            continue;
         i+=4;
         sscanf(s+i,"%d",&b);
         if(a>=n || b>=n || a<0 || b<0)
            continue;
         if(a==b)
            continue;
         if(pos[a]==pos[b])
            continue;
         if(o2+o==2) { /* move onto */
            i=pos[a];
            i2=pos[b];
            k=topof(i)-1;
            do {
               if(bl[i][k]==a || k<0) break;
               if(bl[i][k]==i && i!=a) {
                  printf("yikes1\n");
                  return;
                  break;
               }
               put(bl[i][k],bl[i][k]);
               bl[i][k]=-1;
               k--;
            } while(1);
            k2=topof(i2)-1;
            do {
               if(bl[i2][k2]==b || k<0) break;
               if(bl[i2][k2]==i2 && i2!=b) {
                  printf("yikes2\n");
                  return;
                  break;
               }
               put(bl[i2][k2],bl[i2][k2]);
               bl[i2][k2]=-1;
               k2--;
            } while(1);
            put(bl[i][k],i2);
            bl[i][k]=-1;
         } else if(o2+o==4) { /* pile over */
            i=pos[a];
            i2=pos[b];
            for(j=0;j<26;j++)
               if(bl[i][j]==a)
                  break;
            k=topof(i2);
            k2=topof(i);
            for(;j<k2;j++) {
               pos[bl[i][j]]=i2;
               bl[i2][k++]=bl[i][j];
               bl[i][j]=-1;
            }
            bl[i2][k]=-1;
         } else if(o2==2) { /* pile onto */
            i=pos[a];
            i2=pos[b];
            k2=topof(i2)-1;
            do {
               if(bl[i2][k2]==b || k<0) break;
               if(bl[i2][k2]==i2 && i2!=b) {
                  printf("yikes3\n");
                  return;
                  break;
               }
               put(bl[i2][k2],bl[i2][k2]);
               bl[i2][k2]=-1;
               k2--;
            } while(1);
            for(j=0;j<26;j++)
               if(bl[i][j]==a)
                  break;
            k=topof(i2);
            k2=topof(i);
            for(;j<k2;j++) {
               pos[bl[i][j]]=i2;
               bl[i2][k++]=bl[i][j];
               bl[i][j]=-1;
            }
            bl[i2][k]=-1;
         } else { /* move over */
            i=pos[a];
            i2=pos[b];
            k=topof(i)-1;
            do {
               if(bl[i][k]==a || k<0) break;
               if(bl[i][k]==i && i!=a) {
                  printf("yikes4\n");
                  return;
                  break;
               }
               put(bl[i][k],bl[i][k]);
               bl[i][k]=-1;
               k--;
            } while(1);
            put(bl[i][k],i2);
            bl[i][k]=-1;
         }
      }
/*   printf("%s:\n",s);
   for(i=0;i<n;i++) {
      printf("%d:",i);
      for(j=0;j<25;j++) {
         if(bl[i][j]==-1)
            break;
         printf(" %d",bl[i][j]);
      }
      printf("\n");
   }*/

   } while(1);
   for(i=0;i<n;i++) {
      printf("%d:",i);
      for(j=0;j<26;j++) {
         if(bl[i][j]==-1)
            break;
         printf(" %d",bl[i][j]);
      }
      printf("\n");
   }
}
