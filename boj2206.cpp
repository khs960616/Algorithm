#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2206
BFS
---
벽을 1회 부순 상태에서 이동하는 경우, 
벽을 부수지 않은 상태에서 이동하는 경우를 나누어서 방문여부를 체크해야한다.

나누지 않은 상태에서는 다음과 같이 우회하여 갈 수 있는 경로를 체크하지 못함 
01000
01011
00010

*/
vector<pair<int, int>> dirs = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> maps;
    vector<vector<bool>> isVisit(n, vector<bool>(m, false));
    vector<vector<bool>> isBrokenPathVisit(n, vector<bool>(m, false));
    
    for(int i=0; i<n; ++i) {
        string s;
        cin >> s;
        maps.push_back(s);
    }

    queue<tuple<int, int, int, bool>> q;
    q.push({0, 0, 1, false});
    isVisit[0][0] = true;

    int answer = -1;
    while(!q.empty()) {
        int currentY = get<0>(q.front());
        int currentX = get<1>(q.front());
        int currentDepth = get<2>(q.front());
        bool pathHasBroken = get<3>(q.front());
        q.pop();

        if(currentY == n-1 && currentX == m-1) {
            answer = currentDepth;
            break;
        }

        for(pair<int, int> dir: dirs) {
            int nextY = currentY + dir.first;
            int nextX = currentX + dir.second;
            bool isValidY = (nextY >= 0 && nextY < n);
            bool isValidX = (nextX >= 0 && nextX < m);

            if(!isValidY || !isValidX) continue;

            if(pathHasBroken) {
                if(!isBrokenPathVisit[nextY][nextX] && maps[nextY][nextX] == '0') {
                    isBrokenPathVisit[nextY][nextX] = true;
                    q.push({nextY, nextX, currentDepth+1, pathHasBroken});
                }
            } else {
                if(!isVisit[nextY][nextX]) {
                    if(maps[nextY][nextX] == '0') {
                        isVisit[nextY][nextX] = true;
                        q.push({nextY, nextX, currentDepth+1, pathHasBroken});
                    } else {
                        isBrokenPathVisit[nextY][nextX] = true;
                        q.push({nextY, nextX, currentDepth+1, true});
                    }
                }
            }
        }
    }

    cout << answer;
    return 0;   
}
