import java.io.File;
        import java.io.FileNotFoundException;
        import java.io.PrintStream;
        import java.math.BigInteger;
        import java.util.Scanner;

/**
 * Created by Huang on 2017/10/5.
 */
public class RSA {
    public static void main(String[] args) throws FileNotFoundException {
        File input_file = new File("rsa.in");
        Scanner cin = new Scanner(input_file);
        File output_file = new File("rsa.out");
        PrintStream out = new PrintStream(output_file);

        String str = cin.next();
        BigInteger n = new BigInteger(str);
        str = cin.next();
        BigInteger a = new BigInteger(str);
        str = cin.next();
        BigInteger b = new BigInteger(str);

        BigInteger p = a.multiply(BigInteger.valueOf(2)).add(b).subtract(BigInteger.ONE);
        BigInteger q = b.subtract(a).add(BigInteger.valueOf(2));
        while(p.compareTo(BigInteger.ZERO) < 0) p = p.add(n);
        p = p.mod(n);
        while(q.compareTo(BigInteger.ZERO) < 0) q = q.add(n);
        if(q.compareTo(BigInteger.ZERO) == 0){
            out.println(-1);
            return;
        }
        q = q.mod(n);
        try {
            q = q.modInverse(n);
        }catch (Exception E){
            out.println(-1);
            return;
        }

        BigInteger m = p.multiply(q).mod(n);

        if(!a.equals(m.multiply(m).mod(n).multiply(m).mod(n))) out.println(-1);
        else{
            BigInteger mm = m.add(BigInteger.ONE);
            if(!b.equals(mm.multiply(mm).mod(n).multiply(mm).mod(n))) out.println(-1);
            else out.println(m);
        }
    }
}
