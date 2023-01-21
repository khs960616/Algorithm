#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/1976
  여행가자
  --
  union-find 
*/
int parents[200];

int find_parent(int node) {
	if(parents[node] == node) return node;
	return parents[node] = find_parent(parents[node]);
}

void merge_sub_set(int node1, int node2) {
	int p1 = find_parent(node1);
	int p2 = find_parent(node2);
	parents[max(p1, p2)] = min(p1, p2);
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; ++i) parents[i] = i;
	
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			int is_connected;
			cin >> is_connected;
			if(is_connected) merge_sub_set(i, j);
		}
	}

	int base_sub_set;
	string answer = "YES";
	cin >> base_sub_set;
	base_sub_set = find_parent(base_sub_set-1);
	
	for(int i=1; i<m; ++i) {
		int node = 0;
		cin >> node;
		if(base_sub_set != find_parent(node-1)) answer = "NO";
	}
	cout << answer;
	return 0;
}
