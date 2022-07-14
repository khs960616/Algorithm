#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12952
  N-queen
  ----
  백트래킹 
*/
bool isValid(int n, int row, int column, vector<vector<bool>> queens) {
    int diagnol = 1;
    for(int i=row-1; i>=0; --i) {
        if(queens[i][column]) return false;
        if(column-diagnol>=0 && queens[i][column-diagnol]) return false;
        if(column+diagnol<n && queens[i][column+diagnol]) return false;
        ++diagnol;
    }
    
    return true;
}

void nQueen(int n, int row, int& answer, vector<vector<bool>> queens) {
    if(row == n) return;
    
    for(int i=0; i<n; ++i) {
        if(isValid(n, row, i, queens)) {
            if(row == n-1) {
                ++answer;
                continue;
            }
            queens[row][i] = true;
            nQueen(n, row+1, answer, queens);
            queens[row][i] = false;
        }
    }
}

int solution(int n) {
    int answer = 0;
    vector<vector<bool>> queens(n, vector<bool>(n, false));
    nQueen(n, 0, answer, queens);
    return answer;
}
