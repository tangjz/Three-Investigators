import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.math.BigInteger;
import java.io.File;
import java.util.Scanner;

/**
 * Created by Huang on 2017/10/5.
 */
public class Permutations {



    public static BigInteger solve(Integer A[], int n){
        BigInteger ans = BigInteger.ZERO;
        boolean used[] = new boolean[n + 2];
        BigInteger fac[] = new BigInteger[n];
        fac[0] = BigInteger.ONE;
        for(int i = 1; i < n; ++i) fac[i] = fac[i - 1].multiply(BigInteger.valueOf(i));

        for(int i = 0; i < n; ++i) {
            int cnt = 0;
            for(int j = 1; j < A[i]; ++j)
                if (!used[j]) ++cnt;
            ans = ans.add(fac[n - i - 1].multiply(BigInteger.valueOf(cnt)));
            if(used[A[i]]) break;
            used[A[i]] = true;
        }

        return ans;
    }

    public static void main(String[] args) throws FileNotFoundException {
        File input_file = new File("permutations.in");
        Scanner cin = new Scanner(input_file);
        //Scanner cin = new Scanner(System.in);
        int n = cin.nextInt();
        Integer a[] = new Integer[n];
        Integer b[] = new Integer[n];

        BigInteger A = BigInteger.ZERO;
        BigInteger B = BigInteger.ZERO;
        BigInteger ten = BigInteger.TEN;
        for (int i = 0; i < n; ++i) {
            a[i] = cin.nextInt();
            //A = A.multiply(ten).add(BigInteger.valueOf(a[i]));
        }
        for (int i = 0; i < n; ++i) {
            b[i] = cin.nextInt();
            //B = B.multiply(ten).add(BigInteger.valueOf(b[i]));
        }

        b[n - 1] += 1;

        BigInteger ans = solve(b, n).subtract(solve(a, n));
        //System.out.println(ans.toString());

        File file = new File("permutations.out");

        PrintStream out = new PrintStream(file);

        out.printf(ans.toString());
    }
}
