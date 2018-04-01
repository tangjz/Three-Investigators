import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Fraction {
	final BigInteger fz, fm;
	Fraction() {
		fz = BigInteger.ZERO;
		fm = BigInteger.ONE;
	}
	Fraction(BigInteger x, BigInteger y) {
		BigInteger r = x.abs().gcd(y);
		fz = x.divide(r);
		fm = y.divide(r);
	}
	Fraction(long x, long y) {
		this(BigInteger.valueOf(x), BigInteger.valueOf(y));
	}
	public String toString() {
		return fz.toString() + "/" + fm.toString();
	}
	Fraction add(Fraction t) {
		return new Fraction(fz.multiply(t.fm).add(t.fz.multiply(fm)), fm.multiply(t.fm));
	}
	Fraction subtract(Fraction t) {
		return new Fraction(fz.multiply(t.fm).subtract(t.fz.multiply(fm)), fm.multiply(t.fm));
	}
	Fraction multiply(Fraction t) {
		return new Fraction(fz.multiply(t.fz), fm.multiply(t.fm));
	}
	Fraction sqr() {
		return multiply(this);
	}
	int compareTo(Fraction t) {
		return subtract(t).fz.compareTo(BigInteger.ZERO);
	}
}
public class Main {
	static BigInteger det3(BigInteger[][] mat) {
		BigInteger ret = BigInteger.ZERO;
		ret = ret.add(mat[0][0].multiply(mat[1][1]).multiply(mat[2][2]));
		ret = ret.add(mat[0][1].multiply(mat[1][2]).multiply(mat[2][0]));
		ret = ret.add(mat[0][2].multiply(mat[1][0]).multiply(mat[2][1]));
		ret = ret.subtract(mat[0][2].multiply(mat[1][1]).multiply(mat[2][0]));
		ret = ret.subtract(mat[0][1].multiply(mat[1][0]).multiply(mat[2][2]));
		ret = ret.subtract(mat[0][0].multiply(mat[1][2]).multiply(mat[2][1]));
		return ret;
	}
	public static void main(String[] args) throws IOException {
		Scanner cin = new Scanner(System.in);
		int t = cin.nextInt();
		while(t-- > 0) {
			long[] x = new long[4], y = new long[4];
			for(int i = 0; i < 4; ++i) {
				x[i] = cin.nextLong();
				y[i] = cin.nextLong();
			}
			BigInteger[][] mat = new BigInteger[3][3];
			BigInteger fm;
			Fraction px, py;
			for(int i = 0; i < 3; ++i) {
				mat[i][0] = BigInteger.valueOf(x[i]);
				mat[i][1] = BigInteger.valueOf(y[i]);
				mat[i][2] = BigInteger.valueOf(1);
			}
			fm = det3(mat).shiftLeft(1);
			for(int i = 0; i < 3; ++i) {
				mat[i][0] = BigInteger.valueOf(x[i]);
				mat[i][1] = BigInteger.valueOf(y[i]);
				mat[i][2] = BigInteger.valueOf(1);
				mat[i][0] = mat[i][0].multiply(mat[i][0]).add(mat[i][1].multiply(mat[i][1]));
			}
			px = new Fraction(det3(mat), fm);
			for(int i = 0; i < 3; ++i) {
				mat[i][0] = BigInteger.valueOf(x[i]);
				mat[i][1] = BigInteger.valueOf(y[i]);
				mat[i][2] = BigInteger.valueOf(1);
				mat[i][1] = mat[i][0].multiply(mat[i][0]).add(mat[i][1].multiply(mat[i][1]));
			}
			py = new Fraction(det3(mat), fm);
			// System.out.printf("center: (%s, %s)\n", px, py);
			Fraction dis1 = px.subtract(new Fraction(x[0], 1)).sqr().add(py.subtract(new Fraction(y[0], 1)).sqr());
			Fraction dis2 = px.subtract(new Fraction(x[3], 1)).sqr().add(py.subtract(new Fraction(y[3], 1)).sqr());
			if(dis1.compareTo(dis2) < 0) {
				System.out.println("Accepted");
			} else {
				System.out.println("Rejected");
			}
		}
		cin.close();
	}
}
