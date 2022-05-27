#include <bits/stdc++.h>

using namespace std;
/*
https://www.acmicpc.net/problem/14500
테트로미노
----------
브루트포스, DFS, 구현

구현 방식[1]각 테트로미노의 회전, 반전시 모양이 다르게 나오는 케이스 19개를 각각을 세서 일일히 구현 
// 500 * 500 * 19  -> 대략 5백만 정도이므로 브루트포스 가능 

구현방식 [2]ㅜ ㅏ ㅗ ㅓ 모양을 제외한 다른 테트로미노는 DFS를 활용하면 모두 고려되므로 해당 4가지 케이스만 별도 구현 

*/
int n, m;
vector<vector<int>> v;
vector<vector<bool>> isVisit;
vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool isValid(int y, int x) {
    return y >= 0 && y < n && x >=0 && x< m ;
}

void dfs(int y, int x, int depth, int& answer, int sum) {
    if(depth == 4) {
        answer = max(answer, sum);
        return;
    }

    for(pair<int, int> dir : dirs) {
        int currentY = y+dir.first;
        int currentX = x+dir.second;

        if(isValid(currentY, currentX) && !isVisit[currentY][currentX]) {
            isVisit[currentY][currentX] = true;
            dfs(currentY, currentX, depth+1, answer, sum+v[currentY][currentX]);
            isVisit[currentY][currentX] = false;
        }
    }
}

void checkNoDepthTetromino(int y, int x, int& answer) {
    int base = v[y][x];

    if(isValid(y-1, x-1) && isValid(y-1, x+1)) {
        answer = max(answer, v[y][x]+v[y-1][x-1]+v[y-1][x]+v[y-1][x+1]);
    }   

    if(isValid(y+1, x-1) && isValid(y+1, x+1)) {
        answer = max(answer, v[y][x]+v[y+1][x-1]+v[y+1][x]+v[y+1][x+1]);
    } 

    if(isValid(y-1, x-1) && isValid(y+1, x-1)) {
        answer = max(answer, v[y][x]+v[y-1][x-1]+v[y][x-1]+v[y+1][x-1]);
    }

    if(isValid(y-1, x+1) && isValid(y+1, x+1)) {
        answer = max(answer, v[y][x]+v[y-1][x+1]+v[y][x+1]+v[y+1][x+1]);
    }
}

int main() {
    int answer = -1;
    cin >> n >> m;
    v = vector<vector<int>>(n, vector<int>(m, 0));
    isVisit = vector<vector<bool>>(n, vector<bool>(m, false));

    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin >> v[i][j];
        }
    }

    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            isVisit[i][j] = true;
            dfs(i, j, 1, answer, v[i][j]);
            isVisit[i][j] = false;
            checkNoDepthTetromino(i, j, answer);
        }
    }

    cout << answer;
    return 0;   
}
