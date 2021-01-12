#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

struct index_info {
	int x;
	int y;
};

index_info operator+(index_info a, index_info b) {
	index_info result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

struct index_info direction[4] = { {1,0},{-1,0},{0,1},{0,-1} };
int n;
int apartment[25][25];

bool isValid(index_info &info) {
	if (info.x<0 || info.y <0 || info.x >=n || info.y>=n) return false;
	return true;
}

int main() {
	vector<index_info> arr;
	vector<int> answer;
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%1d", &apartment[i][j]);
			if (apartment[i][j] == 1) arr.push_back({ j,i });
		}
	}

	for (int i = 0; i < arr.size(); i++) {
		if (apartment[arr[i].y][arr[i].x] != 1) continue;
		int count = 1;
		queue<index_info> que;
		que.push(arr[i]);
		apartment[arr[i].y][arr[i].x] = 2;

		while (!que.empty()) {
			index_info current = que.front();
			que.pop();
			for (int i = 0; i < 4; i++) {
				index_info next = current + direction[i];
				if (!isValid(next)) continue;
				if (apartment[next.y][next.x] != 1) continue;

				apartment[next.y][next.x] = 2;
				que.push({next.x, next.y});
				count++;
			}
		}
		answer.push_back(count);
	}

	sort(answer.begin(), answer.end());
	cout << answer.size() << endl;

	for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;

	return 0;
}
