#include <bits/stdc++.h>
#define DONE 3
using namespace std;

/*
  https://www.acmicpc.net/problem/14503
  로봇 청소기
  ---
  구현, 시뮬레이션 
*/

int n, m;
int r, c, d;
int answer = 1;
vector<pair<int, int>> dirs = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

void lotate_dir() {
    d--;
    if(d < 0) d = 3;
}

bool is_valid(int y, int x) {
    return (y>=0 && y<n) && (x>=0 && x<m);
}

int main() {
    cin >> n >> m;
    cin >> r >> c >> d;
    vector<vector<int> > v(n, vector<int>(m, 0));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin >> v[i][j];
        }
    }
    
    v[r][c] = DONE;
    while(1) {
        bool flag = false;
        int prev_dir = d;
        for(int i=0; i<4; ++i) {
            lotate_dir();
            int next_y = r + dirs[d].first;
            int next_x = c + dirs[d].second;

            if(!is_valid(next_y, next_x)) continue;
            // 왼쪽 방향에 아직 청소하지 않은 공간이 존재하는 경우
            if(v[next_y][next_x] == 0) {
                flag = true;
                v[next_y][next_x] = DONE;
                r = next_y;
                c = next_x;
                answer++;
                break;
            }
        }

        if(flag) continue;
        // 네 방향 모두 청소가 이미 되어있거나 벽인 경우 
        d = prev_dir; 
        // 현재 바라보는 방향의 반대방향으로 1칸 이동해야한다.   (d+2)%4 (서쪽->동쪽, 남쪽 -> 북쪽) 이동하는 케이스를 고려하기 위해 모듈러 연산이 필요함.
        int next_y = r + dirs[(d+2)%4].first; 
        int next_x = c + dirs[(d+2)%4].second;
        if(is_valid(next_y, next_x) && v[next_y][next_x] != 1) {
            r = next_y;
            c = next_x;
            continue;
        }
        break;
    }
    cout << answer << '\n';
}
