/* solution to exact? approximate!
   algorithm: naive binary search in stern-brocot tree. */

import java.math.*;
import java.util.*;

public class e2_tle {
	public static void main(String a[]) {
		new e2_tle().go();
	}
	void go() {
		Scanner sc=new Scanner(System.in);
		while(sc.hasNext()) solve(sc.next());
	}
	/* return result of A/B compared to C/D: -1 smaller, 0 equal, 1 equal */
	int comparefrac(BigInteger A,BigInteger B,BigInteger C,BigInteger D) {
		return A.multiply(D).compareTo(B.multiply(C));
	}
	/* return 1 if A/B is in interval [C/D, E/F) */
	boolean isok(BigInteger A,BigInteger B,BigInteger C,BigInteger D,BigInteger E,BigInteger F) {
		return comparefrac(A,B,C,D)>-1 && comparefrac(A,B,E,F)<0;
	}
	void solve(String s) {
		/* X/Y is input fraction */
		BigInteger X=new BigInteger(s.substring(2));
		BigInteger Y=BigInteger.valueOf(10);
		Y=Y.pow(s.length()-2);
		BigInteger ten=BigInteger.valueOf(10);
		BigInteger five=BigInteger.valueOf(5);
		/* desired fraction should be in [loX/loY, hiX/hiY) */
		BigInteger loX=X.multiply(ten).subtract(five);
		BigInteger loY=Y.multiply(ten);
		BigInteger hiX=X.multiply(ten).add(five);
		BigInteger hiY=Y.multiply(ten);
		/* naive binary search! A/B lower limit, C/D upper limit, E/F middle */
		BigInteger A=BigInteger.ZERO;
		BigInteger B=BigInteger.ONE;
		BigInteger C=BigInteger.ONE;
		BigInteger D=BigInteger.ONE;
		BigInteger E,F;
		while(true) {
			E=A.add(C);
			F=B.add(D);
			if(isok(E,F,loX,loY,hiX,hiY)) break;
			if(comparefrac(E,F,loX,loY)<0) { A=E; B=F; }
			else if(comparefrac(E,F,hiX,hiY)>=0) { C=E; D=F; }
		}
		System.out.println(E+" "+F);
	}
}
