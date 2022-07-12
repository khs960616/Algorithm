#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2468
안전 영역
----BFS
*/
vector<pair<int, int> > dirs = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void bfs(int n, int y, int x, int height, 
         vector<vector<int> >& v,
         vector<vector<bool> >& isVisit) {
    queue<pair<int, int> > q;
    isVisit[y][x] = true;
    q.push({y, x});

    while (!q.empty()) {
        int currentY = q.front().first;
        int currentX = q.front().second;
        q.pop();

        for(pair<int, int> dir : dirs) {
            int nextY = currentY + dir.first;
            int nextX = currentX + dir.second;

            bool isValidY = (nextY >= 0 && nextY < n);
            bool isValidX = (nextX >= 0 && nextX < n);

            if(!isValidY || !isValidX) continue;
            if(v[nextY][nextX] > height && !isVisit[nextY][nextX]) {
                isVisit[nextY][nextX] = true;
                q.push({nextY, nextX});
            }
        }
    }
}

int getAreaCnt(int n, int height, vector<vector<int> >& v) {
    int ret = 0;
    vector<vector<bool> > isVisit(n, vector<bool>(n, false));

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(v[i][j] <= height) continue;
            if(isVisit[i][j]) continue;
            isVisit[i][j] = true;
            ++ret;
            bfs(n, i, j, height, v, isVisit);
        }
    }
    return ret;
}

int main() {
    int n, answer = 1, minHeight = 200, maxHeight = 0;
    cin >> n;
    vector<vector<int> > v(n, vector<int>(n, 0));

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            cin >> v[i][j];
            minHeight = min(minHeight, v[i][j]);
            maxHeight = max(maxHeight, v[i][j]);
        }
    }

    for(int height = minHeight; height< maxHeight; ++height) {
        int cnt = getAreaCnt(n, height, v);
        answer = max(answer, cnt);
    }

    cout << answer;
    return 0;
}
