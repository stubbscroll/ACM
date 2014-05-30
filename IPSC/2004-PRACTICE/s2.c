/* solution to censored smiles, hard input
   algorithm: flood fill, recognise different faces, and output each different
   face along with the count. then inspect the output manually and obtain
   answer */

#include <stdio.h>

#define MAX 1000
#define MAXF 60
#define MAXU 11

char s[MAX][MAX+1];
int x,y;

int col[MAX][MAX];
int faces;

int dx[]={1,0,-1,0,1,1,-1,-1},dy[]={0,1,0,-1,1,-1,1,-1};

int q[MAX*MAX*2],qs,qe;

char f[MAXU][MAXF][MAXF];
int fc[MAXU];
int fx[MAXU],fy[MAXU];
int fn;

/* D-connected flood fill with id at (cx,cy) on cells containing c
   return number of filled cells */
int flood(int cx,int cy,char c,int id,int D) {
	int x2,y2,d;
	qs=qe=0;
	if(s[cx][cy]!=c || col[cx][cy]>-1) return 0;
	q[qe++]=cx; q[qe++]=cy; col[cx][cy]=id;
	while(qs<qe) {
		cx=q[qs++]; cy=q[qs++];
		for(d=0;d<D;d++) {
			x2=cx+dx[d]; y2=cy+dy[d];
			if(x2<0 || y2<0 || x2>=x || y2>=y || col[x2][y2]>-1 || s[x2][y2]!=c) continue;
			q[qe++]=x2; q[qe++]=y2; col[x2][y2]=id;
		}
	}
	return qe>>1;
}

/* return 1 cell with c and id is D-adjacent */
int adjacent(int cx,int cy,char c,int id,int D) {
	int x2,y2,d;
	for(d=0;d<D;d++) {
		x2=cx+dx[d]; y2=cy+dy[d];
		if(x2>-1 && y2>-1 && x2<x && y2<y && col[x2][y2]==id && s[x2][y2]==c) return 1;
	}
	return 0;
}

char cur[MAXF][MAXF];
int curx,cury;

int equalface(int ix) {
	int i,j;
	if(curx!=fx[ix] || cury!=fy[ix]) return 0;
	for(i=0;i<curx;i++) for(j=0;j<cury;j++) if(cur[i][j]!=f[ix][i][j]) return 0;
	return 1;
}

void solve() {
	int i,j,face,minx,maxx,miny,maxy;
	for(i=0;i<x;i++) for(j=0;j<y;j++) col[i][j]=-1;
	/* fill boundary */
	for(i=0;i<x;i++) flood(i,0,'0',0,4),flood(i,y-1,'0',0,4);
	for(i=1;i<y-1;i++) flood(0,i,'0',0,4),flood(x-1,i,'0',0,4);
	/* find face boundaries */
	for(faces=i=0;i<x;i++) for(j=0;j<y;j++) if(s[i][j]=='1' && col[i][j]<0 && adjacent(i,j,'0',0,4)) flood(i,j,'1',faces++,8);
	/* count each type of face */
	for(fn=face=0;face<faces;face++) {
		/* fill face interior */
		for(i=0;i<x;i++) for(j=0;j<y;j++) if(s[i][j]=='0' && col[i][j]<0 && adjacent(i,j,'1',face,4)) flood(i,j,'0',face+1,4);
		/* fill face features */
		for(i=0;i<x;i++) for(j=0;j<y;j++) if(s[i][j]=='1' && col[i][j]<0 && adjacent(i,j,'0',face+1,4)) flood(i,j,'1',face,8);
		/* find bounding box and extract face */
		minx=miny=x>y?x:y;
		maxx=maxy=-1;
		for(i=0;i<x;i++) for(j=0;j<y;j++) if(s[i][j]=='1' && col[i][j]==face) {
			if(minx>i) minx=i;
			if(maxx<i) maxx=i;
			if(miny>j) miny=j;
			if(maxy<j) maxy=j;
		}
		curx=maxx-minx+1; cury=maxy-miny+1;
		if(curx>=MAXF || cury>=MAXF) { puts("increase MAXF and recompile"); return; }
		for(i=minx;i<=maxx;i++) for(j=miny;j<=maxy;j++) cur[i-minx][j-miny]=0;
		for(i=minx;i<=maxx;i++) for(j=miny;j<=maxy;j++) if(s[i][j]=='1' && col[i][j]==face) cur[i-minx][j-miny]=1;
		for(i=0;i<fn;i++) if(equalface(i)) { fc[i]++; goto done; }
		/* new face */
		if(fn==MAXU) { puts("increase MAXU and recompile"); return; }
		for(i=0;i<curx;i++) for(j=0;j<cury;j++) f[fn][i][j]=cur[i][j];
		fc[fn]=1;
		fx[fn]=curx; fy[fn++]=cury;
	done:;
	}
	for(face=0;face<fn;face++) {
		printf("face %d, %d occurrences:\n",face,fc[face]);
		for(i=0;i<fx[face];i++) {
			for(j=0;j<fy[face];j++) printf("%c",f[face][i][j]?'#':'.');
			printf("\n");
		}
		printf("\n");
	}
}

int main() {
	int i;
	scanf("%d %d",&x,&y);
	for(i=0;i<x;i++) scanf("%s",s[i]);
	solve();
	return 0;
}
