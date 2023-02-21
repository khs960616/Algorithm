#include <bits/stdc++.h>

using namespace std;


/*
  https://www.acmicpc.net/problem/21608
  상어초등학교
  --
  구현, 시뮬레이션 
*/
vector<pair<int, int> > dirs = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
int preferences[401][4];
int arr[21][21];
int n;

bool is_valid(int y, int x) {
	return (y >= 1 && y <= n) && (x >= 1 && x <= n);
}

pair<int, int> get_current_position_info(int y, int x, int student_num) {
	int preference_cnt = 0, empty_space_cnt = 0;

	for (int i = 0; i < 4; ++i) {
		int ny = y + dirs[i].first;
		int nx = x + dirs[i].second;

		if (!is_valid(ny, nx)) continue;
		if (arr[ny][nx] == 0) empty_space_cnt++;
		else {
			for (int i = 0; i < 4; ++i) {
				if (preferences[student_num][i] == arr[ny][nx]) {
					preference_cnt++;
					break;
				}
			}
		}
	}
	return {preference_cnt, empty_space_cnt};
}

pair<int, int> get_student_position(int student_num) {
	int y = 0, x = 0, max_adj_preference = -1,  max_empty_space = -1;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (arr[i][j] != 0) continue;

			pair<int, int> info = get_current_position_info(i, j, student_num);
			if (max_adj_preference < info.first || (max_adj_preference == info.first && max_empty_space < info.second)) {
				max_adj_preference = info.first;
				max_empty_space = info.second;
				y = i; x = j;
			}
		}
	}
	return {y, x};
}

int calc_cost() {
	int ret = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int preference_cnt = get_current_position_info(i, j, arr[i][j]).first;

			if (!preference_cnt) continue;
			ret += pow(10, preference_cnt-1);
		}
	}
	return ret;
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	cin >> n;
	int student_cnt = n * n;

	for (int i = 1; i <= student_cnt; ++i) {
		int student_num;
		cin >> student_num;
		for (int j = 0; j < 4; ++j) cin >> preferences[student_num][j];
		pair<int, int> pos = get_student_position(student_num);
		arr[pos.first][pos.second] = student_num;
	}

	cout << calc_cost();
	return 0;
}
