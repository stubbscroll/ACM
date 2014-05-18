/* solution to ignore the garbage (hard).
   same algorithm as i.c, only with bigint and built-in radix conversion */

import java.math.*;
import java.util.*;

public class i2 {
	int a[]=new int[]{0,1,2,5,9,8,6};
	BigInteger seven=BigInteger.valueOf(7);

	public static void main(String a[]) {
		new i2().go();
	}

	void go() {
		Scanner sc=new Scanner(System.in);
		StringBuilder out=new StringBuilder();
		while(sc.hasNext()) {
			String r=new StringBuilder(new BigInteger(sc.next(),10).toString(7)).reverse().toString();
			for(char c:r.toCharArray()) out.append((char)(48+a[(int)c-48]));
			out.append('\n');
		}
		System.out.print(out);
	}
}
