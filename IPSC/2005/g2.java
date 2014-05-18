/* solution to gears in action, hard input
   algorithm: chinese remainder theorem.
   java because i assumed answers could be large */

import java.math.*;
import java.util.*;

public class g2 {
	public static void main(String a[]) {
		new g2().go();
	}
	
	Scanner sc;
	int size[],goal[],size2[],goal2[];
	int n,n2;
	TreeSet<Integer> primes;

	int gcd(int a,int b) {
		if(b==0) return a;
		return gcd(b,a%b);
	}

	void addprime(int p) {
		primes.add(p);
	}

	void factor(int n) {
		if(n%2==0) {
			n>>=1;
			addprime(2);
			while(n%2==0) n>>=1;
		}
		for(int i=3;i*i<=n;i+=2) if(n%i==0) {
			addprime(i);
			n/=i;
			while(n%i==0) n/=i;
		}
		if(n>1) addprime(n);
	}

	long inverse(long a,long mod) {
		long b=mod,x=0,y=1,t,q,lastx=1,lasty=0;
		while(b!=0) {
			q=a/b;
			t=a; a=b; b=t%b;
			t=x; x=lastx-q*x; lastx=t;
			t=y; y=lasty-q*y; lasty=t;
		}
		return a==1?(lastx%mod+mod)%mod:0;
	}

	/* solve a set of modular equations using chinese remainder theorem */
	/* n: number of equations of the form x = a[i] mod b[i] */
	BigInteger chinese(int n,int a[],int b[]) {
		BigInteger N=BigInteger.ONE,x=BigInteger.ZERO;
		for(int i=0;i<n;i++) N=N.multiply(BigInteger.valueOf(b[i]));
		for(int i=0;i<n;i++) {
			// x=(x+a[i]*N/b[i]*inverse(N/b[i]%b[i],b[i]))%N;
			BigInteger bi=BigInteger.valueOf(b[i]);
			BigInteger ai=BigInteger.valueOf(a[i]);
			BigInteger inv1=N.divide(bi).mod(bi);
			BigInteger inv=BigInteger.valueOf(inverse(Long.parseLong(inv1.toString()),b[i]));
			BigInteger a1=ai.multiply(N).divide(bi);
			x=x.add(a1.multiply(inv)).mod(N);
		}
		return x;
	}

	void solve() {
		n=sc.nextInt();
		size=new int[n];
		goal=new int[n];
		for(int i=0;i<n;i++) {
			size[i]=sc.nextInt();
			goal[i]=sc.nextInt();
			if((i&1)==1) goal[i]=(size[i]-goal[i])%size[i];
		}
		/* detect impossibility */
		for(int i=0;i<n-1;i++) for(int j=i+1;j<n;j++) {
			int g=gcd(size[i],size[j]);
			if(g>1 && goal[i]%g!=goal[j]%g) {
				System.out.println("Impossible");
				return;
			}
		}
		/* transform system to one that is pairwise coprime */
		primes=new TreeSet<Integer>();
		for(int i=0;i<n;i++) factor(size[i]);
		n2=primes.size();
		size2=new int[n2];
		goal2=new int[n2];
		int ix=0;
		for(int p:primes) {
			int eq=-1,hi=1;
			for(int j=0;j<n;j++) {
				int cur=1,g=size[j];
				while(g%p==0) { g/=p; cur*=p; }
				if(hi<cur) { hi=cur; eq=goal[j]%hi; }
			}
			size2[ix]=hi;
			goal2[ix++]=eq;
		}
		System.out.println(chinese(n2,goal2,size2));
	}
	
	void go() {
		sc=new Scanner(System.in);
		int T=sc.nextInt();
		while(T-->0) solve();
	}
}
