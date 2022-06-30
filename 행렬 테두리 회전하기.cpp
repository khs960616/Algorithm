#include <bits/stdc++.h>
using namespace std;

/*
  https://programmers.co.kr/learn/courses/30/lessons/77485
  행렬 테두리 회전
  -------
  단순 구현
*/
int rotate(vector<vector<int>>& board, vector<int> query) {
    int ret = board[query[0]][query[3]-1];
    int value = board[query[0]][query[1]-1];
    
    for(int i=query[1]-1; i<query[3]; ++i) {
        ret = min(ret, board[query[0]-1][i]);
        int temp = board[query[0]-1][i];
        board[query[0]-1][i] = value;
        value = temp;
    }
    
    for(int i=query[0]; i<query[2]; ++i) {
        ret = min(ret, board[i][query[3]-1]);
        int temp = board[i][query[3]-1];
        board[i][query[3]-1] = value;
        value = temp;
    }
  
    for(int i=query[3]-2; i>=query[1]-1; --i) {
        ret = min(ret, board[query[2]-1][i]);
        int temp = board[query[2]-1][i];
        board[query[2]-1][i] = value;
        value = temp;
    }
    
    for(int i=query[2]-2; i>=query[0]; --i) {
        ret = min(ret, board[i][query[1]-1]);
        int temp = board[i][query[1]-1];
        board[i][query[1]-1] = value;
        value = temp;
    }
    return ret;
}

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    
    // make board;
    vector<vector<int>> board(rows, vector<int>(columns, 0));
    int num = 1;
    for(int i=0; i<rows; ++i) {
        for(int j=0; j<columns; ++j) {
            board[i][j] = num++;
        }
    }
    
    for(vector<int> query : queries) {
        answer.push_back(rotate(board, query));
    }

    return answer;
}
