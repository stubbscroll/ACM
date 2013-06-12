#include <stdio.h>
#include <string.h>

#define MAXN 500
#define MAXR 10000
#define INF 1000000

char navn[MAXN][6];
int nn;

#define MAXS 1024
char s[MAXS];

int reln[MAXN];
int relparents[MAXN][MAXN];
int reldist[MAXN][MAXN];

int getname(char *s) {
	int i;
	char t[7];
	for(i=0;i<5 && s[i] && s[i]!='\n';i++) t[i]=s[i];
	while(i<5) t[i++]=' ';
	t[i]=0;
	for(i=0;i<nn;i++) if(!strcmp(navn[i],t)) return i;
	if(nn==MAXN) { i=0; return 1.0/i; }
	strcpy(navn[nn],t);
	return nn++;
}

int tre1[MAXN];
int tre2[MAXN];

void gen(int *tre,int person,int generasjon) {
	int i;
	tre[person]=generasjon;
	for(i=0;i<reln[person];i++) gen(tre,relparents[person][i],generasjon+reldist[person][i]);
}

void closest(int *x,int *y) {
	int i;
	*x=*y=INF;
	for(i=0;i<nn;i++) if(tre1[i]>-1 && tre2[i]>-1 && tre1[i]<*x && tre2[i]<*y) *x=tre1[i],*y=tre2[i];
}

int main() {
	int a,b,c,x,y;
	do {
		nn=0;
		memset(reln,0,sizeof(reln));
		while(1) {
			fgets(s,MAXS,stdin);
			if(s[0]=='#') continue;
			if(s[0]=='E') break;
			if(s[0]=='R') {
				a=getname(s+1);
				b=getname(s+6);
				sscanf(s+11,"%d",&c);
				/*	b is an ancestor of a */
				relparents[a][reln[a]]=b;
				reldist[a][reln[a]++]=c;
			} else {
				/*	query! find closest common ancestor */
				a=getname(s+1);
				b=getname(s+6);
				memset(tre1,-1,sizeof(int)*nn);
				memset(tre2,-1,sizeof(int)*nn);
				gen(tre1,a,0);
				gen(tre2,b,0);
				closest(&x,&y);
				if(x==INF || a==b) printf("%s and %s are not related.\n",navn[a],navn[b]);
				else if(!x || !y) printf("%s and %s are descendant-%d.\n",navn[a],navn[b],x+y);
				else {
					if(x>y) c=x,x=y,y=c;
					printf("%s and %s are cousin-%d-%d.\n",navn[a],navn[b],x-1,y-x);
				}
			}
		}
	} while(nn);
	return 0;
}
