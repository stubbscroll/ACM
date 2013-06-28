#include <stdio.h>
#include <string.h>
#define INF 1000
char navn[50][133];
int nn;
int f[55][55];
int n,ne;

int getnavn(char *s) {
	int i;
	for(i=0;i<nn;i++) if(!strcmp(s,navn[i])) return i;
	strcpy(navn[nn],s);
	return nn++;
}

int main() {
	char s[133],t[133];
	int a,b,i,j,k,no=1;
	while(scanf("%d %d",&n,&ne),n) {
		for(i=0;i<n;i++) for(j=0;j<n;j++) f[i][j]=f[j][i]=(i==j)?0:INF;
		for(nn=i=0;i<ne;i++) {
			scanf("%s %s",s,t);
			a=getnavn(s);
			b=getnavn(t);
			f[a][b]=f[b][a]=1;
		}
		for(k=0;k<n;k++) for(i=0;i<n;i++) for(j=0;j<n;j++) if(f[i][j]>f[i][k]+f[k][j]) f[i][j]=f[i][k]+f[k][j];
		for(a=i=0;i<n;i++) for(j=0;j<n;j++) if(a<f[i][j]) a=f[i][j];
		printf("Network %d: ",no++);
		if(a==INF) puts("DISCONNECTED\n");
		else printf("%d\n\n",a);
	}
	return 0;
}
