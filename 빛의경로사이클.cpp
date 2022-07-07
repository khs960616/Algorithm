#include <bits/stdc++.h>
#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/86052
  빛의 경로 사이클
  배열, 구현
  --------
  1. 현재 이동중인 방향이 'S', 'L', 'R'을 만났을 떄 어떻게 변화하는가?
  2. 사이클을 어떻게 감지할 것인가? (최조 getCycle 함수 실행 시 input 으로 준 row, column, dir이 동일해지는 경우 (이 경우 동일한 연산을 반복하는 경우이며, 사이클을 모두 돈 case임)
  ---------
  input 조건의 제한 조건을 좀 더 명시적으로 적어줘야 할듯함.
  현재 풀이는 어떤 방향으로 빛을 쏴도, 해당 경로가 반드시 특정 Cycle에는 포함된다는 전제로 푼 것이기 때문에,
  해당 전제가 틀리다면 문제 풀이 자체가 성립하지 않음. 
*/

int rowSize = 0;
int columnSize = 0;
bool isVisit[500][500][4];

int getNextDir(int currentDir, char gridType) {
    if('L' == gridType) {
        switch(currentDir) {
            case LEFT:
                return DOWN;
            case UP:
                return LEFT;
            case RIGHT:
                return UP;
            case DOWN:
                return RIGHT;
        }
    }        
    
    if('R' == gridType) {
        switch(currentDir) {
            case LEFT:
                return UP;
            case UP:
                return RIGHT;
            case RIGHT:
                return DOWN;
            case DOWN:
                return LEFT;
        }
    }
    return currentDir;
}

pair<int, int> getNextPosition(int row, int column, int dir) {
    switch(dir) {
        case LEFT:
            column-=1;
            if(column<0) column = columnSize-1;
            break;
        case RIGHT:
            column+=1;
            if(column>=columnSize) column = 0;
            break;
        case DOWN:
            row+=1;
            if(row>=rowSize) row = 0;
            break;
        case UP:
            row-=1;
            if(row<0) row = rowSize-1;
            break;
    }
    
    return {row, column};
}

int getCycle(int row, int column, int dir, vector<string> grid) {
    int ret = 0;
    
    int currentDir = dir;
    pair<int, int> currentPoisiton = {row, column};

    do{
        ++ret;
        isVisit[currentPoisiton.first][currentPoisiton.second][currentDir] = true;
        
        currentPoisiton = getNextPosition(currentPoisiton.first, 
                                          currentPoisiton.second,
                                          currentDir);
        currentDir = getNextDir(currentDir, grid[currentPoisiton.first][currentPoisiton.second]);
        if(row == currentPoisiton.first && column == currentPoisiton.second) {
            if(isVisit[row][column][currentDir]) break;
        }
    
    } while(1);
    return ret;
}

vector<int> solution(vector<string> grid) {
    vector<int> answer;
    rowSize = grid.size();
    columnSize = grid[0].size();
    
    for(int i=0; i<rowSize; ++i) {
        for(int j=0; j<columnSize; ++j) {
            for(int k=0; k<4; ++k) {
                if(isVisit[i][j][k]) continue;
                answer.push_back(getCycle(i, j, k, grid));
            }
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}
