#include <bits/stdc++.h>

using namespace std;

/*
  https://www.acmicpc.net/problem/15684
  사다리 조작 
  ---
  구현
*/

int answer = INT_MAX;
int n, m, h;
int space[31][10]; // space[i][j] -> 높이가 i인 곳에서 j ~ j+1를 연결하는 가로선의 위치 

void brute_force(int cnt, int row) {
	if (answer == 0) return;
	if (cnt > min(answer, 3)) return;
	bool is_valid = true;
	for (int i = 1; i <= n; ++i) {
		if (!is_valid) break;
		int last = i;
		for (int height = 1; height <= h; ++height) {
			if (last != 1 && space[height][last - 1]) last--;
			else if (last != n && space[height][last]) last++;
		}
		if (i != last) is_valid = false;
	}
	if (is_valid) {
		answer = min(answer, cnt);
		return;
	}

	for (int i = row; i <= h; ++i) {
		for (int j = 1; j < n; ++j) {
			if (space[i][j] == 1) {
				j += 1;
				continue;
			}

			space[i][j] = 1;
			brute_force(cnt + 1, i);
			space[i][j] = 0;
		}
	}
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	cin >> n >> m >> h;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		space[a][b] = 1;
	}

	brute_force(0, 1);
	answer = (answer == INT_MAX) ? -1 : answer;
	cout << answer;
	return 0;
}
