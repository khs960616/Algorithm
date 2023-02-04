#include <bits/stdc++.h>
#define MAX_SIZE 32001
using namespace std;

/*
  https://www.acmicpc.net/problem/1766
  문제집
  ---
  위상 정렬
  
*/

int n, m;
int in_degree_cnt[MAX_SIZE];
vector<vector<int>> child_infos;

int main() {
	cin >> n >> m;
	child_infos = vector<vector<int>>(n+1);

	for(int i=0; i<m; ++i) {
		int parent, child;
		cin >> parent >> child;
		child_infos[parent].push_back(child);
		in_degree_cnt[child]++;
	}

	priority_queue<int> pq;
	for(int i=1; i<=n; ++i) {
		if(!in_degree_cnt[i]) pq.push(-i);
	}

	while(!pq.empty()) {
		int currnet_node = -pq.top();
		pq.pop();

		cout << currnet_node << ' ';

		for(int child: child_infos[currnet_node]) {
			in_degree_cnt[child]--;
			if(in_degree_cnt[child] == 0) {
				pq.push(-child);
			}
		}
	}
	return 0;
}
