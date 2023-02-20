#include <bits/stdc++.h>

using namespace std;

/*
  https://www.acmicpc.net/problem/2623
  음악 프로그램
  ---
  위상정렬 
*/
int indegree[1001];
map<int, vector<int> > childs_info;

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	// 사이클이 생기는 순간 0을 출력해야한다. 
	for(int i=0; i<m; ++i) {
		int manage_cnt, prev_singer;
		cin >> manage_cnt >> prev_singer;

		for(int j=1; j<manage_cnt; ++j) {
			int singer;
			cin >> singer;
			indegree[singer]++;
			childs_info[prev_singer].push_back(singer);
			prev_singer = singer;
		}
	}

	vector<int> answer;
	priority_queue<int> pq;
	for(int i=1; i<=n; ++i) {
		if(!indegree[i]) pq.push(i);
	}

	while(!pq.empty()) {
		int node = pq.top();
		pq.pop();

		answer.push_back(node);
		for(int& child: childs_info[node]) {
			if(--indegree[child] == 0) pq.push(child);
		}
	}

	if(answer.size() != n) {
		cout << 0;
	} else {
		for(int i: answer) {
			cout << i << '\n';
		}
	}
	return 0;
}
