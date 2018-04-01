
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.math.BigInteger;
import java.util.Scanner;

/**
 * Created by Huang on 2017/10/5.
 */
public class StrangeDigits {
    static int len = 0;
    static boolean ok[] = new boolean[39];
    static int a[] = new int[400];
    static int dp[][] = new int[400][39];
    static int from_j[][] = new int[400][39];
    static int from_k[][] = new int[400][39];

    public static void output(PrintStream out, int i, int j, boolean flag){
        if(i == 0) return;
        if(from_k[i][j] > 0) flag = true;
        if(flag){
            if(from_k[i][j] > 9) out.printf("%c", 'A' + (from_k[i][j] - 10));
            else out.printf("%c", '0' + from_k[i][j]);
        }
        output(out, i - 1, from_j[i][j], flag);
    }

    public static void main(String[] args) throws FileNotFoundException {
        File input_file = new File("digits.in");
        Scanner cin = new Scanner(input_file);
        int b = cin.nextInt();
        String str = cin.next();
        for(int i = 0; i < str.length(); ++i)
            if(str.charAt(i) <= '9') ok[str.charAt(i) - '0'] = true;
            else{
                ok[str.charAt(i) - 'A' + 10] = true;
            }

        String nstr = cin.next();

        BigInteger n = new BigInteger(nstr);

        while(!n.equals(BigInteger.ZERO)){
            a[++len] = n.mod(BigInteger.valueOf(b)).intValue();
            n = n.divide(BigInteger.valueOf(b));
        }

        //System.out.println(len);
        dp[0][0] = 1;
        for(int i = 1; i <= len; ++i){
            for(int j = 0; j < 36; ++j) {
                for(int k = 0; k < 36; ++k)
                    if(ok[k]) {
                        int tmp = (j + k) % b, up = (j + k) / b;
                        if (tmp != a[i]) continue;
                        dp[i][up] += dp[i - 1][j];
                        dp[i][up] = Math.min(dp[i][up], 2);
                        if (dp[i - 1][j] > 0) {
                            from_j[i][up] = j;
                            from_k[i][up] = k;
                        }
                    }
            }
        }

        File output_file = new File("digits.out");
        PrintStream out = new PrintStream(output_file);
        if(dp[len][0] == 0){
            out.println("Impossible");
        }else{
            if(dp[len][0] > 1) out.println("Ambiguous");
            else out.println("Unique");
            output(out, len, 0, false);
        }
    }
}
