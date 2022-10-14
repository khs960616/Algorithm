#include <bits/stdc++.h>
#define FREE 0
#define BLOCK 1
#define NO_ROTATE 2
#define EAST 0
#define SOUTH 1
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/1832
  2017 카카오코드 예선
  보행자 천국 
  ----
  DP 
  각 블록에 도착한 갯수와, 도착했을 떄 당시의 방향을 저장해둔 상태로 기록해두면 된다.
  
  삽질 1) 
  city_map 관련해서 increse_by_left_block, increse_by_topside_block의 인자로 vector<vector<int>> city_map넘겼는데
  래퍼런스로 안넘겨서 복사 생성되는 경우 시간초과 발생
  일반적으로 dfs등의 경우 별도로 값을 유지하고 되돌리는 것이 귀찮아 함수 매개변수를 통한 복사생성자를 많이 쓰는 편인데,
  해당 cost도 무시하면 안될듯.. 
*/

int MOD = 20170805;
int dp[500][500][2];
vector<vector<int>> city_ref; // 그냥 이렇게 안하고 래퍼런스 변수로 넘겨도 됬을듯.

void insert_inital_value(int m, int n) {
    for(int i=1; i<m; ++i) {
        if(city_ref[i][0] == BLOCK) break;
        dp[i][0][SOUTH] = 1; 
    }
    
    for(int i=1; i<n; ++i) {
        if(city_ref[0][i] == BLOCK) break;
        dp[0][i][EAST] = 1;
    }
}

void increse_by_left_block(int current_y, int current_x) {
    dp[current_y][current_x][EAST] = (dp[current_y][current_x][EAST]+dp[current_y][current_x-1][EAST]) % MOD;
    if(city_ref[current_y][current_x-1] == FREE) {
        dp[current_y][current_x][EAST] = (dp[current_y][current_x][EAST]+dp[current_y][current_x-1][SOUTH]) % MOD;
    }
}

void increse_by_topside_block(int current_y, int current_x) {
    dp[current_y][current_x][SOUTH] = (dp[current_y][current_x][SOUTH]+dp[current_y-1][current_x][SOUTH]) % MOD;
    if(city_ref[current_y-1][current_x] == FREE) {
        dp[current_y][current_x][SOUTH] = (dp[current_y][current_x][SOUTH]+dp[current_y-1][current_x][EAST]) % MOD;
    }
}

int solution(int m, int n, vector<vector<int>> city_map) {
    if(m&n == 1) return 1;
    memset(dp, 0, sizeof(dp));
    city_ref = city_map;
    
    insert_inital_value(m, n);
    for(int i=1; i<m; ++i) {
        for(int j=1; j<n; ++j) {
            if(city_map[i][j] == BLOCK) continue; // BLOCK인 경우 모든 값이 초기상태인 0이므로 다른 값 계산에 영향이 없다.
            increse_by_left_block(i, j);
            increse_by_topside_block(i, j);
        }
    }
    return (dp[m-1][n-1][0] + dp[m-1][n-1][1]) % MOD;
}
