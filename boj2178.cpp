#include <bits/stdc++.h>

using namespace std;

/*
https://www.acmicpc.net/problem/2178
미로 탐색
bfs
*/

int n, m;
vector<string> v;
vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

class Info {
public:
    int y;
    int x;
    int cnt;
};

int main() {
    int answer = INT_MAX;
    cin >> n >> m;
    v = vector<string>(n);
    for(int i=0; i<n; ++i) cin >> v[i];    
    vector<vector<bool>> isVisit(n, vector<bool>(m, false));

    queue<Info> q;
    q.push({0, 0, 1});
    isVisit[0][0] = true;

    while(!q.empty()) {
        Info i = q.front();
        q.pop();
        if(i.y == n-1 && i.x == m-1) {
            cout << i.cnt;
            break;
        }

        for(pair<int, int> dir: dirs) {
            int curY = i.y + dir.first;
            int curX = i.x + dir.second;

            bool isValidY = (curY >= 0 && curY < n);
            bool isValidX = (curX >=0 && curX < m);

            if(isValidY && isValidX && !isVisit[curY][curX] && v[curY][curX] == '1') {
                isVisit[curY][curX] = true;
                q.push({curY, curX, i.cnt+1});
            }
        }
    }
    
    return 0;   
}
