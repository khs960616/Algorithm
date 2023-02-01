#include <bits/stdc++.h>

using namespace std;

/*
  https://www.acmicpc.net/problem/17142
  연구소 3
  브루트포스, 조합, bfs
  ---
  1. 시간복잡도 
     bfs시 배열 전체를 탐색할 수도 있으므로 50*50, 최대 10개의 바이러스중 m개의 바이러스를 선택 (10 C m) -> m=5일때 최대 252개 정도밖에 안됨 
     >> n^2 * 10Cm 정도지만 input 사이즈가 상당히 작으므로 브루트포스로 접근.
  
  2. 필요 기능
     1. 바이러스를 활성화할 수 있는 지역 중 m개의 원소 고르기 (순서 상관x)
     2. 각 바이러스를 전파하는 기능
     3. 전체 배열이 빈칸없이 가득  채워졌는지 확인하능 기능 
     
  3. 구현 
     1. 콜스택을 활용해서 selected_virus_idx함수에 선택된 바이러스 인덱스를 저장 
     2. queue를 사용해서 bfs를 구현 바이러스가 활성화 되어 전파된 공간은 방문여부를 나타내기 위해 -1로 변경해준다.
     
        바이러스가 전파 가능한 공간은, 아직 활성화되지 않은 바이러스가 위치한 곳과 빈칸이다. 
        이 때, 활성화 되지 않은 바이러스는 초기부터 바이러스가 존재했던 곳이므로 cost를 계산할 떄는 제외되어야한다. 
*/

int n, m;
int virus_cnt, empty_cnt;
int answer = INT_MAX;
vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
vector<pair<int, int>> virus_pos;
int selected_virus_idx[10];

bool is_valid(int y, int x) {
	return (y>=0 && y<n) && (x>=0 && x<n);
}

int get_virus_propagate_time(vector<vector<int>> arr) {
	int ret = 0;
	int propagate_cnt = 0;

	queue<tuple<int, int, int>> q;
	for(int i=0; i<m; ++i) {
		int y = virus_pos[selected_virus_idx[i]].first, x = virus_pos[selected_virus_idx[i]].second;
		q.emplace(y, x, 0);
		arr[y][x] = -1;
	}

	while(!q.empty()) {
		auto [cy, cx, cost] = q.front();
		q.pop();

		for(pair<int, int> dir: dirs) {
			int ny = cy + dir.first;
			int nx = cx + dir.second;
			if(!is_valid(ny, nx) || arr[ny][nx] == 1 || arr[ny][nx] == -1) continue;

			if(arr[ny][nx] == 0) {
				propagate_cnt++;
				ret = max(ret, cost+1);
			}
			arr[ny][nx] = -1;
			q.emplace(ny, nx, cost+1);
		}
	}
	return (propagate_cnt == empty_cnt) ? ret : INT_MAX;
}

void solve(vector<vector<int>>& arr, int idx, int selected_cnt) {
	if(selected_cnt == m) {
		answer = min(answer, get_virus_propagate_time(arr));
		return;
	}

	if(idx == virus_cnt) return;
	for(int i=idx; i<virus_cnt; ++i) {
		selected_virus_idx[selected_cnt] = i;
		solve(arr, i+1, selected_cnt+1);
	}
}

int main() {
	cin >> n >> m;
	vector<vector<int>> arr(n, vector<int> (n));
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			cin >> arr[i][j];
			if(arr[i][j] == 0) empty_cnt++;
			if(arr[i][j] == 2) virus_pos.emplace_back(i, j);
		}
	}
	virus_cnt = virus_pos.size();

	solve(arr, 0, 0);
	if(answer == INT_MAX) cout << -1;
	else cout << answer;
	return 0;
}
