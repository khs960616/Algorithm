#include <bits/stdc++.h>
#define INSTALLATION 1
#define PILLAR 0
#define CEILING 1
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/60061
  2020 KAKAO BLIND RECRUITMENT
  기둥과 보 설치
  ---
  구현 시뮬레이션 
  
  ---------------------------------
    1. 격자의 선분을 어떻게 표현할것인가? 
       grid[n][n][4] -> 다음의 형태로 선분 표현이 가능하다.
       이런식으로 표현할 경우, Grid의 가장 외부의 선분을 제외하고는, 
       각 선분을 표현하는 좌표가 2개씩 중복해서 존재하므로 이를 잘 처리해야한다. 
    
      두 번쨰 생각한 방법)
      grid 사이즈를 원래 사이즈보다 1칸씩 크게 잡자.
      그리고 각 grid[n+1][n+1][2] 로 구성하자.
      좌표 (x, y)가 주어질  때 그리드가 나타내는 것은 다음과 같다. 
      grid[x+1][y+1][0]  (x, y)에 왼쪽변에 설치된 기둥이 존재하는가 ? 
      grid[x+1][y+1][1]  (x, y)에 아래쪽 변에 설치된 보가 존재하는가 ?   
      -> 이러면 동일한 변에 대해 1번만 처리하면 되므로 좀더 간략해진다.   (해당 방식 선택)
      
    2. 설치 및 삭제가 유효하며, 설치가 가능한지 검사하는 방법에 대한 고민 
       2-1) 일단 설치 및 삭제해놓고 각 칸에 대해 모든 것을 검사한다. 
       >> 2*10^5   (건설해야되는 구조물 수 * 모든 격자순회 * 보, 기둥에 대한 탐색 
    
       2-2) 설치 시 조건을 따지고, 제거 시 조건을 따로 따지는 함수를 작성
            구조물 설치의 경우 설치되는 위치를 기준으로만 판단하면 되니 비교적 간단함 
            구조물 제거의 경우 제거되는 위치뿐만 아니라 인접한 구조물에 대해서도 판단해야한다. 
            (구조물 제거 해놓고 인접한 구조물 다 bfs 식으로 넣으면서 순회)
            
       2-1) 방법을 선택하기로함 
            이유 : 2-2) bfs방식이 평균적으로는 더 빠를지 몰라도 최악의 경우 어쩌피 복잡도는 같음. 
                  복잡도가 그렇게 크지 않아, 비교적 구현이 좀 더 쉬운 방식 선택 
    
      ---------
      1. 입력으로 들어오는 좌표를 배열에 넣을 수 있는 형태로 변경하는 로직 (배열 문제에서 주어지는 좌표는 실제 배열로 넣기 위해서는 y축 좌표를 변환해 주어야함) 
      2. 전체 grid에 대한 구조물 유효성 검사.
         1-1) 보에 대한 유효성 검사 로직     (왼쪽 또는 오른쪽에 기둥이 있거나, 양쪽에 보가 존재하는 경우)
         1-2) 기둥에 대한 유효성 검사 로직    (맨 아래에 설치되거나, 보 또는 기둥 위에 존재하는 경우)
*/
int grid_size = 0;
bool build_infos[101][101][2];

pair<int, int> convert_coordinate(int x, int y) {
    return {x, grid_size-y};
}

bool is_valid_pillar(int y, int x) {
    if(y == grid_size) return true;
    
    bool is_on_pillar = build_infos[y+1][x][PILLAR];
    bool is_on_ceiling = build_infos[y][x][CEILING];
    if(x-1 >= 0) is_on_ceiling |= build_infos[y][x-1][CEILING];
    return (is_on_pillar | is_on_ceiling);
}

bool is_valid_ceiling(int y, int x) {
    if(x == grid_size || y == grid_size) return false;
    
    bool is_on_pillar = build_infos[y+1][x][PILLAR] | build_infos[y+1][x+1][PILLAR];
    bool is_middle = false;
    if(x-1>=0 && x+1 <grid_size) {
        is_middle = build_infos[y][x-1][CEILING] & build_infos[y][x+1][CEILING];
    }
    return is_on_pillar | is_middle;
}

bool is_valid_structures(int y, int x, int struct_type) {
    if(struct_type == PILLAR) {
        return is_valid_pillar(y, x);
    } else {
        return is_valid_ceiling(y, x);
    }
}

bool is_valid_operations() {
    for(int i=0; i<=grid_size; ++i) {
        for(int j=0; j<=grid_size; ++j) {
            for(int k=0; k<2; ++k) {
                if(!build_infos[i][j][k]) continue;
                if(!is_valid_structures(i, j, k)) return false;
            }
        }
    }
    return true;
}

vector<vector<int>> get_struct() {
    vector<vector<int>> ret;
    for(int i=0; i<=grid_size; ++i) {
        for(int j=0; j<=grid_size; ++j) {
            for(int k=0; k<2; ++k) {
                if(build_infos[i][j][k]) {
                    ret.push_back({j, (grid_size-i), k});
                }
            } 
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frames) {
    grid_size = n;
    for(vector<int> v: build_frames) {
        pair<int, int> arr_position = convert_coordinate(v[0], v[1]);
        int struct_type = v[2];
        int op_type = v[3];
    
        if(op_type != INSTALLATION && !build_infos[arr_position.second][arr_position.first][struct_type]) continue;
        
        bool is_installation = (op_type == INSTALLATION);
        build_infos[arr_position.second][arr_position.first][struct_type] = is_installation;
        if(!is_valid_operations()) {
            build_infos[arr_position.second][arr_position.first][struct_type] = !is_installation;
        }
    }
    return get_struct();
}
