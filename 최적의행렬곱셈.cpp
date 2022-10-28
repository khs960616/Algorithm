#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12942
  최적의 행렬 곱셈 
  DP
  ---
  점화식을 풀면 되는 well known한 dp문제 유형 
  (i<=k<j)
  dp[i][j] = min(dp[i][j], dp[i][k]+dp[k+1][j] + v[i][0]*v[k][1]*v[j][1]);
  
  dp[i][k] : i번째 행렬부터 k번째 행렬까지 곱하는데 필요한 최소 비용 
  dp[k+1][j] : k+1번째 행렬부터 j번째 행렬까지 곱하는데 필요한 최소비용
  v[i][0]*v[k][1]*v[j][1] : dp[i][k]와 dp[k+1][j] 두 행렬을 곱하는데 필요한 비용 
*/

int dp[201][201];
int solution(vector<vector<int>> v) {
    int answer = 0;
    int n = v.size();
    
    for(int size = 1; size<n; ++size) {
        for(int i=0; (i+size) < n; ++i) {
            int j = i+size;
            dp[i][j] = INT_MAX;
            
            for(int k=i; k<j; ++k) {
                int current_cost = v[i][0] * v[k][1] * v[j][1];
                int prev_cost = dp[i][k] + dp[k+1][j];
                dp[i][j] = min(dp[i][j], prev_cost + current_cost);
            }
        }
    } 

    return dp[0][n-1];
}
