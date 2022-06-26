#include <bits/stdc++.h>
#define INSIDE 2
using namespace std;

/*
  https://www.acmicpc.net/problem/2638
  치즈
  ---
  문제 조건에 의해 각 가장자리의 값은 항상 0이다.
  가장자리의 좌표중 하나를 선택해 만약 방문하는 노드의 값이 치즈가 아닌 경우 queue에 넣으며 BFS를 실행시킨다.
  이 과정에서 치즈가 아닌데, 도달이 불가능한 노드는 치즈로 둘러쌓여있는 공기층에 해당한다.
*/
int n, m;
vector<vector<int>> cheese;
vector<pair<int, int>> dirs = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

void exposeAir() {
    vector<vector<bool>> isVisit(n, vector<bool>(m, false));
    queue<pair<int, int>> q;
    q.push({0, 0});
    isVisit[0][0] = true;

    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(pair<int, int> dir : dirs) {
            int nextY = y + dir.first;
            int nextX = x + dir.second;

            bool isValidY = (nextY >= 0 && nextY < n);
            bool isValidX = (nextX >= 0 && nextX < m);

            if(isValidY && isValidX && cheese[nextY][nextX] != 1 &&!isVisit[nextY][nextX]) {
                isVisit[nextY][nextX] = true;
                cheese[nextY][nextX] = 0;
                q.push({nextY, nextX});
            }
        }
    }
}

bool isMelting(int y, int x) {
    int exposeCnt = 0;
    for(pair<int, int> dir: dirs) {
        if(cheese[y+dir.first][x+dir.second] == 0) ++exposeCnt;
    }

    return exposeCnt >= 2;
}

vector<pair<int, int>> getMeltingTarget() {
    vector<pair<int, int>> ret;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            if(cheese[i][j] == 1 && isMelting(i, j)) {
                ret.push_back({i, j});
            }
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int cheeseCnt = 0, answer = 0;
    cin >> n >> m;
    cheese = vector<vector<int>>(n, vector<int>(m, 0));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin >> cheese[i][j];

            if(cheese[i][j] == 1) {
                ++cheeseCnt;
                continue;
            }

            bool isEdges = (i==0 || i == n-1 || j==0 || j == m-1);
            if(!isEdges) cheese[i][j] = INSIDE;
        }
    }

    while(cheeseCnt) {
        exposeAir();
        vector<pair<int, int>> targets = getMeltingTarget();
        cheeseCnt -= targets.size();
        for(pair<int, int> target: targets) cheese[target.first][target.second] = 0;
        ++answer;
    }
    cout << answer;

    return 0;
}
