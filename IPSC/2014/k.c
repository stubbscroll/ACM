/* solution for knowledge test, easy input
   algorithm: solve input file manually by replacing clues with answers
   in the original input file, then run this program to generate output grid
   and for performing sanity check. */

#include <stdio.h>
#include <string.h>

char g[44][44];
int x,y;

int main() {
	int i,j,n,u,v;
	char s[111];
	scanf("%d %d",&x,&y);
	for(i=0;i<x;i++) scanf("%s",g[i]);
	/* horizontal */
	scanf("%d",&n);
	for(i=0;i<n;i++) {
		scanf("%d %d %s",&u,&v,s);
		for(j=0;v+j<y;j++) if(g[u][j+v]=='.') break;
		if(j!=strlen(s)) printf("wrong length at %d %d %s, expected %d, found %d\n",u,v,s,(int)strlen(s),j);
		for(j=0;s[j];j++) g[u][j+v]=s[j];
	}
	/* vertical */
	scanf("%d",&n);
	for(i=0;i<n;i++) {
		scanf("%d %d %s",&u,&v,s);
		for(j=0;u+j<y;j++) if(g[u+j][v]=='.') break;
		if(j!=strlen(s)) printf("wrong length at %d %d %s, expected %d, found %d\n",u,v,s,(int)strlen(s),j);
		for(j=0;s[j];j++) {
			if(g[u+j][v]!='#' && g[u+j][v]!=s[j]) printf("error at %d %d %s pos %d\n",u,v,s,j);
			g[u+j][v]=s[j];
		}
	}
	for(i=0;i<x;i++) puts(g[i]);
	return 0;
}
