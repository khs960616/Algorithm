#include <bits/stdc++.h>
#define INF 1000000
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/67259
  2020 카카오 인턴십
  경주로 건설 
  ---
  DP, BFS
  
  DP[i][j][k]  : k방향을 바라보는 상태로 (i, j)번째 블록에 도착했을 때의 최소비용
  
  처음에는 DP[i][j]로 잡고 문제를 풀었는데, 이 경우 항상 최적해를 보장하지 않는다. 
  (코너의 경우 500의 추가적인 cost가 들기 때문에, 현재 최적해가 아니더라도, 바라보는 방향에 따라 다음위치에서는 최적해가 될 수 있는 케이스가 존재함)
  따라서 방향에 따라 최적해를 구분하면 이러한 예외가 사라지게 된다.
  
*/
int board_size = 0;
int dp[35][35][4];
vector<pair<int, int> > dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool is_valid(int y, int x) {
    return (y>=0&& y<board_size) && (x>=0 && x<board_size);
}

bool is_conner(int prev_dir, int current_dir) {
    return ((prev_dir+current_dir) % 2 != 0);
}

int calc_next_cost(int prev_dir, int current_dir, int prev_cost) {
    int cost = prev_cost + 100;
    if(is_conner(prev_dir, current_dir)) cost+=500;
    return cost;
}

void init_dp(int board_size) {
    for(int i=0; i<board_size; ++i) {
        for(int j=0; j<board_size; ++j) {
            for(int k=0; k<4; ++k) {
                dp[i][j][k] = INF;
            }
        }
    }
    
    for(int i=0; i<4; ++i) dp[0][0][i] = 0;
}

int solution(vector<vector<int>> board) {
    board_size = board.size();
    init_dp(board_size);
    
    queue<tuple<int, int, int, int> > q;
    q.emplace(0, 0, 0, 1);
    q.emplace(0, 0, 0, 2);
    
    while(!q.empty()) {
        auto [y, x, cost, prev_dir] = q.front();
        q.pop();
        
        for(int i=0; i<4; ++i) {
            int next_y = y + dirs[i].first;
            int next_x = x + dirs[i].second;
            
            if(!is_valid(next_y, next_x)) continue;
            if(board[next_y][next_x] == 1) continue;
            
            int next_cost = calc_next_cost(prev_dir, i, cost); 
            if(dp[next_y][next_x][i] > next_cost) {
                dp[next_y][next_x][i] = min(dp[next_y][next_x][i], next_cost);
                q.emplace(next_y, next_x, next_cost, i);
            }
        }
    }
    
    return *min_element(dp[board_size-1][board_size-1], dp[board_size-1][board_size-1]+4);
}
