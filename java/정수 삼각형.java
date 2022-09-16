import java.util.*;
import java.util.stream.*;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/43105
정수 삼각형
--
dp
*/
class Solution {
    public int solution(int[][] triangle) {
        int[][] dp = new int[triangle.length][triangle.length]; //dp[0][0] = 트리의 element (0,0)에서 시작하여 트리의 끝까지 원소를 잇는 경로 중 최대값
        for(int i=0; i<triangle.length; ++i) {
            dp[triangle.length-1][i] = triangle[triangle.length-1][i];
        }
        
        for(int i=triangle.length-2; i>=0; --i) {
            for(int j=0; j<i+1; ++j) {
                int maxChild = Math.max(dp[i+1][j], dp[i+1][j+1]);
                dp[i][j] = triangle[i][j] + maxChild;
            }
        }
        return dp[0][0];
    }
}
