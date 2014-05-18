/* solution to exact? approximate! hard input
   algorithm: binary search in stern-brocot tree, including speedup:
   try all powers of two of going left/right multiple times, so that we
   don't surpass desired interval.
   takes 144 seconds to solve hard input */

import java.math.*;
import java.util.*;

public class e2 {
	public static void main(String a[]) {
		new e2().go();
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
	int comparemul(BigInteger A,BigInteger B,BigInteger C,BigInteger D,BigInteger K,BigInteger X,BigInteger Y) {
		BigInteger U=A.add(C.multiply(K));
		BigInteger V=B.add(D.multiply(K));
		return comparefrac(U,V,X,Y);
	}
	void solve(String s) {
		/* X/Y is input fraction */
		BigInteger X=new BigInteger(s.substring(2));
		BigInteger Y=BigInteger.valueOf(10);
		Y=Y.pow(s.length()-2);
		BigInteger ten=BigInteger.valueOf(10);
		BigInteger five=BigInteger.valueOf(5);
		BigInteger two=BigInteger.valueOf(2);
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
//			System.out.printf("%s / %s\n",E,F);
			if(isok(E,F,loX,loY,hiX,hiY)) break;
			if(comparefrac(E,F,loX,loY)<0) {
				BigInteger K=BigInteger.ONE;
				while(true) {
					BigInteger K2=K.multiply(two);
					if(comparemul(A,B,C,D,K2,loX,loY)>=0) break;
					K=K2;
				}
				A=A.add(K.multiply(C));
				B=B.add(K.multiply(D));
			}
			else if(comparefrac(E,F,hiX,hiY)>=0) {
				BigInteger K=BigInteger.ONE;
				while(true) {
					BigInteger K2=K.multiply(two);
					if(comparemul(C,D,A,B,K2,hiX,hiY)<=0) break;
					K=K2;
				}
				C=C.add(K.multiply(A));
				D=D.add(K.multiply(B));
			}
		}
		System.out.println(E+" "+F);
	}
}
