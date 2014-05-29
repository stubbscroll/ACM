/* solution to electrical circuits, hard input.
   algorithm: solve each connected component separately,
   multiply number of combinations.
   the large component: use that it is a tree with subgraphs on leaves.
   optimized for code reusage, no performance regards taken.
   java because of bigint.
   invoke with: java -Xmx1500m e2 < e2.in */

import java.math.*;
import java.util.*;

public class e2 {
	public static void main(String a[]) {
		new e2().go();
	}

	Scanner sc=new Scanner(System.in);

	void go() {
		int T=sc.nextInt();
		while(T-->0) solve();
	}

	void solve() {
		BigInteger r=BigInteger.ONE;
		int n=sc.nextInt();
		int m=sc.nextInt();
		/* throw coordinates */
		for(int i=0;i<n+n;i++) sc.nextInt();
		boolean g[][]=new boolean[n][n];
		for(int i=0;i<m;i++) {
			int a=sc.nextInt()-1,b=sc.nextInt()-1;
			g[a][b]=g[b][a]=true;
		}
		/* for each component, calculate number of matchings */
		boolean taken[]=new boolean[n];
		for(int i=0;i<n;i++) if(!taken[i]) {
			boolean g2[][]=flood(g,i,taken,-1,-1,null);
			if(g2.length%2!=0) {
				System.out.println("0");
				return;
			}
			if(g2.length<64) r=r.multiply(BigInteger.valueOf(findways(g2,0)));
			else r=r.multiply(findwayslarge(g2));
		}
		System.out.println(r);
	}

	/* flood fill from node in g and return new subgraph */
	/* taken is a global array of visited nodes */
	/* a-b is a forbidden edge, don't follow it */
	boolean[][] flood(boolean g[][],int u,boolean taken[],int a,int b,int getcomp[]) {
		int n=g.length,N=1;
		boolean vis[]=new boolean[n];
		taken[u]=vis[u]=true;
		int q[]=new int[n],qs=0,qe=0;
		q[qe++]=u;
		while(qs<qe) {
			u=q[qs++];
			for(int i=0;i<n;i++) if(!taken[i] && g[u][i]) {
				if((u==a && i==b) || (u==b && i==a)) continue;
				q[qe++]=i;
				taken[i]=vis[i]=true;
				N++;
			}
		}
		int comp[]=new int[N];
		for(int i=0,j=0;i<n;i++) if(vis[i]) comp[j++]=i;
		if(getcomp!=null) for(int i=0;i<N;i++) getcomp[i]=comp[i];
		boolean g2[][]=new boolean[N][N];
		for(int i=0;i<N;i++) for(int j=0;j<N;j++) g2[i][j]=g[comp[i]][comp[j]];
		return g2;
	}

	/* find number of combinations in graph g using memoization */
	HashMap<Long,Long> h;
	long findways(boolean g[][],long mask) {
		h=new HashMap<Long,Long>();
		long r=btr(g,mask);
		h=null;
		return r;
	}

	long btr(boolean g[][],long mask) {
		int n=g.length,ix;
		if(h.containsKey(mask)) return h.get(mask);
		long r=0;
		/* find first unmatched node */
		for(ix=0;ix<n;ix++) if(0==(mask&(1L<<ix))) break;
		if(ix==n) {
			h.put(mask,1L);
			return 1;
		}
		/* try all ways to match it */
		for(int j=ix+1;j<n;j++) if(g[ix][j] && 0==(mask&(1L<<j))) r+=btr(g,mask+(1L<<ix)+(1L<<j));
		h.put(mask,r);
		return r;
	}

	/* check if g is connected if we remove a,b */
	boolean connected(boolean g[][],int a,int b) {
		return g.length==flood(g,0,new boolean[g.length],a,b,null).length;
	}

	/* this graph is a tree with collapsed subgraphs as leaves.
	   solve each subgraph and multiply result */
	BigInteger findwayslarge(boolean g[][]) {
		int n=g.length;
		boolean removed[][]=new boolean[n][n];
		/* remove all bridges in graph */
		for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) if(g[i][j] && !connected(g,i,j)) removed[i][j]=removed[j][i]=true;
		for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(removed[i][j]) g[i][j]=false;
		/* calculate degrees */
		int deg[]=new int[n];
		for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(g[i][j]) deg[i]++;
		/* solve for each component */
		boolean taken[]=new boolean[n];
		BigInteger r=BigInteger.ONE;
		int comp[]=new int[n];
		for(int u=0;u<n;u++) if(!taken[u]) {
			boolean g2[][]=flood(g,u,taken,-1,-1,comp);
			int N=g2.length;
			if(N==1) continue;
			long mask=0;
			if(N%2==1) {
				/* odd number of nodes: remove node adjacent to removed edge */
				boolean found=false;
				for(int i=0;i<N;i++) {
					for(int j=0;j<n;j++) {
						if(removed[comp[i]][j]) {
							found=true;
							mask=1L<<i;
							break;
						}
					}
					if(found) break;
				}
				if(!found) System.out.println("error");
			}
			r=r.multiply(BigInteger.valueOf(findways(g2,mask)));
		}
		return r;
	}

}
