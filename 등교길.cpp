#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/42898
  등굣길 
  ---
  DP
  중학교 최단경로 찾기 문제와 유사 
*/
int solution(int m, int n, vector<vector<int>> puddles) {
    // convert puddles info to vector
    vector<vector<int> > info(n, vector<int>(m, 0));
    for(vector<int> puddle: puddles) {
        info[puddle[1]-1][puddle[0]-1] = 1;
    }
    
    // init dp vector
    vector<vector<int> > dp(n, vector<int>(m, 0));
    for(int i=1; i<m; ++i) {
        if(info[0][i] == 1) break;
        dp[0][i] = 1;
    }
    for(int i=1; i<n; ++i) {
        if(info[i][0] == 1) break;
        dp[i][0] = 1;
    }
    
    for(int i=1; i<n; ++i) {
        for(int j=1; j<m; ++j) {
            if(info[i][j] == 1) continue;
            dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
        }
    }
    
    return dp[n-1][m-1] % MOD;
}
