#include <bits/stdc++.h>
#define ALPHA -1
using namespace std;

/*
  https://www.acmicpc.net/problem/20057
  마법사 상어와 토네이토
  ---
  구현, 시뮬레이션 
  
  필요한 데이터 구조
  1. 현재 태풍의 위치, 현재 태풍의 진행방향으로 몇 칸 이동해야하는지 정보 
  2. 모래를 흩날리는 정보를 가지는 window 
    (단순 하드 코딩으로 인덱스로 때려박으면 코드 중복도 심하고, 복잡하다고 느낌 > 따라서 정보를 담은 배열을 하나 두고, 반시계 방향으로 90도씩 회전시키며 활용함)
  3. 현재 모래의 정보를 가지고 있는 n*n 크기의 격자 
  
  ---
  필요한 기능
  1. 태풍의 눈을 이동시키는 기능 (결국 한칸씩 이동하며 모래를 흩날려야 되기 떄문에 구조상 함수로 따로 분류하지는 않았음)
  2. 모래를 흩날리는 정보를 가지고 있는 window를 반시계 방향으로 90도씩 회전하는 기능
  3. 모래를 흩날리는 기능 
*/

int n;
int typoon_eye_y = 0, typoon_eye_x = 0, move_scale = 0;
int answer = 0;
vector<pair<int, int> > dirs = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
vector<vector<int> > windows = {{0,0,2,0,0}, {0, 10, 7, 1, 0}, {5, ALPHA, 0, 0, 0}, {0, 10, 7, 1, 0}, {0, 0, 2, 0, 0}};

bool is_valid(int y, int x) {
    return y>=0 && y<n && x>=0 && x<n;
}

void rotate_window() {
    vector<vector<int>> tmp = windows;
    for(int i=0; i<5; ++i) {      
        for(int j=0; j<5; ++j) {
            windows[4-j][i] = tmp[i][j];
        }
    }
}

// scatter_sand에서 if-else와 코드 중복을 되도록 줄이기 위해 hash map을 사용해서 각 percentage에 맞는 모래의 양을 꺼내쓰도록 구성함
unordered_map<int, int> get_scatter_info(int current_sand) {
    unordered_map<int, int> ret;
    ret[0] = 0;
    ret[1] = current_sand / 100;
    ret[2] = current_sand / 50;
    ret[5] = current_sand / 20;
    ret[7] = (current_sand * 7) / 100;
    ret[10] = current_sand / 10;
    ret[ALPHA] = (current_sand-ret[5]-2*(ret[1]+ret[2]+ret[7]+ret[10]));
    return ret;
}

void scatter_sand(vector<vector<int> >& v) {
    int current_sand = v[typoon_eye_y][typoon_eye_x];
    v[typoon_eye_y][typoon_eye_x] = 0;
    unordered_map<int, int> info = get_scatter_info(current_sand);
    for(int i=typoon_eye_y-2; i<typoon_eye_y+3; ++i) {
        for(int j=typoon_eye_x-2; j<typoon_eye_x+3; ++j) {
            int percentage = windows[i-typoon_eye_y+2][j-typoon_eye_x+2];
            int add_value = info[percentage];
            if(!is_valid(i, j)) {
                answer += add_value;
                continue;
            }
            v[i][j] += add_value;
        }
    }
}

void move_typoon(vector<vector<int> >& v) {
    while(1) {
        for(int i=0; i<4; ++i) {
/*
그림을 관찰해보면 동->서, 서->동으로 이동할때마다 이동해야하는 칸이 1칸씩 증가한다. 
마지막에 동->서쪽으로 이동할때는 이동해야될 칸이 증가하지 않으나, 
종료조건에 의해 이동이 무시되므로 별도로 고려하지 않음 
*/
            if(i % 2 == 0) move_scale++;  
            int move_cnt = move_scale;

            while(move_cnt--) {
                typoon_eye_y += dirs[i].first;
                typoon_eye_x += dirs[i].second;
                scatter_sand(v);
                if(typoon_eye_y == 0 && typoon_eye_x == 0) return;
            }
            rotate_window();
        }
    }
}

int main() {
    cin >> n;
    typoon_eye_y = typoon_eye_x = n/2;

    vector<vector<int> > v(n, vector<int>(n, 0));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            cin >> v[i][j];
        }
    }

    move_typoon(v);
    cout << answer << '\n';
}
