#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/84021
  퍼즐 조각 채우기
  BFS, 복잡한 구현 
  ---
  필요한 기능 정리
  
  1. game_board 에서는 퍼즐이 들어갈 수 있는 빈칸을,
     table에서는 퍼즐을 BFS를 통해 추출해내야한다. 
     
     이 때 퍼즐 모양을 어떤 형태의 데이터로 저장할지 결정해야한다.
     생각해본 방식은 다음의 두 가지이다.
     1-1) 퍼즐을 이루는 각 좌표를 vector형태로 저장한다.
     1-2) 퍼즐은 최대 6개의 좌표로 이루어질 수 있으므로 6*6 격자로는 모든 데이터 표현이 가능하다. 
          따라서 격자 형태의 데이터를 해쉬값으로 만들어 저장할 수 있다.
     
     두 가지 방식 모두 블록을 이루는 가장 작은 y좌표와 x좌표를 이용해 좌표계 변환은 필요하다. (다른 위치에 존재해도 모양이 같다면 다른 블록이므로 정확한 비교를 위해서,
     문제 풀이에서는 1-1) 방식을 선택했다.  차후, 퍼즐의 회전까지 고려한다면, 해쉬를 이용해 시간복잡도가 줄어들 것 같지도 않고, 구현난이도가 더 상승하기 때문이다.
     
  2. 시계방향으로 90도 블록 회전 
     회전변환의 성질을 이용하면 x' = -y,  y'= x형태로 좌표 표현이 가능하다.
     그러나 나는 1-1)에서 가장 작은 좌표를 기준으로 (0, 0)을 시작으로 하는 좌표계를 만든 것이므로 음수 형태의 좌표는 생성하지 않았다.
     
     따라서 회전하고자하는 블록을 이루는 좌표중 가장 y값이 큰 값을 구한후 x'에 값을 더해준다. (좌표값만큼 평행이동을 해준다.)
     이렇게 데이터를 표현하고 나면 x' = (max(x) - y),  y' = x의 형태이며 이전의 y값중 가장 큰 값을 더했으므로 
     모든 x'은 양수이며, 평행이동을 한 것이므로 모양도 변하지 않는다. 또한 데이터의 형태 또한 1번에서와 같이 가장 작은 x좌표, y좌표를 기준을 원점으로한 형태의 좌표를 구할 수 있다.
     
     회전 이후에는 블록을 이루는 각 좌표들을 정렬하여 차후 같은 블록인지 비교하기 쉽게 만든다. 
*/
int board_size = 0;
vector<pair<int, int> > dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool is_valid(int y, int x) {
    return (y>=0 && y<board_size) && (x>=0 && x<board_size);
}

void coordinate_transformation(vector<pair<int, int> >& block) {
    int min_x = INT_MAX, min_y = INT_MAX;
    
    for(pair<int, int>& p: block) {
        min_y = min(min_y, p.first);
        min_x = min(min_x, p.second);
    }
    
    for(pair<int, int>& p: block) {
        p.first -= min_y;
        p.second -= min_x;
    }
}

vector<pair<int, int> > get_block(vector<vector<int>>& board, 
                                  vector<vector<bool> >& is_visit,
                                  int type, int y, int x) {
    vector<pair<int, int> > ret;
    queue<pair<int, int> > q;
    q.emplace(y, x);
    
    while(!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        ret.emplace_back(p);
        
        for(pair<int, int> dir: dirs) {
            int ny = p.first + dir.first;
            int nx = p.second + dir.second;
            if(!is_valid(ny, nx)) continue;
            if(board[ny][nx] != type || is_visit[ny][nx]) continue;
            
            is_visit[ny][nx] = true;
            q.emplace(ny, nx);
        }
    }
    
    coordinate_transformation(ret);
    sort(ret.begin(), ret.end());
    return ret;
}

vector<vector<pair<int, int> > > get_blocks(vector<vector<int>>& board, int type) {
    vector<vector<pair<int, int> > > ret;
    vector<vector<bool> > is_visit(board_size, vector<bool>(board_size, false));
    
    for(int i=0; i<board_size; ++i) {
        for(int j=0; j<board_size; ++j) {
            if(is_visit[i][j]) continue;
            if(board[i][j] != type) continue;
            
            is_visit[i][j] = true;
            ret.push_back(get_block(board, is_visit, type, i, j));
        }
    }
    return ret;
}

void rotate_block(vector<pair<int, int> >& block) {
    int max_row = 0;
    for(pair<int, int> p: block) max_row = max(max_row, p.first);
    
    for(pair<int, int>& p: block) {
        int y = p.first, x = p.second;
        p.first = x;
        p.second = max_row-y;
    }
    sort(block.begin(), block.end());
}

bool compare_block(vector<pair<int, int> > empty_space, vector<pair<int, int> > puzzle) {
    int space_size = empty_space.size();
    if(space_size != puzzle.size()) return false;
    
    int cnt = 4;
    while(cnt--) {
        bool flag = true;
        for(int i=0; i<space_size; ++i) {
            if(empty_space[i].first != puzzle[i].first || empty_space[i].second != puzzle[i].second) {
                flag = false;
                break;
            }    
        }
        
        if(flag) return true;
        rotate_block(puzzle);
    }
    
    return false;
}

int solution(vector<vector<int>> game_board,
             vector<vector<int>> table) {
    board_size = game_board.size();
    int answer = 0;
    
    vector<vector<pair<int, int> > > empty_spaces = get_blocks(game_board, 0);
    vector<vector<pair<int, int> > > puzzles = get_blocks(table, 1);
    
    int empty_space_cnt = empty_spaces.size();
    int puzzle_cnt = puzzles.size();
    vector<bool> is_used(puzzle_cnt, false);
    
    for(int i=0; i<empty_space_cnt; ++i) {
        for(int j=0; j<puzzle_cnt; ++j) {
            if(is_used[j]) continue;
            
            if(compare_block(empty_spaces[i], puzzles[j])) {
                is_used[j] = true;
                answer+= puzzles[j].size();
                break;
            }
        }
    }
    
    return answer;
}
