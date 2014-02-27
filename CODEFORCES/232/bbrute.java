/* brute force solution to B. just outputs all answers starting from n=2,
   not submittable as it doesn't read input */

import java.util.*;
import java.math.*;

public class bbrute {
	boolean isprime(int n) {
		if(n<4) return n>1;
		if((n&1)==0) return false;
		for(int i=3;i*i<=n;i+=2) if(n%i==0) return false;
		return true;
	}
	public static void main(String[]a) {
		new bbrute().go();
	}
	int find(int n,int d) {
		while(!isprime(n)) n+=d;
		return n;
	}
	void go() {
		BigInteger teller=BigInteger.ZERO;
		BigInteger nevner=BigInteger.ONE;
		
		for(int i=2;i<1000000001;i++) {
			int u=find(i,-1);
			int v=find(i+1,1);
			
			// a/b + c/d
			BigInteger a=teller;
			BigInteger b=nevner;
			BigInteger c=BigInteger.ONE;
			BigInteger d=BigInteger.valueOf(u).multiply(BigInteger.valueOf(v));
			teller=a.multiply(d).add(b.multiply(c));
			nevner=b.multiply(d);
			BigInteger g=teller.gcd(nevner);
			teller=teller.divide(g);
			nevner=nevner.divide(g);
			System.out.printf("%d: %d/%d\n",i,teller,nevner);
		}
	}
}
