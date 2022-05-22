#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1520
내리막길 
---------------------
DP, Memoization, dfs
뽑아낼 수 있는 상태 : 현재 position
cnt[i][j]  -> 원점으로부터 v[i][j] 까지 낮은 계단만을 밟으며 내려올수 있는 경우의 수
*/

int m, n;
vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
vector<vector<int>> v;
vector<vector<int>> cnt;

int calcPaths(int y, int x) {
    //y, x -> 현재 위치
    int& ret = cnt[y][x];
    if(ret != -1) return ret;

    ret = 0;
    for(pair<int, int> dir: dirs) {
        int nextY = y + dir.first;
        int nextX = x + dir.second;
        bool isValidY = (nextY >=0 && nextY < m);
        bool isValidX = (nextX >=0 && nextX < n);
        bool isFinal = (nextY == m-1 && nextX == n-1); 
        //현재 위치가 이전보다 낮은 경우에만 현재 case로 이동이 가능하다.
        if(isValidY && isValidX && !isFinal && v[y][x] < v[nextY][nextX]) {
            ret += calcPaths(nextY, nextX);
        }
    }

    return ret;
}

int main() {    
    //init 
    cin >> m >> n;
    v = vector<vector<int>>(m, vector<int>(n, 0));
    cnt = vector<vector<int>>(m, vector<int>(n, -1));
    cnt[0][0] = 1;  //각 경로는 v[i][j]를 1개씩만 중복해서 포함할 수 없으며, 원점에서 시작하므로 cnt[0][0] = 1 
    vector<vector<bool>> isVisit(m, vector<bool>(n, false));
    for(int i=0; i<m; ++i) {
        for(int j=0; j<n; ++j) {
            cin >> v[i][j];
        }
    }
  
    // solution
    cout << calcPaths(m-1, n-1);

    return 0;
}
