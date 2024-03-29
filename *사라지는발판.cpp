#include <bits/stdc++.h>
#define EMPTY 0
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/92345
  2022 KAKAO BLIND RECRUITMENT
  사라지는 발판 c++
  REF:  https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/#%EB%AC%B8%EC%A0%9C-7-%EC%82%AC%EB%9D%BC%EC%A7%80%EB%8A%94-%EB%B0%9C%ED%8C%90
  ---
  브루트포스, 복잡한 재귀 구현 설계
  
  게임에서 자기 자신이 이길 수 있는 경우, 최소의 비용으로 승리하는 비용을, 지는 경우 최대의 비용으로 패배하는 경우를 출력한다.
  
  1. 현재 움직일 수 있는 블록이 존재하는지 검사한다. 만일 움직일 수 있는 블록이 없다면, 현재 사용자가 패배한 경우이며, 이 떄 이동한 거리는 0이 된다.
     (재귀 함수 기저)
  
  2. 현재 자기 자신의 칸이 비어있는 경우, 이전 상대의 차례 때 내 발판이 없어진 경우이며, 이 경우에도 현재 사용자가 패배한 경우이며, 이 때 이동한 거리는 0이 된다.
  
  3. 1,2에서 걸러지지 않았다면, 현재 사용자가 이길지 질지는 아직 정해지지 않은 상태이다.
     이 경우 움직일 수 있는 칸으로 움직인 후 상대에게 턴을 넘겨준다.
  
  4. 현재 턴을 가진 사용자가 움직일 수 없거나, 발판이 없어진 경우가 생길 떄 까지 3번의 과정을 반복한다.
  
  5. 각 함수에서 사용자가 움직일 수 있는 모든 칸으로 움직이고 나면, 사용자가 특정 칸으로 맨 처음 움직였을 때 반드시 이길 수 없는지 여부를 알 수 있게 된다.
     따라서 반드시 이길 수 있는 경우 최소의 비용을, 질 수 밖에 없는 경우 최대의 비용을 return한다.
*/

int row = 0, col = 0;
vector<pair<int, int> > dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool is_valid(int y, int x) {
    return (y>=0 && y<row) && (x>=0 && x<col);
}

bool can_move(vector<vector<int>>& board, int y, int x) {
    for(pair<int, int> dir: dirs) {
        int mov_y = y + dir.first;
        int mov_x = x + dir.second;
        if(!is_valid(mov_y, mov_x) || board[mov_y][mov_x] == EMPTY) continue;
        return true;
    }
    return false;
}

pair<bool, int> play(vector<vector<int>> board, 
                     int current_turn_y, int current_turn_x, 
                     int next_turn_y, int next_turn_x) {
    if(!can_move(board, current_turn_y, current_turn_x)) return {false, 0};
    
    bool is_win = false;
    int optimal_turn = 0;
    int max_turn = 0, min_turn = INT_MAX;
    
    if(board[current_turn_y][current_turn_x] != EMPTY) {
        board[current_turn_y][current_turn_x] = EMPTY; //현재 함수에서 어디로 이동하던, 현재 칸만 0으로 만들어주면 된다.
        
        for(pair<int, int> dir: dirs) {
            int mov_y = current_turn_y + dir.first;
            int mov_x = current_turn_x + dir.second;
            if(!is_valid(mov_y, mov_x) || board[mov_y][mov_x] == EMPTY) continue;

            pair<bool, int> result = play(board, next_turn_y, next_turn_x, mov_y, mov_x); 
// result에서 반환되는 이동 cost는 board[current_turn_y][current_turn_x]-> board[mov_y][mov_x]로 한칸 움직인 것은 포함되지 않은 비용이므로 1을 더해야한다.)
            if(!result.first) {
                is_win = true;
                min_turn = min(min_turn, result.second+1);
            } else {
                max_turn = max(max_turn, result.second+1);
            }
        }
    }
    optimal_turn = is_win ? min_turn : max_turn;
    return {is_win, optimal_turn};
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    row = board.size(), col = board[0].size();
    pair<bool, int> result = play(board, aloc[0], aloc[1], bloc[0], bloc[1]);
    return result.second;
}


/*

다시 풀어보며 느낀점
1. 변수 네이밍좀 잘하자.. 짜면서 헷갈림
2. 재귀적으로 짜는 것이, 콜스택이 터지는게 아니면 구현 난이도면에서 확실히 훨씬 쉬워지는 것 같음
   - 재귀함수로 구현하게 되면 
      해당 문제에서는 결국 종료 조건(움직일 수 없는 경우 또는 현재 나의 발판이 0인 경우)를 기준으로 잘 종료시키고
      이동이 가능한 칸으로 움직이는 것만 잘 정의하면 됨
      
3.     if(!result.first) {
            flag = true;
            min_turn = min(min_turn, result.second+1);
        } else max_turn = max(max_turn, result.second+1);
        
        해당 부분 구현하면서 삽질을 좀 많이함.   
        실제 상대방이 진 경우에만, 내가 이긴 것이고,  상대방이 이긴 케이스에는 내가 진 케이스이므로 
        각각 min_turn과 max_turn은 항상 다르게 업데이트 해주어야함 
        (다시 구현하면서 그냥 flag변수 하나 두고, 
          해당 값이 true면 모든 결과를 min_turn에 업데이트했는데 이렇게되면 값 업데이트에 문제가 생기므로 주의하자.
          

#include <bits/stdc++.h>
#define EMPTY 0
#define NON_EMPTY 1
using namespace std;

int N, M;
vector<pair<int, int> > dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool is_valid(int y, int x) {
    return (y>=0 && y<N) && (x>=0 && x<M);
}

bool can_move(vector<vector<int>>& board, int y, int x) {
    for(pair<int, int> dir: dirs) {
        int ny = y+dir.first;
        int nx = x+dir.second;
        
        if(!is_valid(ny, nx) || board[ny][nx] == EMPTY) continue;
        return true;
    }
    return false;
}

//나의 승리 여부, 승리시 최소 count, 패배시 최대 count
pair<bool, int> play(vector<vector<int>>& board, 
                     int current_turn_y, int current_turn_x,
                     int next_turn_y, int next_turn_x) {
    
    if(!can_move(board, current_turn_y, current_turn_x)) {
        return {false, 0};
    }
    if(board[current_turn_y][current_turn_x] == EMPTY) return {false, 0};

    bool flag = false;
    int min_turn = INT_MAX, max_turn = 0;
    for(pair<int, int> dir: dirs) {
        int ny = current_turn_y + dir.first;
        int nx = current_turn_x + dir.second;
        
        if(!is_valid(ny, nx) || board[ny][nx] == EMPTY) continue;
        
        board[current_turn_y][current_turn_x] = EMPTY;
        pair<bool, int> result = play(board, next_turn_y, next_turn_x, ny, nx);
        board[current_turn_y][current_turn_x] = NON_EMPTY;
        
        if(!result.first) {
            flag = true;
            min_turn = min(min_turn, result.second+1);
        } else max_turn = max(max_turn, result.second+1);
    }    

    return {flag, flag ? min_turn : max_turn};
}

int solution(vector<vector<int>> board, 
             vector<int> aloc, 
             vector<int> bloc) {
    
    N = board.size();
    M = board[0].size();
    
    pair<bool, int> result = play(board, aloc[0], aloc[1], bloc[0], bloc[1]);
    return result.second;
}

*/
