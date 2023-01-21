#include <bits/stdc++.h>
#define MERGE_CODE 0
using namespace std;

vector<int> parents;

/*
  https://www.acmicpc.net/problem/1717
  집합의 표현 
  --
  union-find 
*/

int find_parent(int node) {
	if (parents[node] == node) return node;
	return parents[node]= find_parent(parents[node]);
}

void merge_sub_set(int node1, int node2) {
	int p1 = find_parent(node1);
	int p2 = find_parent(node2);

	if (p1 == p2) return;
	parents[max(p1, p2)] = min(p1, p2);
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m; 
	for (int i = 0; i <= n; ++i) parents.push_back(i);

	for (int i = 0; i < m; ++i) {
		int op, node1, node2;
		cin >> op >> node1 >> node2;

		if (op == MERGE_CODE) {
			merge_sub_set(node1, node2);
		}
		else {
			if (find_parent(node1) == find_parent(node2)) cout << "YES\n";
			else cout << "NO\n";
		}
	}
	return 0;
}
