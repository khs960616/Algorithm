#include <bits/stdc++.h>
using namespace std;

long bias = 0;
int n = 0, m = 0;
vector<vector<int> > v;
vector<pair<int, int> > dirs = {{0, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};
vector<pair<int, int> > diagonals = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
vector<pair<int, int> > clouds;

/*
https://www.acmicpc.net/problem/21610
마법사 상어와 비바라기
---
구현, 시뮬레이션
    ---
    데이터를 어떻게 표현할 것인가?
    격자는 2*2 ~ 50*50 
    이동 명령은 총 1이상 100 이하
    이동 칸은 50이하 
    ---
    필요한 기능 
    1. 구름을 이동 시키고 물의 양을 1 증가 시키는 기능
    2. 모든 칸에 대해서 각 대각선에 물이 몇개하는지 세는 기능 
    3. 물을 감소시키고 구름을 생성하는 기능 
    4. 물복사 버그를 구현하는 기능
*/

bool is_valid(int y, int x) {
    return y>=0 && y<n && x>=0 && x<n;
}

void move_clouds(int dir, int distance) {
    pair<int, int> mov_value = dirs[dir];
    mov_value.first*=distance;
    mov_value.second*=distance;

    for(pair<int, int>& cloud : clouds) {
        long y = (cloud.first + mov_value.first + bias) % n;
        long x = (cloud.second + mov_value.second + bias) % n;

        cloud.first = (int) y;
        cloud.second = (int) x;
    }
}

int get_adj_water_cnt(int y, int x) {
    int ret = 0;
    for(pair<int, int> diagonal : diagonals) {
        int next_y = y + diagonal.first;
        int next_x = x + diagonal.second;
        if(!is_valid(next_y, next_x)) continue;
        if(v[next_y][next_x] != 0) ret++;
    }
    return ret;
}

void incraese_water(vector<vector<bool> > prev_clouds) {
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(!prev_clouds[i][j]) continue;
          // 이 부분에서 테스트 케이스가 빈약한것인지, 원래 의도가 이런 것인지 불분명함. 
          // 원래 삼성스타일의 문제였다면 각 좌표별로 더해야할 값 저장해놨다가 한번에 업데이트 하는 식으로 수정해야되지 않나 싶음 
            v[i][j] += get_adj_water_cnt(i, j);
        }
    }
}

vector<vector<bool> > remove_cloud() {
    vector<vector<bool> > prev_cloud(n, vector<bool>(n, false));
    for(pair<int, int> cloud : clouds) {
        v[cloud.first][cloud.second]++;
        prev_cloud[cloud.first][cloud.second] = true;
    }
    clouds.clear();
    return prev_cloud;
}

int main() {
    cin >> n >> m;
    bias = pow(n, 6);
    clouds = {{n-1, 0}, {n-1, 1}, {n-2, 0}, {n-2, 1}};

    v = vector<vector<int> >(n, vector<int>(n));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            cin >> v[i][j];
        }
    }

    for(int i=0; i<m; ++i) {
        int dir = 0, distance = 0;
        cin >> dir >> distance;
        move_clouds(dir, distance);
        vector<vector<bool> > prev_clouds = remove_cloud();
        incraese_water(prev_clouds);

        for(int j=0; j<n; ++j) {
            for(int k=0; k<n; ++k) {
                if(prev_clouds[j][k]) continue;
                if(v[j][k] < 2) continue;
                v[j][k]-=2;
                clouds.emplace_back(j, k);
            }
        }
    }

    int answer = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            answer+=v[i][j];
        }
    }
    cout << answer << '\n';
}
