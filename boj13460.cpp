#include <bits/stdc++.h>
#define HOLE 'O'
#define RED 0
#define BLUE 1
using namespace std;

/*
  https://www.acmicpc.net/problem/13460
  구슬탈출 
  ---
  시뮬레이션
  전체 브루트포스 돌려서 품
  
  BFS 방식으로 다시 풀어볼것
  ---
  구현할 때 고려했던 부분들
  
  1. 구슬을 움직임을 시뮬레이션 하는 기능 
     -> 한쪽 방향으로 구슬을 기울이는 경우 구슬은 해당 뱡향으로 이동 가능한만큼 이동하도록 구현한다.
     -> 이렇게 구현하는 경우 두 구슬 중 어떤 구슬을 먼저 움직이느냐에 따라 결과가 올바르게 나올 수도, 없을 수도 있다.
        
       두 구슬의 x좌표는 같고 y좌표가 다른 경우
           - 위쪽으로 기울이는 경우, 두 구슬 중 y좌표가 더 적은 구슬이 먼저 이동해야한다.
           - 아래쪽으로 기울이는 경우, 두 구슬 중 y좌표가 더 큰 구슬이 먼저 이동해야한다.
       
       즉, 이동하려는 방향의 벽과 더 가까운 구슬이 항상 먼저 움직여야한다. 
       그렇지 않다면, 실제로는 더 움직일 수 있음에도 불구하고, 다른 구슬에 막혀 움직일 수 없다고 판단하는 경우가 생기기 때문이다.
       
  2. 구슬이 hole에 빠지는 경우 답이 될 수 있는지 없는 지 여부를 판단해야한다.
    -> #####
       #ORB#   
       #####    예시로 다음의 board를 왼쪽으로 기울이는 경우, 두 구슬 모두 hole에 들어가지만, 파란색 구슬도 들어갔으므로 정답으로 인정될 수 없다.
       즉, 구슬이 1개만 들어간 경우, 그 구슬이 빨간 구슬인 경우가 구하고자하는 정답이다.
  
  3. BFS를 이용하면  불필요한 콜스택 호출이 줄어들 것으로 생각된다.  https://codingwell.tistory.com/55 
*/
int answer = INT_MAX;
int N, M;
vector<pair<int, int> > dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct Marble {
    int y, x;
    int type;
    Marble(){}
    Marble(int y, int x, int type) {
        this->y = y;
        this->x = x;
        this->type = type;
    }
};

void pre_process(vector<vector<char>>& board, vector<Marble>& marbles) {
    cin >> N >> M;
    board = vector<vector<char> >(N, vector<char>(M));

    for(int i=0; i<N; ++i) {
        for(int j=0; j<M; ++j) {
            cin >> board[i][j];
            if(board[i][j] == 'R') {
                marbles.emplace_back(i, j, RED);
            }
            if(board[i][j] == 'B') {
                marbles.emplace_back(i, j, BLUE);
            }
        }
    }
}

bool sort_x_less(Marble m1, Marble m2) {
    return m1.x < m2.x;
}

bool sort_x_greater(Marble m1, Marble m2) {
    return m1.x > m2.x;
}

bool sort_y_less(Marble m1, Marble m2) {
    return m1.y < m2.y;
}

bool sort_y_greater(Marble m1, Marble m2) {
    return m1.y > m2.y;
}

vector<Marble> put_priority_marble(vector<Marble> marbles, int dir_idx) {
    switch (dir_idx) {
        case 0:
            sort(marbles.begin(), marbles.end(), sort_y_less);
            break;
        case 1:
            sort(marbles.begin(), marbles.end(), sort_x_greater);
            break;
        case 2:
            sort(marbles.begin(), marbles.end(), sort_y_greater);
            break;
        case 3:
            sort(marbles.begin(), marbles.end(), sort_x_less);
            break;
    }
    return marbles;
}

bool move_and_check_fall_in_hole(vector<vector<char>>& board, 
                        Marble& marble, int idx) {
    
    int next_y = marble.y + dirs[idx].first;
    int next_x = marble.x + dirs[idx].second;

    while(board[next_y][next_x] == '.') {
        next_y = next_y + dirs[idx].first;
        next_x = next_x + dirs[idx].second;
    }

    bool ret = (board[next_y][next_x] == HOLE);
    board[marble.y][marble.x] = '.';
    marble.y = next_y, marble.x = next_x;

    if(!ret) {
        marble.y -= dirs[idx].first;
        marble.x -= dirs[idx].second;
        board[marble.y][marble.x] = (marble.type == RED) ? 'R' : 'B';
    }
    return ret;
}

void roll_back(vector<vector<char>>& board, vector<Marble>& marbles, vector<Marble>& current_marbles) {
    for(int j=0; j<2; ++j) {
        if(board[current_marbles[j].y][current_marbles[j].x] == 'R' || board[current_marbles[j].y][current_marbles[j].x] == 'B') {
            board[current_marbles[j].y][current_marbles[j].x] = '.';
        }
    }

    for(int j=0; j<2; ++j) {
        board[marbles[j].y][marbles[j].x] = (marbles[j].type == RED) ? 'R' : 'B';
    }
}

void solve(vector<vector<char>> board, vector<Marble> marbles, int cnt, int prev) {
    if(cnt >= 10) return;

    for(int i=0; i<4; ++i) {
        if(prev == i) continue;
        vector<Marble> current_marbles = put_priority_marble(marbles, i);
        vector<Marble> fall_marbles;
        
        for(int j=0; j<2; ++j) {
            if(move_and_check_fall_in_hole(board, current_marbles[j], i)) {
                fall_marbles.push_back(current_marbles[j]);
            }
        }

        if(fall_marbles.size() == 1 && fall_marbles[0].type == RED) {
            answer = min(answer, cnt+1);
            return;
        }
        solve(board, current_marbles, cnt+1, i);
        roll_back(board, marbles, current_marbles);
    }
}

int main() {
    vector<vector<char>> board;
    vector<Marble> marbles;
    pre_process(board, marbles);
    solve(board, marbles, 0, -1);

    if(answer == INT_MAX) answer = -1;
    cout << answer;
}
