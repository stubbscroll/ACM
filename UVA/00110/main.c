#include <stdio.h>

int n,cases;

void print(int a,int b,int c,int d,int e,int f,int g,int h,int p)
{
  int i;
  int l[8];
  int m[8];

  l[0]=a; l[1]=b; l[2]=c; l[3]=d; l[4]=e; l[5]=f; l[6]=g; l[7]=h;
  for(i=0;i<n;i++)
    m[i]=0;
  for(i=0;i<n;i++)
    m[l[i]]=1;
  for(i=0;i<n;i++)
    if(!m[i])
      l[n-1]=i;

  for(i=0;i<n;i++)
    printf("  ");
  printf("writeln(");
  for(i=0;i<n-1;i++)
    printf("%c,",'a'+l[i]);
  printf("%c)\n",'a'+l[i]);  
}

void generate(int a,int b,int c,int d,int e,int f,int g,int h,int p)
{
  int l[8],i,j,m[8];

  if(p==n-1) {
    print(a,b,c,d,e,f,g,h,p);
    return;
  }
  l[0]=a; l[1]=b; l[2]=c; l[3]=d; l[4]=e; l[5]=f; l[6]=g; l[7]=h;
  for(i=0;i<=p+1;i++) {
    for(j=0;j<p+1;j++)
      printf("  ");
    if(i==0)
      printf("if ");
    else if(i==p+1)
      printf("else\n");
    else
      printf("else if ");
    if(i<p+1) {
      for(j=0;j<8;j++) m[j]=l[j];
      printf("%c < %c then\n",'a'+l[p-i],'a'+l[p-i+1]);
      generate(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],p+1);
      j=l[p-i]; l[p-i]=l[p-i+1]; l[p-i+1]=j;
    } else {
      generate(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],p+1);      
    }
  }
}

int main()
{
  int i;
  char s[20];

  gets(s);
  sscanf(s,"%d",&cases);
  gets(s);
  do {
     gets(s);
     sscanf(s,"%d",&n);
     gets(s);
     cases--;
     printf("program sort(input,output);\nvar\n");
     for(i=0;i<n-1;i++)
       printf("%c,",'a'+i);
     printf("%c : integer;\nbegin\n  readln(",'a'+i);
     for(i=0;i<n-1;i++)
       printf("%c,",'a'+i);
     printf("%c);\n",'a'+i);
     generate(0,1,2,3,4,5,6,7,0);
     printf("end.\n");
     if(cases)
        printf("\n");
  } while(cases);
  return 0;
}
