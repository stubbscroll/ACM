#include <stdio.h>

int bits[5]={1,2,4,8,16};
int c[15]; /* card */
int t[15]; /* suit */
int v[15]; /* how much of each value */
int q[5];  /* sort quicker */ 

int tryhand(int h)
{
   int i,j,k;

   j=5;
   for(i=0;i<5;i++)
      if(h&bits[i]) {
         c[10+i]=c[i];
         t[10+i]=t[i];
      } else {
         c[10+i]=c[j];
         t[10+i]=t[j++];
      }
   for(i=0;i<15;i++)
      v[i]=0;
   for(i=0;i<5;i++)
      v[c[10+i]]++;
   for(i=0;i<5;i++)
      q[i]=v[c[10+i]]*100+c[10+i];
   do {
      j=0;
      for(i=0;i<4;i++)
         if(q[i]<q[i+1]) {
            j=q[i]; q[i]=q[i+1]; q[i+1]=j;
            j=c[10+i]; c[10+i]=c[11+i]; c[11+i]=j;
            j=t[10+i]; t[10+i]=t[11+i]; t[11+i]=j;
         }
   } while(j);
   if(t[10]==t[11] && t[10]==t[12] && t[10]==t[13] && t[10]==t[14])
      j=1; /* flush */
   else
      j=0;
   /* check for straight */
   if(c[10]==14 && c[11]==5 && c[12]==4 && c[13]==3 && c[14]==2)
      k=1;
/*   else if(c[10]==14 && c[11]==13 && c[12]==12 && c[13]==11 && c[14]==2)
      k=1;
   else if(c[10]==14 && c[11]==13 && c[12]==12 && c[13]==3 && c[14]==2)
      k=1;
   else if(c[10]==14 && c[11]==13 && c[12]==4 && c[13]==3 && c[14]==2)
      k=1;
   else if(c[10]==14 && c[11]==13 && c[12]==12 && c[13]==11 && c[14]==10)
      k=1;*/
   else if(c[10]==c[11]+1 && c[10]==c[12]+2 && c[10]==c[13]+3 && c[10]==c[14]+4)
      k=1;
   else
      k=0;
   if(j+k==2)
      return 9;
   if(q[0]>400)
      return 8;
   if(q[0]>300 && q[3]>200)
      return 7;
   if(j==1)
      return 6;
   if(k==1)
      return 5;
   if(q[0]>300)
      return 4;
   if(q[0]>200 && q[2]>200)
      return 3;
   if(q[0]>200)
      return 2;
   return 1;
}

int main()
{
   char s[100];
   int i,j,max;

   do {
      if(gets(s)==NULL)
         break;
      if(strlen(s)<2)
         continue;
      for(i=0;i<10;i++) {
         t[i]=s[i*3+1];
         switch(s[i*3]) {
         case 'T':
            c[i]=10; break;
         case 'J':
            c[i]=11; break;
         case 'Q':
            c[i]=12; break;
         case 'K':
            c[i]=13; break;
         case 'A':
            c[i]=14; break;
         default:
            c[i]=s[i*3]-'0';
         }
      }
      printf("Hand: ");
      for(i=0;i<15;i++)
         printf("%c",s[i]);
      printf("Deck: ");
      for(i=15;i<29;i++)
         printf("%c",s[i]);
      printf(" Best hand: ");
      max=0;
      for(i=0;i<32;i++) {
         j=tryhand(i);
         if(j>max) max=j;
      }
      switch(max) {
      case 9: printf("straight-flush\n"); break;
      case 8: printf("four-of-a-kind\n"); break;
      case 7: printf("full-house\n"); break;
      case 6: printf("flush\n"); break;
      case 5: printf("straight\n"); break;
      case 4: printf("three-of-a-kind\n"); break;
      case 3: printf("two-pairs\n"); break;
      case 2: printf("one-pair\n"); break;
      case 1: printf("highest-card\n"); break;
      }
   } while(1);
}
