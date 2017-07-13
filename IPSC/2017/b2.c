/* algorithm:
   - any W grid with r>=3,c>=3 are impossible because they start with 2 corners
     of degree 1, and more such corners are created during path
   - any B grid with r>=3,c>=3 and at least one even side are impossible for the
     same corner stuff reason
   - smallest dimension == 1 is possible if there's one eligible cell
   - smallest dimension == 2 is always possible, make a snake
   - B grid with r!=c are impossible, problematic corners are created
   - B square grid with odd size is possible, make an inward spiral
   - brute force search shows that odd*(odd+2) B grid is also possible
*/

#include <stdio.h>

int r,c;
char cols[2],col;

char m[133][133];
int listr[55555],listc[55555],n;

int dx[]={1,1,-1,-1};
int dy[]={1,-1,1,-1};

int count(int x,int y) {
	int d,x2,y2,res=0;
	for(d=0;d<4;d++) {
		x2=x+dx[d]; y2=y+dy[d];
		if(x2<0 || y2<0 || x2>=r || y2>=c || m[x2][y2]) continue;
		res++;
	}
	return res;
}

void solve() {
	int i,j,x,y,d,x2,y2,bestd,best,num;
	scanf("%d %d %s",&r,&c,cols);
	col=cols[0];
	/* impossible cases */
	if((r==1 && c>=3 && col=='W') ||
	   (r==1 && c>=4) ||
	   (c==1 && r>=3 && col=='W') ||
	   (c==1 && r>=4) ||
	   (r>=3 && c>=3 && col=='W') ||
	   (r>=3 && c>=3 && r!=c && r!=c+2 && r!=c-2) ||
	   (r>=3 && c>=3 && !(r&1))) {
		puts("impossible\n");
		return;
	}
	/* possible cases, hardcode size 1 and 2 */
	if(r==1) printf("1 %d\n\n",1+(col=='B'));
	else if(c==1) printf("%d 1\n\n",1+(col=='B'));
	else if(r==2) {
		for(i=0;i<c;i++) printf("%d %d\n",1+((i&1)^(col=='B')),i+1);
		putchar('\n');
	} else if(c==2) {
		for(i=0;i<r;i++) printf("%d %d\n",i+1,1+((i&1)^(col=='B')));
		putchar('\n');
	} else {
		/* the spiral algorithm */
		n=0;
		for(i=0;i<r;i++) for(j=0;j<c;j++) m[i][j]=0;
		if(r<c) x=0,y=1;
		else x=1,y=0;
		m[x][y]=1; listr[n]=x+1; listc[n++]=y+1;
		while(1) {
			/* stupid heuristic that hopefully enforces spiral: take the cell with
			   the fewest available neighbours */
			best=123; bestd=-1;
			for(d=0;d<4;d++) {
				x2=x+dx[d]; y2=y+dy[d];
				if(x2<0 || y2<0 || x2>=r || y2>=c || m[x2][y2]) continue;
				num=count(x2,y2);
				if(best>num) best=num,bestd=d;
			}
			if(bestd<0) break;
			x=x+dx[bestd]; y=y+dy[bestd]; m[x][y]=1;
			listr[n]=x+1; listc[n++]=y+1;
		}
		for(i=0;i<n;i++) printf("%d %d\n",listr[i],listc[i]);
		if(n!=r*c/2) printf("sanity");
		putchar('\n');
	}
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
