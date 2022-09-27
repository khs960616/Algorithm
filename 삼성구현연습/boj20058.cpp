#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/20058
  마법사 상어와 파이어스톰
  ---
  구현, bfs, 재귀 
  
  격자 회전 코드 참고 사항 : https://yjyoon-dev.github.io/boj/2020/11/04/boj-20058/ 
  회전 하는 코드의 경우 다음과 같이 구성하는게 더 좋을듯..
  
*/
int grid_size = 0;
int n = 0, q = 0;
vector<vector<int> > a;
vector<pair<int, int> > dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void rotate(int y, int x, int len) {
    if(len == 1) return;

    vector<int> prev;
    for(int i=x; i<x+len; ++i) prev.push_back(a[y][i]);
    for(int i=y+1; i<y+len; ++i) prev.push_back(a[i][x+len-1]);
    for(int i=x+len-2; i>=x; --i) prev.push_back(a[y+len-1][i]);
    for(int i=y+len-2; i>y; --i) prev.push_back(a[i][x]);
    
    // 90도 회전
    for(int i=0; i<len-1; ++i) {
        prev.insert(prev.begin(), prev.back());
        prev.pop_back();
    }
    
    int prev_idx = 0;
    for(int i=x; i<x+len; ++i) a[y][i] = prev[prev_idx++];
    for(int i=y+1; i<y+len; ++i) a[i][x+len-1] = prev[prev_idx++];
    for(int i=x+len-2; i>=x; --i) a[y+len-1][i] = prev[prev_idx++];
    for(int i=y+len-2; i>y; --i) a[i][x] = prev[prev_idx++];

    if(len > 2) rotate(y+1, x+1, len-2);
}

bool is_valid(int y, int x) {
    return y>=0 && y<grid_size && x>=0 && x<grid_size;
}

int get_adj_info(int y, int x) {
    if(a[y][x] == 0) return 0;

    int adj_ice_cnt = 0;
    for(pair<int, int> dir: dirs) {
        int adj_y = y+dir.first;
        int adj_x = x+dir.second;
        if(!is_valid(adj_y, adj_x)) continue;
        if(a[adj_y][adj_x] != 0) ++adj_ice_cnt;
    }

    return adj_ice_cnt;
}

int bfs(int y, int x, vector<vector<bool> >& is_visit) {
    int ret = 1;
    queue<pair<int, int> > q;
    q.emplace(y, x);
    is_visit[y][x] = true;

    while(!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();

        for(pair<int, int> dir: dirs) {
            int next_y = p.first + dir.first;
            int next_x = p.second + dir.second;

            if(!is_valid(next_y, next_x)) continue;
            if(!is_visit[next_y][next_x] && a[next_y][next_x] != 0) {
                q.emplace(next_y, next_x);
                is_visit[next_y][next_x] = true;
                ++ret;
            }
        }
    }
    
    return ret;
}

int main() {
    cin >> n >> q;
    grid_size = (1<<n);

    a = vector<vector<int> >(grid_size, vector<int>(grid_size, 0));
    for(int i=0; i<grid_size; ++i) {
        for(int j=0; j<grid_size; ++j) {
            cin >> a[i][j];
        }
    }

    for(int i=0; i<q; ++i) {
        int fire_storm = 0;
        cin >> fire_storm;

        int div_size = (1<<fire_storm);
        // 구간별 회전 
        for(int j=0; j<grid_size; j+=div_size) {
            for(int k=0; k<grid_size; k+=div_size) {
                rotate(j, k, div_size);
            }
        }
        // 얼음 갯수 줄이기
        vector<pair<int, int> > decrease_coordinates;
        for(int j=0; j<grid_size; ++j) {
            for(int k=0; k<grid_size; ++k) {
                int cnt = get_adj_info(j, k);
                if(cnt < 3 && a[j][k] > 0) decrease_coordinates.emplace_back(j, k);
            }
        }
        for(pair<int, int> coordinate : decrease_coordinates) --a[coordinate.first][coordinate.second];

    }

    int total_ice = 0, max_area_size = INT_MIN;
    vector<vector<bool> > is_visit(grid_size, vector<bool>(grid_size, false));
    for(int i=0; i<grid_size; ++i) {
        for(int j=0; j<grid_size; ++j) {
            total_ice+= a[i][j];

            if(!is_visit[i][j] && a[i][j] != 0) {
                max_area_size = max(max_area_size, bfs(i, j, is_visit));
            }
        }
    }

    if(max_area_size == INT_MIN) max_area_size = 0;
    cout << total_ice << '\n' << max_area_size;
}
