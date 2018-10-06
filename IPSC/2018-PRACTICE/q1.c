/* solution for qizz quzz, easy input
   algorithm: build up list of replacements as we scan the list of input items
   linearly. for each item, check if there's a replacement string and check if
   the item's prefix matches this string. add the remaining suffix as a new
   replacement string
*/   

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int n;
char t[1000][25001];

int k;
int d[1000];
char s[1000][1000];

void solve() {
	int i,j,val,up;
	char u[25001];
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%s",t[i]);
	/* check sequence, find first entry that fails */
	k=0;
	for(i=0;i<n;i++) {
		int hasd=0,hasl=0;
		for(j=0;t[i][j];j++) {
			if(isdigit(t[i][j])) hasd=1;
			else hasl=1;
		}
		if(t[i][0]=='0' || (hasd&hasl)) goto failed;
		/* build string for this index */
		up=0;
		u[0]=0;
		for(j=0;j<k;j++) if((i+1)%d[j]==0) {
			strcpy(u+up,s[j]);
			up+=strlen(s[j]);
		}
		if(strncmp(u,t[i],up)) goto failed;
		if(hasd) {
			if(strlen(t[i])>5) goto failed;
			val=strtol(t[i],0,10);
			if(val!=i+1) goto failed;
			continue;
		}
		/* build string for this index */
		up=0;
		u[0]=0;
		for(j=0;j<k;j++) if((i+1)%d[j]==0) {
			strcpy(u+up,s[j]);
			up+=strlen(s[j]);
		}
		if(strncmp(u,t[i],up)) goto failed;
		/* the rest of the string is a new entry */
		/* the rest is an empty string: no entry, we're ok */
		if(!t[i][up]) continue;
		/* constraint: k<=2 */
		if(k==2) goto failed;
		strcpy(s[k],t[i]+up);
		/* constraint: exactly 4 chars */
		if(strlen(s[k])!=4) goto failed;
		d[k]=i+1;
		k++;
	}
failed:
	printf("%d\n",i);
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
