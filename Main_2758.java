import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

/*
https://www.acmicpc.net/problem/2758
로또
dp
*/

public class Main_2758 {
	
	private static int T, N, M;
	private static long[][] dp = new long[11][2001]; // dp[i][j] : 선택한 길이가 i이며, 마지막 선택한 번호가 j인 로또 번호의 갯수
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		
		for(int i=1; i<11; ++i) Arrays.fill(dp[i], -1);
		
		for(int i=0; i<T; ++i) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			
			long ret = 0;
			for(int j=M; j>=1; --j) ret += getLottoCnt(N, j); 
			System.out.println(ret);
		}
	}
  
	private static long getLottoCnt(int n, int m) {
		if(n == 1) dp[n][m] = 1;
		if(dp[n][m] != -1) return dp[n][m];
		
		dp[n][m] = 0;
		for(int i=m/2; i>=1; --i) {
			dp[n][m] += getLottoCnt(n-1, i);
		}
		return dp[n][m];
	}
}
