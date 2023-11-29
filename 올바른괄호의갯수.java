/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12929#
  올바른 괄호의 갯수
  ---
  카탈란수 
*/

class Solution {
    public int solution(int n) {
        int[] dp = new int[16];
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        
        for(int i=3; i<=n; ++i) {
             for(int j=0; j<i; ++j) {
                dp[i] += (dp[j]*dp[i-1-j]);   
             }
        }
        return dp[n];
    }
}
