#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/20056
  마법사 상어와 파이어볼
  ---
  구현, 시뮬레이션, 모듈러 연산
*/

int n = 0, m = 0, k = 0;
int bias = 0;     // 모듈러 연산에서 사용하기 위한 보정값
vector<pair<int, int> > dirs = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

struct Fire {
    int r;
    int c;
    int mass;
    int dir;
    int speed;
};

// 각 fire_ball들을 진행 방향으로 speed값 만큼 이동시킨다. 이 때 문제 조건에서 1과 N은 연결되어있는 원형큐 형태라고 하였으므로 모듈러 연산을 활용해야한다.
void move_fire_ball(vector<Fire>& fire_balls) {
    for(Fire& fire_ball : fire_balls) {
        pair<int, int> mov_dir = dirs[fire_ball.dir];
        fire_ball.r = (fire_ball.r + (mov_dir.first * fire_ball.speed) + bias) % n;
        fire_ball.c = (fire_ball.c + (mov_dir.second * fire_ball.speed) + bias) % n;
    }
}

// 각 파이어볼의 좌표를 key값으로 하여 정보를 맵형태로 가공한다.
map<pair<int, int>, vector<Fire> > add_fire_balls(vector<Fire> fire_balls) {
    map<pair<int, int>, vector<Fire> > ret;
    for(Fire fire_ball : fire_balls) {
        ret[{fire_ball.r, fire_ball.c}].push_back(fire_ball);
    }
    return ret;
}

vector<Fire> divide_fire_ball(vector<Fire> fire_balls) {
    vector<Fire> ret;

    map<pair<int, int>, vector<Fire> > infos = add_fire_balls(fire_balls);
    for(auto info : infos) {
        pair<int, int> key = info.first;
        vector<Fire> values = info.second;
        int v_size = values.size();
        if(v_size == 1) {
            ret.push_back(values[0]);
            continue;
        }

        int t_mass = 0, t_speed = 0, odd = 0, even = 0;
        for(Fire fire : values) {
            t_mass += fire.mass;
            t_speed += fire.speed;
            if(fire.dir % 2 == 0) even++;
            else odd++;
        }

        t_mass /= 5;
        t_speed /= v_size;

        if(t_mass == 0) continue;

        int s_idx = ((odd == v_size) || (even == v_size)) ? 0 : 1;
        for(; s_idx<8; s_idx+=2) {
            ret.push_back({key.first, key.second, t_mass, s_idx, t_speed});
        }
    }
    
    return ret;
}

int main() {
    vector<Fire> fire_balls;
    cin >> n >> m >> k;
    bias = pow(n, 5);   // 문제 제약조건에 의해 n의 최솟값은 4, speed의 최댓값은 1000이다. 따라서 pow(n, 5)를 취하게 되면 bias값은 항상 speed보다 크다.

    for(int i=0; i<m; ++i) {
        int r, c, m, s, d;
        cin >> r >> c >> m >> s >> d;
        fire_balls.push_back({r-1, c-1, m, d, s});
    }

    for(int i=0; i<k; ++i) {
        move_fire_ball(fire_balls);
        fire_balls = divide_fire_ball(fire_balls);
    }

    int answer = 0;
    for(Fire fire_ball : fire_balls) answer += fire_ball.mass;
    cout << answer << '\n';
}
