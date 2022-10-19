#include <bits/stdc++.h>
#define AIR_CLEANER -1
using namespace std;

/*
  https://www.acmicpc.net/problem/17144
  미세먼지 안녕!
  --
  구현, 시뮬레이션 
  (배열 다루기) 
*/
int R, C, T;
vector<vector<int> > house;
vector<pair<int, int> > air_cleaner;
vector<pair<int, int> > dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool is_valid(int y, int x) {
    return (y>=0 && y<R) && (x>=0 && x<C);
}

void dust_diffusion(vector<vector<int> >& diffusion, int y, int x) {
    int cnt = 0;
    int quantity = house[y][x] / 5;

    for(pair<int, int> dir: dirs) {
        int next_y = y+dir.first;
        int next_x = x+dir.second;

        if(!is_valid(next_y, next_x)) continue;
        if(house[next_y][next_x] == AIR_CLEANER) continue;
        diffusion[next_y][next_x] += quantity;
        cnt++;
    }
    house[y][x] -= (quantity * cnt);
}

void diffusion_step() {
    vector<vector<int> > diffusion(R, vector<int>(C, 0));

    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            if(house[i][j] == AIR_CLEANER) continue;
            dust_diffusion(diffusion, i, j);
        }
    }

    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            house[i][j] += diffusion[i][j];
        }
    }
}

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void clear_top_side() {
    int y = air_cleaner[0].first;
    int x = air_cleaner[0].second;
    int prev_dust = house[y][x+1];
    house[y][x+1] = 0;

    for(int i = x+2; i<C; ++i) swap(prev_dust, house[y][i]);
    for(int i = y-1; i>=0; --i) swap(prev_dust, house[i][C-1]);
    for(int i = C-2; i>=0; --i) swap(prev_dust, house[0][i]);
    for(int i = 1; i<y; ++i) swap(prev_dust, house[i][0]);
}

void clear_bottom_side() {
    int y = air_cleaner[1].first;
    int x = air_cleaner[1].second;
    int prev_dust = house[y][x+1];
    house[y][x+1] = 0;

    for(int i = x+2; i<C; ++i) swap(prev_dust, house[y][i]);
    for(int i = y+1; i<R; ++i) swap(prev_dust, house[i][C-1]);
    for(int i = C-2; i>=0; --i) swap(prev_dust, house[R-1][i]);
    for(int i = R-2; i>y; --i) swap(prev_dust, house[i][0]);
    
}

void air_clean_step() {
    clear_top_side();
    clear_bottom_side();
}

int get_total_dust_quantity() {
    int ret = 2;
    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            ret += house[i][j];
        }
    }
    return ret;
}

int main() {
    cin >> R >> C >> T;
    house = vector<vector<int> >(R, vector<int> (C, 0));

    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            cin >> house[i][j];
            if(house[i][j] == AIR_CLEANER) {
                air_cleaner.emplace_back(i, j);
            }
        }
    }

    for(int i=0; i<T; ++i) {
        diffusion_step();
        air_clean_step();
    }

    cout << get_total_dust_quantity() << '\n';
    return 0;
}
