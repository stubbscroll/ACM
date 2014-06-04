#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char u[64],v[64],w[64];

int toread[26];
int towrite[26];
int var[26];

int getval(char *s) {
  if(isdigit(s[0])) return strtol(s,0,10);
  return var[s[0]-'A'];
}

void storeval(int z,char *s) {
  var[s[0]-'A']=z;
}

void simul(char *t) {
  FILE *f=fopen(t,"r");
  char s[128];
  int num;
  int tor=0,tow=0;
  if(!f) { printf("error\n"); return; }
  while(fgets(s,127,f)) {
    num=sscanf(s,"%s %s %s",u,v,w);
    if(num!=2 && num!=3) continue;
    if(!strcmp(u,"and")) storeval(getval(v)&getval(w),v);
    if(!strcmp(u,"or")) storeval(getval(v)|getval(w),v);
    if(!strcmp(u,"not")) storeval(~getval(v),v);
    if(!strcmp(u,"mov")) storeval(getval(w),v);
    if(!strcmp(u,"get")) storeval(toread[tor++],v);
    if(!strcmp(u,"put")) towrite[tow++]=var[v[0]-'A'];
    if(!strcmp(u,"shl")) storeval(((getval(v)<<getval(w))&255),v);
    if(!strcmp(u,"shr")) storeval(((getval(v)>>getval(w))&255),v);
  }
  fclose(f);
}

int main(int argc,char**argv) {
  int i;
  for(i=0;i<7;i++) toread[i]=i&1;
  simul(argv[1]);
  for(i=0;i<7;i++) printf("%d ",towrite[i]);
  return 0;
}
