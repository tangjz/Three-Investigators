import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main {
	public static void main(String[] args) throws IOException {
		int[][] c = new int[27][27];
		for(int i = 0; i <= 26; ++i) {
			c[i][0] = c[i][i] = 1;
			for(int j = 1; j < i; ++j)
				c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
		Scanner cin = new Scanner(System.in);
		int t = cin.nextInt();
		while(t-- > 0) {
			int n = cin.nextInt();
			int[] sa = new int[n + 1], rk = new int[n + 1];
			for(int i = 0; i < n; ++i) {
				sa[i] = cin.nextInt();
				rk[--sa[i]] = i;
			}
			rk[n] = -1;
			int low = 1;
			for(int i = 1; i < n; ++i)
				if(rk[sa[i - 1] + 1] > rk[sa[i] + 1])
					++low;
			BigInteger coeff = BigInteger.ONE, ans = BigInteger.ZERO;
			for(int i = 0; i + low <= 26 && i + low <= n; ++i) {
				ans = ans.add(coeff.multiply(BigInteger.valueOf(c[26][i + low])));
				if(i + 1 + low <= 26 && i + 1 + low <= n)
					coeff = coeff.multiply(BigInteger.valueOf(n - low - i)).divide(BigInteger.valueOf(i + 1));
			}
			System.out.println(ans);
		}
		cin.close();
	}
}
