import java.io.*;
import java.math.*;
import java.util.*;

public class A {
	BufferedReader in=new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st=new StringTokenizer("");
	int INT(Object o) { return Integer.parseInt(o.toString()); }
	String LINE() throws Exception { return in.readLine(); }
	String TOKEN() throws Exception {
		while(!st.hasMoreTokens()) st=new StringTokenizer(LINE());
		return st.nextToken();
	}
	int INT() throws Exception { return Integer.parseInt(TOKEN()); }
	long LONG() throws Exception { return Long.parseLong(TOKEN()); }
	double DOUBLE() throws Exception { return Double.parseDouble(TOKEN()); }
	String PD(double d,int n) {
		return String.format("%."+n+"f",d).replace(",",".");
	}

	public static void main(String args[]) throws Exception {
		new A().go();
	}

	public void go() throws Exception {
		int cases=INT();
		while(cases-->0) {
			BigInteger r = new BigInteger(TOKEN());
			while(true) {
				String s=TOKEN();
				if(s.equals("=")) break;
				BigInteger b = new BigInteger(TOKEN());
				if(s.equals("+")) r=r.add(b);
				else if(s.equals("-")) r=r.subtract(b);
				else if(s.equals("*")) r=r.multiply(b);
				else if(s.equals("/")) r=r.divide(b);
			}
			System.out.println(r);
		}
	}
}
