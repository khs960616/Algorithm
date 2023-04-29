import java.util.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/154538
  숫자 변환하기
  DP
  --
     dp 점화식 
     dp[i] = min(dp[i-n], dp[i/2], dp[i/3]); 
     
     재귀 함수로 구현하는 경우 함수의 호출이 ^3으로 늘어난다.
     따라서 x=1, y=1_000_000 로 주어지는 경우 스택 overflow 발생 가능
     bottom up으루 구현하는 편이 간단한 문제 .
*/
class PG154538 {
  
    public int solution(int x, int y, int n) {
        int[] dp = new int[y+1];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[x] = 0;
        
        for(int i=x; i<=y; ++i) {
            
            if(dp[i] == Integer.MAX_VALUE) continue;
            if(i+n<=y) dp[i+n] = Math.min(dp[i+n], dp[i]+1);
            if(i*2<=y) dp[i*2] = Math.min(dp[i*2], dp[i]+1);
            if(i*3<=y) dp[i*3] = Math.min(dp[i*3], dp[i]+1);
        }
        return dp[y] == Integer.MAX_VALUE ? -1 : dp[y];
    }
}
