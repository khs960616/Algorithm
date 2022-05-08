#include <bits/stdc++.h>
#define EMPTY '?'

using namespace std;

/*
2018 KAKAO BLIND RECRUITMENT
[1차] 프렌즈 4블록
---
구현, sliding window 
*/

int rowSize, colSize;
vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {1, 1}};

bool isFourBlock(int i, int j, vector<string>& board) {
    for(pair<int, int> dir: dirs) {
        int row = i+dir.first;
        int col = j+dir.second;

        if(board[row][col] != board[i][j]) return false;
    }
    return true;
}

int deleteBlock(const int i, const int j, vector<string>& board) {
    int cnt = 0;
    if(board[i][j] != EMPTY) {
        board[i][j] = EMPTY;
        ++cnt;
    }
    
    for(pair<int, int> dir: dirs) {
        int row = i+dir.first;
        int col = j+dir.second;
        if(board[row][col] != EMPTY) {
            board[row][col] = EMPTY;
            ++cnt;
        }
    }
    
    return cnt;
}

void sortBlock(vector<string>& board) {
    for(int i=0; i<colSize; ++i) {
        string sortColumn = "";
        for(int j=0; j<rowSize; ++j) {
            if(board[j][i]==EMPTY) sortColumn = (board[j][i] + sortColumn);
            else sortColumn += board[j][i];
        }
        for(int j=0; j<rowSize; ++j) {
            board[j][i] = sortColumn[j];
        }
    }
}

int solution(int m, int n, vector<string> board) {
    rowSize = m, colSize = n;
    int answer = 0;
    vector<string> v = board;
    
    while(1) {
        vector<pair<int, int>> v;
        int cnt = 0;
        
        for(int i=0; i<rowSize-1; ++i) {
            for(int j=0; j<colSize-1; ++j) {
                if(board[i][j] == EMPTY) continue;
                if(isFourBlock(i, j, board)) v.push_back({i, j});
            }
        }
        if(v.empty()) break;
        for(pair<int, int> p: v) answer+=deleteBlock(p.first, p.second, board);
        sortBlock(board);
    }
    
    return answer;
}
