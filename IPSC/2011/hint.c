#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char buffer[10000];
int len;

int isdelete(int num) {
  int i;
  for(i=0;i<30;i++) if(num==(1<<i)) return 1;
  for(i=2;i*i<=num;i++) if(num%i==0) return 0;
  return 1;
}

int main() {
  int z,i,j;
  char input[10000];
  len=0;
  scanf("%s",input);
  for(z=0;z<strlen(input);z++) {
    if(input[z]>='0' && input[z]<='9') {
      if(len!=0) {
        printf("error");
        exit(1);
      }
    } else if(tolower(input[z])=='q') {
      strcpy(buffer,input);
      len=strlen(buffer);
    } else if(tolower(input[z])=='c') {
      for(i=0;i<len;i++) if(islower(buffer[i])) buffer[i]=toupper(buffer[i]);
      else if(isupper(buffer[i])) buffer[i]=tolower(buffer[i]);
    } else if(tolower(input[z])=='o') {
      for(i=0;i<len;i++) if(isdelete(len-i)) buffer[i]=0;
      j=len;
      for(i=len=0;i<j;i++) if(buffer[i]) buffer[len++]=buffer[i];
    } else if(tolower(input[z])=='p') {
      for(i=0;i<len;i++) if(isdelete(i+1)) buffer[i]=0;
      j=len;
      for(i=len=0;i<j;i++) if(buffer[i]) buffer[len++]=buffer[i];
    }
    printf("after %c: '%s'\n",input[z],buffer);
  }
  return 0;
}
