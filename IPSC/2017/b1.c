/* algorithm: generate all cells to be traversed, sorted by distance from
   upper left. then reorder cells so that transitions between diagonals match */

#include <stdio.h>

#define INF 1000

int r,c,flip;
char cols[2],col;

int listr[100000],listc[100000];
int n;

void swap(int i,int j) {
	int t;
	t=listr[i],listr[i]=listr[j],listr[j]=t;
	t=listc[i],listc[i]=listc[j],listc[j]=t;
}

int can(int i,int j) {
	int dx=listr[j]-listr[i];
	int dy=listc[j]-listc[i];
	if(dx<0) dx=-dx;
	if(dy<0) dy=-dy;
	return dx==dy;
}

void solve() {
	int t,i,j,prevs,curs,cure,r1,c1;
	scanf("%d %d %s",&r,&c,cols);
	col=cols[0];
	flip=0;
	if(r>c) t=r,r=c,c=t,flip=1;
	if((r==1 && c>=3 && col=='W') ||
	   (r==1 && c>=4 && col=='B')) {
		puts("impossible\n");
		return;
	}
	n=0;
	for(i=(col=='B');i<r+c-1;i+=2) {
		for(j=0;j<=i;j++) if(j<r && i-j<c) listr[n]=j,listc[n++]=i-j;
	}
	listr[n]=listc[n]=INF;
	curs=cure=0;
	while(listr[cure]+listc[cure]==listr[curs]+listc[curs]) cure++;
	while(1) {
		if(listr[cure]==INF) break;
		prevs=curs; curs=cure;
		while(listr[cure]+listc[cure]==listr[curs]+listc[curs]) cure++;
		if(curs+1==cure && cure==n) {
			/* special case: last diagonal is 1 point, find place to insert it */
			for(i=1;i<n-1;i++) if(can(i-1,curs) && can(curs,i)) {
				r1=listr[curs]; c1=listc[curs];
				for(j=n-2;j>=i;j--) listr[j+1]=listr[j],listc[j+1]=listc[j];
				listr[i]=r1; listc[i]=c1;
				goto done;
			}
		}
		/* find 2 points in each diagonal that are neighbours */
		for(i=(prevs?prevs+1:prevs);i<curs;i++) for(j=curs;j<cure;j++) if(can(i,j)) {
			if(i!=curs-1) swap(i,curs-1);
			if(j!=curs) swap(j,curs);
			goto ok;
		}
		printf("error");
	ok:;
	}
done:
	for(i=0;i<n;i++) {
		if(flip) printf("%d %d\n",listc[i]+1,listr[i]+1);
		else printf("%d %d\n",listr[i]+1,listc[i]+1);
	}
	putchar('\n');
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
