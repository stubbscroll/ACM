/* solution to polly wanna cracker, both input
   java because of big numbers bleh */

import java.math.*;
import java.util.*;

public class p {
	public static void main(String a[]) {
		new p().go();
	}
	void go() {
		Scanner sc=new Scanner(System.in);
		int first=1;
		while(sc.hasNext()) {
			BigInteger p=new BigInteger(sc.next());
			BigInteger n=new BigInteger(sc.next());
			if(first<1) System.out.println();
			else first=0;
			BigInteger remain=n.mod(p);
			if(!remain.equals(BigInteger.ZERO)) System.out.println(remain+" "+n.divide(p).add(BigInteger.ONE));
			System.out.println(p.subtract(remain)+" "+n.divide(p));
		}
	}
}
