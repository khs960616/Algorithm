#include <bits/stdc++.h>

using namespace std;

/*
  https://www.acmicpc.net/problem/16234
  인구이동
  --
  구현, 시뮬레이션, bfs
  
  50*50 * 2000
  
  1. 모든 나라를 방문하며 인접하는 국가와 인구 차이가 l이상, r이하인 경우 같은 그룹으로 묶는다.
     이 때, bfs로 사방탐색을 하며 모든 국가를 체크한다.
     (탐색 이후, 같은 그룹에 속하는 모든 국가의 값은 평균값으로 변화되야하므로 모든 좌표를 저장한다.)
  
  2. 1을 통해 그룹핑한 모든 나라의 인구값을, 그룹의 인구 평균값으로 수정한다.  
  3. 더 이상 값이 변화하지 않을 때 까지 1과 2에 과정을 반복한다. 
  
*/

vector<pair<int, int>> dirs = { {0, 1}, {-1, 0}, {0, -1}, {1, 0} };
int n, l, r;
int a[50][50];
bool is_visit[50][50];

bool is_valid(int y, int x) {
	return (y >= 0 && y < n) && (x >= 0 && x < n);
}

int bfs(int y, int x) {
	vector<pair<int, int> > p;
	p.emplace_back(y, x);
	int sum = a[y][x];

	queue<pair<int, int>> q;
	q.emplace(y, x);
	is_visit[y][x] = true;

	while (!q.empty()) {
		pair<int, int> cur_pos = q.front();
		int prev_cost = a[cur_pos.first][cur_pos.second];
		q.pop();

		for (pair<int, int>& dir : dirs) {
			int ny = cur_pos.first + dir.first;
			int nx = cur_pos.second + dir.second;
			if (!is_valid(ny, nx) || is_visit[ny][nx]) continue;

			int diff = abs(a[ny][nx] - prev_cost);
			if (diff >= l && diff <= r) {
				is_visit[ny][nx] = true;
				p.emplace_back(ny, nx);
				q.emplace(ny, nx);
				sum += a[ny][nx];
			}
		}
	}

	sum /= p.size();
	for (pair<int, int> city : p) a[city.first][city.second] = sum;
	return p.size() - 1;
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	
	cin >> n >> l >> r;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> a[i][j];
		}
	}

	int answer = 0;
	while (1) {
		int cnt = 0;
		memset(is_visit, false, sizeof(is_visit));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (is_visit[i][j]) continue;
				cnt += bfs(i, j);
			}
		}

		if (cnt == 0) break;
		answer++;
	}

	cout << answer;
	return 0;
}
