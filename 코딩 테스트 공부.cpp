#include <bits/stdc++.h>
#define INF 100000
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/118668
  2022 KAKAO TECH INTERNSHIP
  코딩테스트 연습
  ---
  DP 최단거리, 브루트포스 
*/
int max_required_alp = INT_MIN, max_required_cop = INT_MIN;

void get_max_required(vector<vector<int>> problems) {
    for(vector<int> problem: problems) {
        max_required_alp = max(max_required_alp, problem[0]);
        max_required_cop = max(max_required_cop, problem[1]);
    }
}

int solution(int alp, int cop, vector<vector<int>> problems) {
    get_max_required(problems);
    
    vector<vector<int> > dp(max_required_alp+1, vector<int>(max_required_cop+1, INF));
    int start_alp = min(alp, max_required_alp);
    int start_cop = min(cop, max_required_cop);
    dp[start_alp][start_cop] = 0;
    
    for(int i = start_alp; i<=max_required_alp; ++i) {
        for(int j = start_cop; j<=max_required_cop; ++j) {
            if(i < max_required_alp) {
                dp[i+1][j] = min(dp[i+1][j], dp[i][j]+1);
            }
            if(j < max_required_cop) {
                dp[i][j+1] = min(dp[i][j+1], dp[i][j]+1);
            }
            
            for(vector<int> problem: problems) {
                if(problem[0] > i || problem[1] > j) continue;
                int next_alp = min(max_required_alp, (i + problem[2]));
                int next_cop = min(max_required_cop, (j + problem[3]));
                dp[next_alp][next_cop] = min(dp[next_alp][next_cop], dp[i][j]+problem[4]);
            }
        }
    }
    
    return dp[max_required_alp][max_required_cop];
}
