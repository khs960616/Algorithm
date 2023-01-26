#include <bits/stdc++.h>

using namespace std;

int n, m, c_size;
vector<pair<int, int>> cams;
vector<pair<int, int>> dirs = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

/*
  https://www.acmicpc.net/problem/15683
  감시
  ---
  구현, 브루트포스 
  
  1. dirs배열에 원소 순서를 y축, x축 교차로 구성한 후, rotate를 구현하면 비교적 함수들을 간단히 구성할 수 있다.
  2. input 사이즈가 굉장히 작기 떄문에, vector의 복사 생성자를 활용하면, 카메라의 감시 구역을 정하고 다음 iteration을 위해 다시 배열을 초기 상태로 rollback하는 것을 
     별도 구현할 필요가 없어지기 때문에 로직을 단순화 시킬 수 있다.  
     (만일 rollback을 구현해야한다면, 해당 카메라에 의해 영향을 받은 영역에 대한 좌표를 저장하고, 해당 좌표들에 대해서만 rollback 해야한다.)

      
      ex)   1 0 0 0 
            0 0 0 2
            0 0 0 0  다음과 같은 배열이 주어졌을때를 생각하자. 
            
            함수 호출 순서에 의해, grid가 다음과 같은 순서로 변화할 것이다. (좌표가 유효하지 않은 경우는 순서에서 제외하였다.)
           
            1 # # # 
            0 0 0 2
            0 0 0 0       2번 감시 카메라는 최초에 위 아래 방향을 감시하게 되면 

            1 # # # 
            0 0 0 2
            0 0 0 #       2번 카메라가 좌 우 방향을 감시하는 것을 시뮬레이션 하기 위해서는 2번 카메라가 현재 감시중인 영역을 rollback 해야하는데, 
                          이때 (0, 3) 영역을 초기화 해버리면 로직이 깨지게 된다.
                          따라서 롤백을 별도로 구현하고자한다면 2번 감시카메라에 의해서 꺼진 영역인 (2, 3)만 다시 롤백할 수 있도록 좌표를 저장하는 방식으로 구현할 수 있다.
                          
*/
bool is_valid(int y, int x) {
	return (y >= 0 && y < n) && (x >= 0 && x < m);
}

int calc_blind_spot(vector<vector<int>>& grids) {
	int ret = 0;
	for (vector<int> grid : grids) {
		for (int n : grid) {
			if (n == 0) ret++;
		}
	}
	return ret;
}

void monitor(vector<vector<int>>& grid, int c_idx, int d_idx) {
	int ny = cams[c_idx].first, nx = cams[c_idx].second;

	while (1) {
		ny += dirs[d_idx].first;
		nx += dirs[d_idx].second;
		if (!is_valid(ny, nx) || grid[ny][nx] == 6) return;
		if (grid[ny][nx] == 0) grid[ny][nx] = -1;
	}
}

vector<vector<int>> montior_by_cam_type(vector<vector<int>> v, int c_idx, int iter) {
	int cam_type = v[cams[c_idx].first][cams[c_idx].second];

	switch (cam_type) {
		case 1:
			monitor(v, c_idx, (0 + iter) % 4);
			break;
		case 2:
			monitor(v, c_idx, (0 + iter) % 4);
			monitor(v, c_idx, (2 + iter) % 4);
			break;
		case 3:
			monitor(v, c_idx, (0 + iter) % 4);
			monitor(v, c_idx, (1 + iter) % 4);
			break;
		case 4:
			monitor(v, c_idx, (0 + iter) % 4);
			monitor(v, c_idx, (1 + iter) % 4);
			monitor(v, c_idx, (2 + iter) % 4);
			break;
		default:
			monitor(v, c_idx, 0);
			monitor(v, c_idx, 1);
			monitor(v, c_idx, 2);
			monitor(v, c_idx, 3);
			break;
	}
	return v;
}

void solve(vector<vector<int>> v, int c_idx, int& answer) {
	if (c_idx == c_size) {
		answer = min(answer, calc_blind_spot(v));
		return;
	}

	int cam_type = v[cams[c_idx].first][cams[c_idx].second];
	int iter = 1;
	if (cam_type != 5) iter = (cam_type == 2) ? 2 : 4;

	for (int i = 0; i < iter; ++i) {
		solve(montior_by_cam_type(v, c_idx, i), c_idx + 1, answer);
	}
}

int main() {
	cin >> n >> m;
	vector<vector<int>> v(n, vector<int>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> v[i][j];
			if (v[i][j] >= 1 && v[i][j] <= 5) cams.emplace_back(i, j);
		}
	}
	
	int answer = INT_MAX;
	c_size = cams.size();
	solve(v, 0, answer);
	cout << answer;
	return 0;
}
