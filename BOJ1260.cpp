#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

bool isConnected[1001][1001];
bool isVisit[1001];

void DFS(int v, int n) {
	isVisit[v] = true;
	cout << v << ' ';
	for (int i = 1; i <= n; i++) {
		if (!isVisit[i]) {
			if (isConnected[v][i]) DFS(i, n);
		}
	}
}

void BFS(int v, int n) {
	queue <int> que;
	que.push(v);
	isVisit[v] = true;

	while (!que.empty()) {
		int preNum = que.front();
		cout << preNum << ' ';
		que.pop();

		for (int i = 1; i <= n; i++) {
			if (!isVisit[i]) {
				if (isConnected[preNum][i]) {
					isVisit[i] = true;
					que.push(i);
				}
			}
		}
	}
	cout << endl;
}


int main() {
	std::ios::sync_with_stdio(false); cin.tie(0);
	int n = 0, m = 0, v=0;
	cin >> n >> m >> v;

	for (int i = 0; i < m; i++) {
		int x = 0, y = 0;
		cin >> x >> y;
		isConnected[x][y] = true;
		isConnected[y][x] = true;
	}

	DFS(v, n);
	cout << endl;
	memset(isVisit, false, sizeof(isVisit));
	BFS(v, n);
}
