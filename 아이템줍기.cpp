#include <bits/stdc++.h>
#define WINDOW_SIZE 101
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/87694
  아이템 줍기
  BFS, 구현
  ---
  1. 각 직사각형들을 겹쳤을 때, 바깥 둘레를 지도 형태로 표현해야한다.
  2. 만들어진 지도를 통해 BFS를 이용해 최단경로를 구해야한다.
  ---
  고려해야할 점
  1. 모든 좌표계를 2배씩 증가 시키면 문제를 단순화하는데 큰 도움이 된다.
     - 실제 좌표는 선분을 나타내는게 아닌, 각 선분을 이루는 "점"이다. 
       따라서 2배 증가시키지 않는 경우 테스트케이스 1번에서 문제가 생긴다.
       실제로는 선분이 아닌 떨어져있는 두 점이 표현 방식의 차이로 인해 선분으로 오인되는 경우가 생긴다.
       
  2. 지도형태로 바깥 테두리만 어떻게 뽑아낼까?
     - 두 가지가 고려될 수 있다.
       직사각형의 면에 속하는 모든 점을 1로 표현한다.
       이후 주어진 직사각형들을 다시 순회하며 테두리를 제외한 모든 좌표를 0으로 바꿔주면, 실제로 겹쳐있으면서, 테두리가 아닌 부분들은 모두 지워지게 된다.
  
  
  1번과 2번을 고려해서 구현하면 복잡한 문제가 단순 최단 경로를 구하는 BFS문제로 변화하게 된다.
  이 떄 1번에서 모든 좌표를 2배씩 증가시켰으므로, 실제 경로도 2배만큼 증가했을 것이므로, 최종결과는 2로 나누어져야한다.
*/
vector<pair<int, int> > dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool is_valid(int y, int x) {
    return (y>0 && y<WINDOW_SIZE) && (x>0 && x<WINDOW_SIZE);
}

void scale_up(vector<vector<int>>& rectangles, 
              int& characterX, int& characterY,
              int& itemX, int& itemY) {
    
    characterX*=2, characterY*=2, itemX*=2, itemY*=2;
    for(vector<int>& rectangle: rectangles) {
        for(int& i: rectangle) i*=2;
    } 
}

void fill_rectangles(vector<vector<int>>& rectangles, vector<vector<int> >& board) {
    for(vector<int>& rectangle: rectangles) {
        for(int i=rectangle[1]; i<=rectangle[3]; ++i) {
            for(int j=rectangle[0]; j<=rectangle[2]; ++j) {
                board[i][j] = 1;
            }
        }
    }
}

void delete_inner_coordinate(vector<vector<int>>& rectangles, vector<vector<int> >& board) {
    for(vector<int>& rectangle: rectangles) {
        for(int i=rectangle[1]+1; i<rectangle[3]; ++i) {
            for(int j=rectangle[0]+1; j<rectangle[2]; ++j) {
                board[i][j] = 0;
            }
        }
    }
}

vector<vector<int> > make_board(vector<vector<int>>& rectangles) {
    vector<vector<int> > board(WINDOW_SIZE, vector<int>(WINDOW_SIZE, 0));
    fill_rectangles(rectangles, board);
    delete_inner_coordinate(rectangles, board);
    return board;
}

int solution(vector<vector<int>> rectangles, 
             int characterX, int characterY, 
             int itemX, int itemY) {
    scale_up(rectangles, characterX, characterY, itemX, itemY);
    
    vector<vector<int> > board = make_board(rectangles);
    vector<vector<bool> > is_visit(WINDOW_SIZE, vector<bool>(WINDOW_SIZE, false));


    queue<tuple<int, int, int> > q;
    q.emplace(characterY, characterX, 0);
    is_visit[characterY][characterX] = true;
    
    while(!q.empty()) {
        auto [y, x, cost] = q.front();
        q.pop();

        if(y == itemY && x == itemX) return cost/2;
        
        for(int i=0; i<4; ++i) {
            int ny = y+dirs[i].first;
            int nx = x+dirs[i].second;
            
            if(!is_valid(ny, nx)) continue;
            if(board[ny][nx] == 0 || is_visit[ny][nx]) continue;
            
            is_visit[ny][nx] = true;
            q.emplace(ny, nx, cost+1);
        }
    }
    return 0;
}
