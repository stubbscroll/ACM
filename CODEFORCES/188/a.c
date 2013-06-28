#include <stdio.h>
typedef long long ll;
int main() {
	ll ch=0;
	ll x,y,m,t,d;
	scanf("%I64d %I64d %I64d",&x,&y,&m);
	if(x>=m || y>=m) { puts("0"); return 0; }
	if(x<y) t=x,x=y,y=t;
	if(x>0 && y<0) {
		d=(-y)/x;
		y+=x*d;
		ch=d;
	}
	for(;;) {
		ch++;
		if(x<y) x+=y; else y+=x;
		if(x>=m || y>=m) break;
		if(x<=0 && y<=0) break;
	}
	if(x<m && y<m) puts("-1");
	else printf("%I64d\n",ch);
	return 0;
}
