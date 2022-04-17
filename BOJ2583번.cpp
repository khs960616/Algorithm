#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n, k;
    cin >> m >> n >> k;
    vector<vector<bool> > visit(m, vector<bool>(n, false));
    vector<vector<int> > area(m, vector<int>(n, 0));
    vector<int> answer;
    queue<pair<int,int> > bfs;

    // make coordinate
    while(k--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int minY = min(y1, y2); 
        int maxY = max(y1, y2);
        int minX = min(x1, x2);
        int maxX = max(x1, x2);
        
        for(int i=minY; i<maxY; i++) {
            for(int j=minX; j<maxX; j++) {
                area[i][j] = 1;
            }
        }
    }

    //dfs
    for(int i=0; i<m; ++i) {
        for(int j=0; j<n; ++j) {
            if(area[i][j]==1 || visit[i][j]) continue;
            bfs.push(make_pair(i, j));
            int val = 0;

            while(!bfs.empty()) {
                pair<int, int> coordinate = bfs.front();
                bfs.pop();
                if(visit[coordinate.first][coordinate.second]) continue;

                ++val;
                visit[coordinate.first][coordinate.second] = true;
                // 상하좌우 유효한 좌표인지, 사각형이 위치하지 않은 영역인지 확인
                if(coordinate.first-1>=0 && !area[coordinate.first-1][coordinate.second]) {
                    bfs.push(make_pair(coordinate.first-1, coordinate.second));
                }

                if(coordinate.second+1<n && !area[coordinate.first][coordinate.second+1]) {
                    bfs.push(make_pair(coordinate.first, coordinate.second+1));
                }

                if(coordinate.first+1<m && !area[coordinate.first+1][coordinate.second]) {
                    bfs.push(make_pair(coordinate.first+1, coordinate.second));
                }

                 if(coordinate.second-1>=0 && !area[coordinate.first][coordinate.second-1]) {
                    bfs.push(make_pair(coordinate.first, coordinate.second-1));
                }
            }
            answer.push_back(val);
        }
    }

    sort(answer.begin(), answer.end());
    cout << answer.size() << endl;
    for(int i : answer) cout << i << ' ';
    return 0;
} 
