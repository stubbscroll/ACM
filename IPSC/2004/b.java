/* solution to bishops, both inputs.
   algorithm: output 2n-2, except when n=1, for which the output is 1. */

import java.math.*;
import java.util.*;

public class b {
	public static void main(String a[]) {
		Scanner sc=new Scanner(System.in);
		while(sc.hasNext()) {
			BigInteger n=new BigInteger(sc.next());
			if(n.equals(BigInteger.ONE)) System.out.println("1");
			else System.out.println(n.add(n).subtract(BigInteger.valueOf(2)));
		}
	}
}