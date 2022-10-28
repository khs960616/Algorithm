#include <bits/stdc++.h>
#define HORIZONTAL 0
#define VERTICAL 1
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/60063
  2020 KAKAO BLIND RECRUITMENT
  블록 이동하기
  ---
  bfs, 복잡한 구현
  
  특정 좌표에서 로봇이 할 수 있는 operation을 정의한다.
    1. 상하좌우 이동
      - 현재 로봇의 두 좌표를 상하좌우로 이동시킬 수 있는지 여부를 체크한다. 
        (만일 두 좌표중 하나라도 벽에 막혀있다면 해당 칸으로는 움직일 수 없다.)
    2. 로봇의 좌표중 하나를 축으로 회전
      - 회전축을 기준으로, 회전축의 대각선 방향의 칸과, 회전 후 다른 좌표가 위치해야될 위치가 0인지 검사한다.
      - 회전축을 기준으로 각각 2가지 방향을 가질 수 있다.
      
   
   따라서 bfs를 통해 queue에 들어간 하나의 robot은 총 8가지의 상태변화를 가진다.
   상, 하, 좌, 우 이동 (4가지) 특정 축을 기준으로 회전(4가지)
   
   회전과 평행 이동은 모두 cost가 1로 동일하므로, 최단 경로를 구하기 위해서 bfs를 사용한다. 
*/
int N = 0;
vector<pair<int, int> > dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
bool is_visit[101][101][2];
bool is_valid(int y, int x) {
    return y>=0 && y<N && x>=0 && x<N;
}

struct Robot {
    int y, x;
    int cost;
    int state;
};

void insert_horizontal_rotate(queue<Robot>& q, 
                              vector<vector<int>>& board,
                              int y, int x, int cost,
                              int add_y) {

    if(is_valid(y, x-1) && is_valid(y+add_y, x-1)) {
        if(board[y][x-1] == 0 && board[y+add_y][x-1] == 0) {
            if(!is_visit[y][x-1][HORIZONTAL]) {
                is_visit[y][x-1][HORIZONTAL] = true;
                q.push({y, x-1, cost+1, HORIZONTAL});
            }
        }
    }
    
    if(is_valid(y, x+1) && is_valid(y+add_y, x+1)) {
        if(board[y][x+1] == 0 && board[y+add_y][x+1] == 0) {
            if(!is_visit[y][x][HORIZONTAL]) {
                is_visit[y][x][HORIZONTAL] = true;
                q.push({y, x, cost+1, HORIZONTAL});
            }
        }
    } 
}

void insert_vertical_rotate(queue<Robot>& q, 
                            vector<vector<int>>& board,
                            int y, int x, int cost,
                            int add_x) {
    
    if(is_valid(y+1, x+add_x) && is_valid(y+1, x)) {
        if(board[y+1][x+add_x] == 0 && board[y+1][x] == 0) {
            if(!is_visit[y][x][VERTICAL]) {
                is_visit[y][x][VERTICAL] = true;
                q.push({y, x, cost+1, VERTICAL});
            }
        }
    }
    
    if(is_valid(y-1, x+add_x) && is_valid(y-1, x)) {
        if(board[y-1][x+add_x] == 0 && board[y-1][x] == 0) {
            if(!is_visit[y-1][x][VERTICAL]) {
                is_visit[y-1][x][VERTICAL] = true;
                q.push({y-1, x, cost+1, VERTICAL});
            }
        }
    }
}

int solution(vector<vector<int>> board) {
    N = board.size();
    int answer = 0;
    
    queue<Robot> q;
    q.push({0, 0, 0, HORIZONTAL});
    is_visit[0][0][HORIZONTAL] = true;
    
    while(!q.empty()) {
        Robot r = q.front();
        q.pop();
        
        int y1 = r.y, x1 = r.x;
        int y2 = r.y, x2 = r.x;
        if(r.state == HORIZONTAL) x2+=1;
        else y2+=1;
        
        if(y2 == N-1 &&  x2 == N-1) return r.cost;

        for(pair<int, int> dir: dirs) {
            int ny1 = y1+dir.first, ny2 = y2+dir.first;
            int nx1 = x1+dir.second, nx2 = x2+dir.second;
            if(!is_valid(ny1, nx1) || !is_valid(ny2, nx2)) continue;
            if(board[ny1][nx1] == 1 || board[ny2][nx2] == 1) continue;
            if(is_visit[ny1][nx1][r.state]) continue;
            is_visit[ny1][nx1][r.state] = true;
            q.push({ny1, nx1, r.cost+1, r.state});
        }
        
        if(r.state == HORIZONTAL) {
            insert_vertical_rotate(q, board, y1, x1, r.cost, 1);
            insert_vertical_rotate(q, board, y2, x2, r.cost, -1);
        } else {
            insert_horizontal_rotate(q, board, y1, x1, r.cost, 1);
            insert_horizontal_rotate(q, board, y2, x2, r.cost, -1);
        }
    }
    return -1;
}
