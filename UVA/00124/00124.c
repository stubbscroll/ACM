#include <stdio.h>
#include <string.h>

char var[21];
char r[100][5];
int re[256][256];
char v[20][5];
char s[300];

int n,nc;

char b[21];

char sol[500][25];
int soln;

void backtrack(int p)
{
   char bak[21];
   int i,j,k;

   if(p==n) {
      strcpy(sol[soln++],b);
      return;
   }
   for(i=0;i<=p;i++) {
      for(j=0;j<p;j++)
         bak[j]=b[j];
      for(j=p;j>i;j--)
         b[j]=b[j-1];
      b[i]=var[p];
      for(j=0;j<p;j++)
         for(k=j+1;k<=p;k++)
            if(re[b[j]][b[k]]==1) goto not;
      backtrack(p+1);
not:
      for(j=0;j<p;j++)
         b[j]=bak[j];
   }
}

int main()
{
   int i,j,first=1;

   while(1) {
      if(gets(s)==NULL) break;
      n=sscanf(s,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
         v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],v[10],v[11],v[12],
         v[13],v[14],v[15],v[16],v[17],v[18],v[19],v[20]);
      gets(s);
      nc=sscanf(s,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s "
         "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s "
         "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s "
         "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s "
         "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
         r[0],r[1],r[2],r[3],r[4],r[5],r[6],r[7],r[8],r[9],
         r[10],r[11],r[12],r[13],r[14],r[15],r[16],r[17],r[18],r[19],
         r[20],r[21],r[22],r[23],r[24],r[25],r[26],r[27],r[28],r[29],
         r[30],r[31],r[32],r[33],r[34],r[35],r[36],r[37],r[38],r[39],
         r[40],r[41],r[42],r[43],r[44],r[45],r[46],r[47],r[48],r[49],
         r[50],r[51],r[52],r[53],r[54],r[55],r[56],r[57],r[58],r[59],
         r[60],r[61],r[62],r[63],r[64],r[65],r[66],r[67],r[68],r[69],
         r[70],r[71],r[72],r[73],r[74],r[75],r[76],r[77],r[78],r[79],
         r[80],r[81],r[82],r[83],r[84],r[85],r[86],r[87],r[88],r[89],
         r[90],r[91],r[92],r[93],r[94],r[95],r[96],r[97],r[98],r[99]);
      for(i=0;i<n;i++) var[i]=v[i][0];
      for(i=0;i<256;i++)
         for(j=0;j<256;j++)
            re[i][j]=0;
      for(i=0;i<nc;i+=2) {
         re[r[i][0]][r[i+1][0]]=-1;
         re[r[i+1][0]][r[i][0]]=1;
      }
      b[n]=0;
      soln=0;
      backtrack(0);
      if(first==0) printf("\n");
      first=0;
      qsort(sol,soln,sizeof(sol[0]),strcmp);
      for(i=0;i<soln;i++) printf("%s\n",sol[i]);
   }
}
