import java.util.Scanner;
import java.math.BigInteger;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int k = scanner.nextInt();

        System.out.println(solve(n, k));
    }

    private static BigInteger solve(int N, int K) {
        BigInteger[][] dp = new BigInteger[101][1001];
        for (int i = 0; i <= K; i++) {
            for (int j = 0; j <= N; j++) {
                dp[i][j] = BigInteger.ZERO;
            }
        }
        dp[0][0] = BigInteger.ONE;

        for (int i = 1; i <= K; i++) {
            for (int j = 0; j <= N; j++) {
                if (j >= i) {
                    dp[i][j] = dp[i-1][j].add(dp[i][j-i]);
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        return dp[K][N];
    }
}


