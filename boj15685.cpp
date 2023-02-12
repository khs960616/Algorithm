#include <bits/stdc++.h>


/*
  https://www.acmicpc.net/problem/15685
  드래곤 커브
  ---
  1. 원점 기준 좌표계에서 현재 커브의 가장 끝점을 기준으로 하는 좌표계로 모든 좌표들을 변환한다.
      > (마지막점 좌표가 (X, Y)라면 다른 모든 좌표에 (-x, -y) 만큼 해준다. 
      
  2. 시계방향으로 90도 회전변환 시킨다. 
  
  3. 회전변환 후 모든 좌표들을 다시 원점 좌표계를 기준으로 돌린다.
*/
using namespace std;

int n;
int arr[101][101];
vector<pair<int, int>> dirs = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

bool is_valid(int x, int y) {
	return (x >= 0 && x < 101) && (y >= 0 && y < 101);
}

deque<pair<int, int>> getAddCoordinate(deque<pair<int, int>>& dq) {
	deque<pair<int, int>> ret(dq);
	return ret;
}

void insertValue(deque<pair<int, int>>& dq, int x, int y) {
	if (is_valid(x, y)) arr[x][y] = 1;
	dq.emplace_back(x, y);
}

void translation(deque<pair<int, int>>& dq, int dir) {
	pair<int, int> base = dq.back();
	base.first *= dir; base.second *= dir;
	int len = dq.size();
	for (int i = 0; i < len - 1; ++i) {
		dq[i].first += base.first;
		dq[i].second += base.second;
	}
}

void rotate(pair<int, int>& p) {
	p.first ^= p.second;
	p.second ^= p.first;
	p.first ^= p.second;
	p.first *= -1;
}

void rotateAll(deque<pair<int, int>>& dq) {
	int len = dq.size();
	for (int i = 0; i < len - 1; ++i) rotate(dq[i]);
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		deque<pair<int, int>> dq;
		insertValue(dq, x, y);
		insertValue(dq, x + dirs[d].first, y + dirs[d].second);

		while (g--) {
			deque<pair<int, int>> tmp = getAddCoordinate(dq);
			translation(tmp, -1);
			rotateAll(tmp);
			translation(tmp, 1);
			tmp.pop_back();

			while (!tmp.empty()) {
				insertValue(dq, tmp.back().first, tmp.back().second);
				tmp.pop_back();
			}
		}
	}

	int answer = 0;
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			int val = arr[i][j] + arr[i][j + 1] + arr[i + 1][j] + arr[i + 1][j + 1];
			if (val == 4) answer++;
		}
	}

	cout << answer;
	return 0;
}
