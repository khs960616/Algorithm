#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/12100
  2048(Easy)
  ---
  구현, 시뮬레이션
  
  1. 각 좌표를 저장한다.
  2. 이동 방향을 기준으로 우선순위가 높은 순위별로 정렬한다.
  3. 이동 시킨다.
  4. 서로 인접한 노드의 값이 같으면 합친다. 
  5. 이동시킨다.
  
  -> 모든 경우 대해 해당 연산을 반복 
  
  구현을 단순화하기 위해, 노드들의 이동, 정렬, 머지 과정을 별도로 분리함 
*/
int n, answer;

vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool is_valid(int y, int x) {
	return (y>=0 && y<n) && (x>=0 && x<n);
}

bool y_greater(tuple<int, int, int> t1, tuple<int, int, int> t2) {
	return get<0>(t1) > get<0>(t2);
}

bool x_less(tuple<int, int, int> t1, tuple<int, int, int> t2) {
	return get<1>(t1) < get<1>(t2);  
}

bool x_greater(tuple<int, int, int> t1, tuple<int, int, int> t2) {
	return get<1>(t1) > get<1>(t2);
}

void sortByDir(vector<tuple<int, int, int>>& blocks, int dir) {
	switch(dir) {
		case 0:
			sort(blocks.begin(), blocks.end());
			break;
		case 1:
			sort(blocks.begin(), blocks.end(), x_greater);
			break;
		case 2:
			sort(blocks.begin(), blocks.end(), y_greater);
			break;
		case 3:
			sort(blocks.begin(), blocks.end(), x_less);
			break;
	}
}

void move_blocks(vector<tuple<int, int, int>>& blocks, int dir) {
	vector<vector<bool> > is_visit(n, vector<bool>(n, false));
	sortByDir(blocks, dir);

	for(auto& [y, x, cost] : blocks) {
		while(1) {
			int ny = y+dirs[dir].first;
			int nx = x+dirs[dir].second;
			if(!is_valid(ny, nx) || is_visit[ny][nx]) break;
			y = ny;
			x = nx;
		}
		is_visit[y][x] = true;
	}
}

vector<tuple<int, int, int>> merge_blocks(vector<tuple<int, int, int>>& blocks, int dir) {
	vector<tuple<int, int, int>> merge_blocks;

	for(auto& [y, x, cost] : blocks) {
		bool flag = true;
		for(auto& [prev_y, prev_x, prev_cost]: merge_blocks) {
			if((prev_y == y+dirs[dir].first) && (prev_x == x+dirs[dir].second)) {
				if(cost == prev_cost) {
					flag = false;
					prev_cost+=cost;
				}
			}
		}
		if(flag) merge_blocks.emplace_back(y, x, cost);
	}

	return merge_blocks;
}

void solve(int cnt, int dir, vector<tuple<int, int, int>> blocks) {
	if(cnt == 5) {
		for(auto& [y, x, cost]: blocks) answer = max(answer, cost);
		return;
	} 

	move_blocks(blocks, dir);
	blocks = merge_blocks(blocks, dir);
	move_blocks(blocks, dir);
	for(int i=0; i<4; ++i) solve(cnt+1, i, blocks);
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	cin >> n;
	vector<tuple<int, int, int>> blocks;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			int num;
			cin >> num;
			if(num) blocks.emplace_back(i, j, num);
		}
	}

	for(int i=0; i<4; ++i) solve(0, i, blocks);
	cout << answer;
	return 0;
}
