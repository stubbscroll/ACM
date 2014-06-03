import java.io.*;
import java.math.*;
import java.util.*;

public class C {
	BufferedReader in=new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st=new StringTokenizer("");
	String LINE() throws Exception { return in.readLine(); }
	String STR() throws Exception {
		while(!st.hasMoreTokens()) st=new StringTokenizer(LINE());
		return st.nextToken();
	}
	int INT() throws Exception { return Integer.parseInt(STR()); }
	long LONG() throws Exception { return Long.parseLong(STR()); }
	double DOUBLE() throws Exception { return Double.parseDouble(STR()); }
	String PD(double d,int n) {
		return String.format("%."+n+"f",d).replace(",",".");
	}

	public static void main(String args[]) throws Exception {
		new C().go();
	}

	String[][] str;
	int num[];
	int n;

	String var[];
	int val[];

	int evaltall(String s) {
		if(s.charAt(0)>='0' && s.charAt(0)<='9') return Integer.parseInt(s);
		for(int i=0;i<n;i++) if(s.equals(str[i][0])) return eval(i);
		System.out.println("oh man, error "+s);
		return -123;
	}

	int eval(int pos) {
		while(true) {
			boolean hasmul=false;
			for(int i=3;i<num[pos];i+=2) if(str[pos][i].equals("*") || str[pos][i].equals("/")) { hasmul=true; break; }
			if(!hasmul) break;
			String op;
			for(int i=3;i<num[pos];i+=2) if((op=str[pos][i]).equals("*") || op.equals("/")) {
				int a=evaltall(str[pos][i-1]);
				int b=evaltall(str[pos][i+1]);
				if(op.equals("*")) str[pos][i-1]=""+(a*b);
				else str[pos][i-1]=""+(a/b);
				for(int j=i+2;j<num[pos];j++) str[pos][j-2]=str[pos][j];
				num[pos]-=2;
				break;
			}
		}

		while(true) {
			boolean hasmul=false;
			for(int i=3;i<num[pos];i+=2) if(str[pos][i].equals("+") || str[pos][i].equals("-")) { hasmul=true; break; }
			if(!hasmul) break;
			String op;
			for(int i=3;i<num[pos];i+=2) if((op=str[pos][i]).equals("+") || op.equals("-")) {
				int a=evaltall(str[pos][i-1]);
				int b=evaltall(str[pos][i+1]);
				if(op.equals("+")) str[pos][i-1]=""+(a+b);
				else str[pos][i-1]=""+(a-b);
				for(int j=i+2;j<num[pos];j++) str[pos][j-2]=str[pos][j];
				num[pos]-=2;
				break;
			}
		}

		return Integer.parseInt(str[pos][2]);
	}

	public void go() throws Exception {
		String s=LINE();
		int cases=Integer.parseInt(s);
		boolean first=true;
		while(cases-->0) {
			s=LINE();
			s=LINE();
			n=Integer.parseInt(s);
			str=new String[n][];
			num=new int[n];
			var=new String[n];
			val=new int[n];
			for(int i=0;i<n;i++) {
				s=LINE();
				str[i]=s.split(" ");
				num[i]=str[i].length;
				var[i]=str[i][0];
			}
			for(int i=0;i<n;i++) val[i]=eval(i);
			for(int i=0;i<n;i++) for(int j=0;j<n-1;j++) if(var[j].compareTo(var[j+1])>0) {
				String x=var[j]; var[j]=var[j+1]; var[j+1]=x;
				int t=val[j]; val[j]=val[j+1]; val[j+1]=t;
			}
			if(!first) System.out.println();
			else first=false;
			for(int i=0;i<n;i++) System.out.printf("%s = %d\n",var[i],val[i]);
		}
	}
}
