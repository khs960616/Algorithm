/*
https://school.programmers.co.kr/learn/courses/30/lessons/12902
3*n 타일링
---
DP
*/

class Solution {
    private static final int MOD = 1000000007;
    
    public int solution(int n) {
        if(n%2 != 0) return 0;
        
        long[] answer = new long[5001]; //중간 연산의 결과가 최대 30억을 넘어갈 수 있으므로 long
        answer[0] = 1;
        answer[2] = 3;
        
        for(int i=4; i<=n; i+=2) {
            answer[i] += (answer[i-2] * answer[2]) % MOD; 
            for(int j=i-4; j>=0; j-=2) {
                answer[i] += ((answer[j] * 2) % MOD);
            }
            answer[i] %= MOD;
        }
        return (int) answer[n];
    }
}
