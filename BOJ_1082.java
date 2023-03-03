package algorithm;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

/*
https://www.acmicpc.net/problem/1082
방 번호
dp, 큰 수 처리 
---
배낭문제와 동일한 형태지만 큰 수를 처리해야하므로 String으로 처리 
*/
public class BOJ_1082 {
	
	private static int N, M;
	private static int[] prices;
	private static String[][] dp; // dp[i][j] i개의 인덱스까지의 아이템이 있을때, 잔액이 j만큼 남았을 때, 만들 수 있는 방번호 최댓값
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		
		prices = new int[N];
		StringTokenizer st = new StringTokenizer(br.readLine());
		for(int i=0; i<N; ++i) {
			prices[i] = Integer.parseInt(st.nextToken());
		}
		
		M = Integer.parseInt(br.readLine());
		
		dp = new String[N][M+1];
		for(int i=0; i<N; ++i) Arrays.fill(dp[i], "");
		
		int quo = 0;
		StringBuilder sb = new StringBuilder("");
		
		for(int i=0; i<=M; ++i) {
			if(quo != (i/prices[0])) {
				quo = (i/prices[0]);
				sb.append("0");
			}
			dp[0][i] = sb.toString();
		}
		
		for(int i=1; i<N; ++i) {
			for(int j=0; j<=M; ++j) {
				for(int k=0; k<i; ++k) {
					sb = new StringBuilder("");
					for(int l=0; l<=j; l+=prices[i]) {
						dp[i][j] = max(dp[i][j], sb.toString()+dp[k][j-l]);
						sb.append(i);
					}
				}
			}
		}
		
		System.out.println(isAllZero(dp[N-1][M])? "0" : dp[N-1][M]);
	}
	
	
	private static String max(String s1, String s2) {
		if(isAllZero(s1)) s1 = "0";
		if(isAllZero(s2)) s2 = "0";
		
		if(s1.length() == s2.length()) {
			for(int i=0; i<s1.length(); ++i) {
				int v1 = s1.charAt(i)-'0', v2 = s2.charAt(i)-'0';
				if(v1 == v2) continue;
				return v1 > v2 ? s1 : s2;
			}
		} 
		return s1.length()  > s2.length() ? s1 : s2;
	}
	
	private static boolean isAllZero(String s) {
		if(s.isEmpty()) return false;
		
		int len = s.length();
		for(int i=0; i<len; ++i) {
			if((s.charAt(i)-'0') != 0) return false;
		}
		return true;
	}
}
