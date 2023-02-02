#include <bits/stdc++.h>
#define MAX_SIZE 100000
using namespace std;

/*
  https://www.acmicpc.net/problem/1647
  도시분할계획
  ---
  1. 최소 스패닝 트리를 구한다.
  2. 최소 스패닝 트리를 구성하는 edge중 cost가 가장 작은 것을 제외한다.
  
  크루스칼 알고리즘 사용
*/
int n, m;
int sub_set[MAX_SIZE];

int get_root(int node) {
	if (sub_set[node] == node) return node;
	return sub_set[node] = get_root(sub_set[node]);
}

bool merge(int node1, int node2) {
	int root1 = get_root(node1);
	int root2 = get_root(node2);

	if (root1 == root2) return false;
	sub_set[max(root1, root2)] = min(root1, root2);
	return true;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) sub_set[i] = i;
	
	priority_queue<tuple<int, int, int>> pq;
	for (int i = 0; i < m; ++i) {
		int from, to, cost;
		cin >> from >> to >> cost;
		pq.emplace(-cost, from, to);
	}

	int answer = 0;
	int max_weight = -1;
	while (!pq.empty()) {
		int cost = -get<0>(pq.top());
		int node1 = get<1>(pq.top());
		int node2 = get<2>(pq.top());
		pq.pop();

		if (merge(node1-1, node2-1)) {
			answer += cost;
			max_weight = max(max_weight, cost);
		}
	}

	cout << answer-max_weight;
	return 0;
}
