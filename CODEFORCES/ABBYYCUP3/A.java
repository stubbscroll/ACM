/* accepted on A1, timeout on A2 */

import java.math.*;
import java.io.*;
import java.util.*;

public class A {
  public static void main(String[]a) {
    new A().go();
  }
  void go() {
    BigInteger ans=BigInteger.ONE;
    BigInteger nine=BigInteger.valueOf(9);
    BigInteger ten=BigInteger.valueOf(10);
    Scanner sc=new Scanner(System.in);
    String s=sc.next();
    boolean seen[]=new boolean[10];
    int l=s.length(),mul=10;
    for(int i=0;i<l;i++) {
      char c=s.charAt(i);
      if(c=='?') {
        if(i==0) ans=ans.multiply(nine);
        else ans=ans.multiply(ten);
      } else if(c>='A' && c<='Z') {
        int ix=(int)c-(int)'A';
        if(seen[ix]) continue;
        if(i==0) ans=ans.multiply(BigInteger.valueOf(mul-1));
        else ans=ans.multiply(BigInteger.valueOf(mul));
        mul--;
        seen[ix]=true;
      }
    }
    System.out.println(ans);
  }
}
