#include <bits/stdc++.h>
#define INF 2000
using namespace std;

int answer = 0;
int n, m, r;
vector<vector<int> > edges;
vector<int> values;

/*
https://www.acmicpc.net/problem/14938
서강그라운드
플루이드 와샬
---
1. input size n (1 ≤ n ≤ 100)으로 매우 작음
2. 특정 정점을 선택했을때, 획득 가능한 아이템의 최대 갯수는 
   각 정점에서 모든 정점까지의 최단 거리를 구한 후, 주어진 범위 m이하인 모든 정점에 존재하는 아이템의 갯수의 합이다.
3. (1), (2)의 근거로 모든 정점에서 모든정점까지인 최단 경로를 구하는 플루이드 와샬 알고리즘 사용 (100^3)
*/
void init_floid() {
    for(int k=1; k<n+1; ++k) {
        for(int i=1; i<n+1; ++i) {
            for(int j=1; j<n+1; ++j) {
                if(i == j) {
                    edges[i][j] = 0;
                    continue;
                }
                edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j]);
            }
        }
    }
}

int get_currnet_cost(int idx) {
	int ret = 0;
	for(int i=1; i<n+1; ++i) {
		if(edges[i][idx] > m) continue;
		ret += values[i];
	}
	return ret;
}

int main() {
	cin >> n >> m >> r;
	edges = vector<vector<int> >(n+1, vector<int>(n+1, INF));
	values = vector<int>(n+1, 0);

	for(int i=1; i<n+1; ++i) cin >> values[i];
	for(int i=0; i<r; ++i) {
		int from, to, cost;
		cin >> from >> to >> cost;
		edges[from][to] = edges[to][from] = cost;
	}
	init_floid();
	
	for(int i=1; i<n+1; ++i) answer = max(get_currnet_cost(i), answer);
	cout << answer << '\n';
	return 0;
}
