#include <bits/stdc++.h>

using namespace std;

/*
  https://www.acmicpc.net/problem/17140
  이차원 배열과 연산
  --
  구현, 시뮬레이션 
*/
int arr[101][101];
int row_size = 3, col_size = 3;

void r_operation() {
	int ret = col_size;
	map<int, int> count_map;

	for(int i=1; i<=row_size; ++i) {
		for(int j=1; j<=col_size; ++j) {
			if(arr[i][j] == 0) continue;
			count_map[arr[i][j]]++;
		}
		priority_queue<pair<int, int> > pq;
		for(auto i: count_map) pq.emplace(-i.second, -i.first);

		int inc = 0;
		while(!pq.empty() && inc < 100) {
			pair<int, int> p = pq.top();
			pq.pop();
			arr[i][++inc] = -p.second;
			arr[i][++inc] = -p.first;
		}

		for(int j=inc+1; j<101; ++j) arr[i][j] = 0;
		count_map.clear();
		ret = max(ret, inc);
	}

	col_size = ret;
}

void c_operation() {
	int ret = row_size;
	map<int, int> count_map;

	for(int i=1; i<=col_size; ++i) {
		for(int j=1; j<=row_size; ++j) {
			if(arr[j][i] == 0) continue;
			count_map[arr[j][i]]++;
		}
		priority_queue<pair<int, int> > pq;
		for(auto i: count_map) pq.emplace(-i.second, -i.first);

		int inc = 0;
		while(!pq.empty() && inc < 100) {
			pair<int, int> p = pq.top();
			pq.pop();
			arr[++inc][i] = -p.second;
			arr[++inc][i] = -p.first;
		}

		for(int j=inc+1; j<101; ++j) arr[j][i] = 0;
		count_map.clear();
		ret = max(ret, inc);
	}

	row_size = ret;
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	int r, c, k;
	cin >> r >> c >> k;
	for(int i=1; i<=3; ++i) {
		for(int j=1; j<=3; ++j) {
			cin >> arr[i][j];
		}
	}

	int answer = -1;
	for(int i=0; i<101; ++i) {
		if(arr[r][c] == k) {
			answer = i;
			break;
		}

		if(row_size >= col_size) r_operation();
		else c_operation();
	}

	cout << answer;
	return 0;
}
