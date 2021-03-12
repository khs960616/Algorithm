#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define INF 987654
#define MIN(a,b) (a > b ? b:a)
using namespace std;

int n, m;

int main() {
	int min = INF;
	int answer = 0;
	cin >> n >> m;
	vector<vector<int>> edge(n,vector<int>(n,INF));

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		edge[a - 1][b - 1] = edge[b-1][a-1]=1;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (j == k) continue;
				
				if (edge[j][i] < INF && edge[i][k] < INF) {
					edge[j][k] = MIN(edge[j][k], (edge[j][i] + edge[i][k]));
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		int kevin = 0;
		for (int j = 0; j < n; j++) {
			if (i == j || edge[i][j] >= INF) continue;
			kevin += edge[i][j];
		}
		if (min > kevin && kevin != 0) {
			min = kevin;
			answer = i;
		}
	}

	cout << (answer + 1);
	return 0;
}
