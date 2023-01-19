#include <bits/stdc++.h>

using namespace std;

/*
  https://www.acmicpc.net/problem/1197
  최소 스패닝 트리 
  ---
  스패닝 트리 : 그래프의 모든 정점을 연결하는 그래프 중, 최소한의 간선을 유지하는 트리 
  
  크루스칼 알고리즘
  - 간선 이동 비용에 대한 오름 차순 정렬한다.
  - 비용이 적은 간선부터 선택하며 트리를 구성한다. 단 이 때 트리에서 싸이클을 만드는 간선은 선택하지 않는다. 
  
  union find 
  - 여러 노드가 존재할 떄, 특정 노드들이 서로 같은 집합에 속하는지를 알고 싶을 떄 사용하는 알고리즘 
  - 각 서브셋에 대해 parent배열을 활용한다. 
*/

int V, E;
int  parents[10001];
priority_queue<tuple<int, int, int>> edges;

int find_sub_set_root(int node) {
	if(node == parents[node]) return parents[node];
	return parents[node] = find_sub_set_root(parents[node]);
}

bool is_same_sub_set(int y, int x) {
	return (find_sub_set_root(y) == find_sub_set_root(x));
}

void merge_sub_set(int y, int x) {
	int y_root = find_sub_set_root(y);
	int x_root = find_sub_set_root(x);
	parents[max(y_root, x_root)] = min(y_root, x_root);
}

int kruskal() {
	int ret = 0;

	while(!edges.empty()) {
		auto [cost, nd1, nd2] = edges.top();
		edges.pop();

		if(is_same_sub_set(nd1, nd2)) continue;

		merge_sub_set(nd1, nd2);
		ret -= cost;
	}

	return ret;
}

int main() {
	cin >> V >> E;
	for(int i=1; i<=V; ++i) parents[i] = i;
	for(int i=0; i<E; ++i) {
		int from, to, cost; 
		cin >> from >> to >> cost;
		edges.emplace(-cost, from, to);
	}

	cout << kruskal() << '\n';
	return 0;
}
