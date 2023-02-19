#include <bits/stdc++.h>
#define MAX 32001

using namespace std;

/*
  https://www.acmicpc.net/problem/2252
  줄 세우기
  위상 정렬
  ---
  1. 줄을 세우다 보면, 결국 맨 앞에는 누군가가 서야하므로 사이클이 존재하지 않는다.
  2. 주어진 m에 대해서 A가 B보다 먼저 서야하므로 키 순서대로 출력하면 A -> B 형태로 출력해야한다. 따라서 B의 indegree count를 1개 증가시켜주고 부모노드인 A의 자식으로 추가한다.
  3. indegree count가 0인 노드부터 우선순위큐에 넣으며, 하나씩 출력한다. 
     노드가 큐에서 나올떄는 자신의 자식들의 indegree count값을 1개씩 줄여주며, 만약 indegree count가 0이 되면 pq에 넣어준다.
*/

map<int, vector<int>> child_infos;
int indegree_cnt[MAX];

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	int n, m;	
	cin >> n >> m; 

	for(int i=0; i<m; ++i) {
		int front, back;
		cin >> front >> back;
		indegree_cnt[back]++;
		child_infos[front].push_back(back);
	}

	priority_queue<pair<int, int>> pq;
	for(int i=1; i<=n; ++i) {
		if(indegree_cnt[i] == 0) pq.emplace(-0, i);
	}

	while(!pq.empty()) {
		pair<int, int> p = pq.top();
		pq.pop();

		cout << p.second << ' ';
		for(int child: child_infos[p.second]) {
			if(--indegree_cnt[child] == 0) {
				pq.emplace(0, child);
			}
		}
	}

	return 0;
}
