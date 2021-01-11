#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

int m, n, h;
int box[100][100][100];

struct tomato_info {
	int i;
	int j;
	int k;
	int time;
};

struct tomato_info direction[6] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{-1,0,0,0},{0,-1,0,0},{0,0,-1,0} };

tomato_info operator+(tomato_info a, tomato_info b) {
	tomato_info result;
	result.i = a.i + b.i;
	result.j = a.j + b.j;
	result.k = a.k + b.k;
	return result;
}

bool isValidCoordinate(tomato_info &target) {
	if (target.i < 0 || target.i >= h) return false;
	if (target.j < 0 || target.j >= n) return false;
	if (target.k < 0 || target.k >= m) return false;
	return true;
}

int main() {
	queue<tomato_info> que;
	tomato_info current_info;
	cin >> m >> n >> h;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				cin >> box[i][j][k];
				if (box[i][j][k] == 1) {
					que.push({i,j,k,0});
				}
			}
		}
	}

	while (!que.empty()) {
		current_info = que.front();
		que.pop();
		for (int i = 0; i < 6; i++) {
			tomato_info dir = current_info + direction[i];
			if (!isValidCoordinate(dir)) continue;
			if (box[dir.i][dir.j][dir.k]) continue;
			box[dir.i][dir.j][dir.k] = 1;
			que.push({dir.i,dir.j,dir.k,(current_info.time+1)});
		}
	}

	if (que.empty()) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < m; k++) {
					if (box[i][j][k] == 0) {
						current_info.time = -1;
						i = h;
						j = n;
						break;
					}
				}
			}
		}
	}

	cout << current_info.time;
	return 0;
}
