import java.io.BufferedReader;
import java.io.InputStreamReader;

/*
https://www.acmicpc.net/problem/9252
LCS2
dp, 구현
---
*/
public class BOJ_9252 {
	
	private static int[][] dp;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String s1 = br.readLine(), s2 = br.readLine();
		int len1 = s1.length(), len2 = s2.length();
		
		dp = new int[len2][len1];
		if(s1.charAt(0) == s2.charAt(0)) dp[0][0] = 1;
		
		for(int i=1; i<len1; ++i) {
			int value = (s2.charAt(0) == s1.charAt(i)) ? 1 : 0;
			dp[0][i] = Math.max(dp[0][i-1], value);
		}
		for(int i=1; i<len2; ++i) {
			int value = (s1.charAt(0) == s2.charAt(i)) ? 1 : 0;
			dp[i][0] = Math.max(dp[i-1][0], value);
		}
		
		for(int i=1; i<len2; ++i) {
			for(int j=1; j<len1; ++j) {
				dp[i][j] = Math.max(dp[i-1][j], dp[i][j-1]);
				if(s1.charAt(j) == s2.charAt(i)) {
					dp[i][j] = Math.max(dp[i][j], dp[i-1][j-1]+1);
				}
			}
		}
		
		System.out.println(dp[len2-1][len1-1]);
		
		if(dp[len2-1][len1-1] != 0) {
			StringBuilder sb = new StringBuilder();
			
			int prevValue = dp[len2-1][len1-1];
			int y = len2-1, x = len1-1;
			
			while(prevValue != 0 && (y>=0 && x>=0)) {
				while(y>0 && dp[y-1][x] == prevValue) --y;
				while(x>0 && dp[y][x-1] == prevValue) --x;
				sb.append(s1.charAt(x--));
				
				if(x >= 0) prevValue = dp[y][x];
			}
			
			if(x>=0 && y>=0 && dp[y][x]!=0) {
				while(y>0 && dp[y-1][x] == prevValue) --y;
				while(x>0 && dp[y][x-1] == prevValue) --x;
				sb.append(s1.charAt(x));
			}
			
			System.out.println(sb.reverse().toString());
		}
	}
}
