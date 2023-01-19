#include <bits/stdc++.h>
using namespace std;

double answer = DBL_MAX;
int T, N;
int coordinates[20][2];
bool is_visited[20];

/*
	https://www.acmicpc.net/problem/1007
	* 벡터 매칭 
	--
	브루트 포스, 조합 
	---
	solve)
		0. 
			벡터 -> (종점y좌표 - 출발점 y좌표, 종점x좌표 - 시작점 x좌표)
			벡터 합 -> (각 벡터의 y좌표의 합, X좌표의 합)
			벡터의 크기 -> 원점(0, 0), 에서 벡터의 위치까지 거리의 스칼라 크기

		1. 벡터의 총합을 구하기 위해서 각 벡터를 별도로 저장할 필요가 없다. 
		2. 0과 1의 이유로, 문제를 단순화하면 총 N개의 정점중 N/2개의 정점을 선택하는 문제로 바뀜
*/

double get_total_vector_sums() {
	int y = 0, x = 0;
	for (int i = 0; i < N; ++i) {
		y += is_visited[i] ? -coordinates[i][0] : coordinates[i][0];
		x += is_visited[i] ? -coordinates[i][1] : coordinates[i][1];
	}
	return sqrt((pow(y, 2) + pow(x, 2)));
}

void solve(int idx, int cnt) {
	if (cnt == N / 2) {
		answer = min(answer, get_total_vector_sums());
		return;
	}

	for (int i = idx; i < N; ++i) {
		if (is_visited[i]) continue;
		is_visited[i] = true;
		solve(i + 1, cnt + 1);
		is_visited[i] = false;
	}
}

int main() {
	cin >> T;
	cout << fixed;
	cout.precision(7);

	for (int test_case = 0; test_case < T; ++test_case) {
		memset(is_visited, false, sizeof(is_visited));
		answer = DBL_MAX;
		cin >> N;
		for (int i = 0; i < N; ++i) cin >> coordinates[i][0] >> coordinates[i][1];
		solve(0, 0);
		cout << answer << '\n';
	}
	return 0;
}
