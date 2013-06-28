#include <stdio.h>
#include <string.h>

int aut,n;
char s[40];

/* dp[mask][at] mask: bitmask, at: where we're at
   mask: bit 2: pos 0,
         bit 3: pos n-1
         bit 1: pos at
				 bit 0: pos at+1 */
char dp[16][33];

int main() {
	int i,at,z,mask,b,last3,next;
	while(scanf("%d %d %s",&aut,&n,s)==3) {
		memset(dp,0,sizeof(dp));
		for(z=i=0;i<n;i++) s[i]-='0';
		/* process char 0 */
		if(((aut&128)==0)==(s[0]==0)) z=dp[8|4|1][1]=1; /* 111 */
		if(((aut&64)==0)==(s[0]==0)) z=dp[8|4|0][1]=1;  /* 110 */
		if(((aut&32)==0)==(s[0]==0)) z=dp[8|0|1][1]=1;  /* 101 */
		if(((aut&16)==0)==(s[0]==0)) z=dp[8|0|0][1]=1;  /* 100 */
		if(((aut&8)==0)==(s[0]==0)) z=dp[ 0|4|1][1]=1;   /* 011 */
		if(((aut&4)==0)==(s[0]==0)) z=dp[ 0|4|0][1]=1;   /* 010 */
		if(((aut&2)==0)==(s[0]==0)) z=dp[ 0|0|1][1]=1;   /* 001 */
		if(((aut&1)==0)==(s[0]==0)) z=dp[ 0|0|0][1]=1;   /* 000 */
		if(!z) goto garden;
		/* process char 1 */
		for(mask=0;mask<16;mask++) if(dp[mask][1]) {
			for(b=0;b<2;b++) {
				/* bit 2 (leftmost), bit 0 (middle), b (rightmost) */
				last3=(mask&4)+((mask&1)<<1)+b;
				if((s[1]==0)!=((aut&(1<<last3))==0)) continue;
				next=(mask&12)+b+((mask&1)<<1);
				dp[next][2]=1;
			}
		}
		/* process char 2..n-3 */
		for(at=2;at<n-2;at++) for(mask=0;mask<16;mask++) if(dp[mask][at]) {
			for(b=0;b<2;b++) {
				/* bit 1 (leftmost), bit 0 (middle), b (rightmost) */
				last3=((mask&3)<<1)+b;
				if((s[at]==0)!=((aut&(1<<last3))==0)) continue;
				next=(mask&12)+b+((mask&1)<<1);
				dp[next][at+1]=1;
			}
		}
		/* process char n-2 and n-1 */
		for(mask=0;mask<16;mask++) if(dp[mask][n-2]) {
			/* bit 1 (leftmost), bit 0 (middle), bit 3 (rightmost) */
			last3=((mask&3)<<1)+((mask&8)>>3);
			if((s[n-2]==0)!=((aut&(1<<last3))==0)) continue;
			/* bit 0 (leftmost), bit 3 (middle), bit 2 (rightmost) */
			last3=((mask&1)<<2)+((mask&12)>>2);
			if((s[n-1]==0)==((aut&(1<<last3))==0)) goto reach;
		}
	garden:
		puts("GARDEN OF EDEN");
		continue;
	reach:
		puts("REACHABLE");
	}
	return 0;
}
