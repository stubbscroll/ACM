/* uva 100 AC 09.10.2008 */

import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
	BufferedReader in=new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st=new StringTokenizer("");
	int INT(Object o) { return Integer.parseInt(o.toString()); }
	String L() throws Exception { return in.readLine(); }
	String STR() throws Exception {
		while(!st.hasMoreTokens()) st=new StringTokenizer(L());
		return st.nextToken();
	}
	int INT() throws Exception { return Integer.parseInt(STR()); }
	public static void main(String args[]) throws Exception {
		new Main().entry();
	}
	int MAX=4000000;
	int dp[]=new int[MAX];
	int numiter(int n) {
		if(n<2) return 1;
		if(n<MAX && dp[n]>-1) return dp[n];
		int res;
		if((n&1)>0) return res=1+numiter(n*3+1);
		else res=1+numiter(n>>1);
		if(n<MAX) dp[n]=res;
		return res;
	}
	public void entry() throws Exception {
		Arrays.fill(dp,-1);
		while(true) {
			String s=L();
			if(s==null) break;
			st=new StringTokenizer(s);
			int oldi=INT(),oldj=INT();
			int i=Math.min(oldi,oldj),j=Math.max(oldi,oldj);
			int maks=0;
			for(;i<=j;i++) maks=Math.max(maks,numiter(i));
			System.out.printf("%d %d %d\n",oldi,oldj,maks);
		}
	}
}
