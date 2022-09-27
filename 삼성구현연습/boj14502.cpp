#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/14502
연구소
---
브루트 포스, 재귀, bfs
1. 각 빈칸에 벽을 설치하는 경우, 설치하지 않는 경우를 재귀적으로 호출하며 벽을 설치한다.
2. 설치한 벽의 개수가 3개가 되면, bfs를 통해 바이러스를 인접노드에 전파시킨다.
3. 바이러스를 모두 전파시킨 후 빈칸의 개수를 구한다. 
*/

int answer = INT_MIN;
int n = 0, m = 0;
int empty_cnt = 0;
vector<pair<int, int> > empty_space;
vector<pair<int, int> > virus_space;
vector<pair<int, int> > dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool is_valid(int y, int x) {
    return (y>=0 && y<n) && (x>=0 && x<m);
}

int bfs(vector<vector<int> > v) {
    queue<pair<int, int> > q;
    for(pair<int, int> virus : virus_space) q.push(virus);
    
    while(!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();

        for(pair<int, int> dir : dirs) {
            int next_y = p.first + dir.first;
            int next_x = p.second + dir.second;

            if(!is_valid(next_y, next_x)) continue;
            if(v[next_y][next_x] == 0) {
                v[next_y][next_x] = 2;
                q.emplace(next_y, next_x);
            }
        }
    }

    int ret = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            if(v[i][j] == 0) ret++;
        }
    }
    return ret;
}


void establish_wall(vector<vector<int> > v, int current_idx, int remain_cnt) {
    if(remain_cnt == 0) {
        answer = max(answer, bfs(v));
        return;
    }

    if(current_idx >= empty_cnt) return;
    // 현재 빈 칸에 벽을 설치하지 않고 넘어 가는 경우 
    establish_wall(v, current_idx+1, remain_cnt);
    // 현재 빈 칸에 벽을 설치하는 경우
    v[empty_space[current_idx].first][empty_space[current_idx].second] = 1;
    establish_wall(v, current_idx+1, remain_cnt-1);
}

int main() {
    cin >> n >> m;

    vector<vector<int> > v(n, vector<int>(m, 0));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin >> v[i][j];
            if(v[i][j] == 0) empty_space.emplace_back(i, j);
            else if(v[i][j] == 2) virus_space.emplace_back(i, j);
        }
    }
    empty_cnt = empty_space.size();
    establish_wall(v, 0, 3);

    cout << answer << '\n';
}
