/* solution to andrew's revenge, hard input
   original source modified to take inverse of A, and henceforth reverse
   the encryption.
   with no further optimizations the program needs 45 seconds. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int randseed=47;
int A[7][7], B[7][7], C[7][7], D[7], E, F;
char ch;

int RANDOM() { return randseed=(randseed*5621+1)%65536; }

void combine() {
	int i,j,k;
	for (i=0;i<7;i++) for (j=0;j<7;j++) {
		C[i][j]=0; 
		for (k=0;k<7;k++) C[i][j] += (B[i][k] * A[k][j]);
		C[i][j]%=26;
		if(C[i][j]<0) C[i][j]+=26,C[i][j]%=26;
	}
}

int reduce(int x, int y) { if (!(x*y)) return x+y; return reduce(y,x%y); }

/* identity matrix with additional 1 */
int type1() {
	int i,j,x,y,c=0;
	for(i=0;i<7;i++) if(B[i][i]!=1) return 0;
	for(i=0;i<7;i++) for(j=0;j<7;j++) if(i!=j && B[i][j]) {
		if(B[i][j]!=1) return 0;
		x=i; y=j; c++;
	}
	if(c!=1) return 0;
	B[x][y]*=-1;
	return 1;
}

int invers(int a) {
	int i;
	for(i=0;i<26;i++) if(a*i%26==1) return i;
	printf("inverse error\n");
	return 0;
}

/* diagonal matrix with at one non-one value */
int type2() {
	int i,j,x=0,c=0,o=0;
	for(i=0;i<7;i++) for(j=0;j<7;j++) if(i==j) {
		if(B[i][i]==1) o++;
		else c++,x=i;
	} else if(B[i][j]) return 0;
	if(c!=1) return 0;
	B[x][x]=invers(B[x][x]);
	return 1;
}

/* identity, do nothing */
int type3() {
	int i,j;
	for(i=0;i<7;i++) for(j=0;j<7;j++) if(B[i][j]!=(i==j)) return 0;
	return 1;
}

int main(void){
	int i,j,loop;
	
	for (i=0;i<7;i++) for (j=0;j<7;j++) A[i][j]=(i==j);
	for (loop=0;loop<134620173;loop++) {
		for (i=0;i<7;i++) for (j=0;j<7;j++) B[i][j]=(i==j);
		i=RANDOM()%7; j=RANDOM()%7;
		if (i==j) {
			i=RANDOM()%26; while (reduce(i,26)>=2) i=RANDOM()%26;
			B[j][j]=i; 
		} else B[i][j]=1;
		/* inverse! */
		if(type1());
		else if(type2());
		else if(type3());
		else printf("matrix error\n");
		
		combine(); 
		memcpy(A,C,sizeof(A));
	}
	E=0;
	while (!feof(stdin)) {
		scanf("%c",&ch); if (ch<'A') continue; if (ch>'Z') continue;
		D[E++]=ch-'A'; 

		if (E==7) { 
			for (i=0;i<7;i++) {
				F=0; for (j=0;j<7;j++) F+=D[j]*A[j][i]; F%=26; 
				printf("%c",F+'A');
			}
			E=0;
		}
	}
	printf("\n");
	return 0;
}
