#include <bits/stdc++.h>
#define INF 20000000
using namespace std;

/*
  https://www.acmicpc.net/problem/2098
  외판원 순회 
  ---
  비트마스킹 + DP를 이용한 TSP알고리즘 
  
*/

int N;
int cost[16][16];
int dp[16][1<<16]; //dp[i][j] -> 현재 위치가 i이고, 방문 상태가 j일 때, 남은 노드들을 최적으로 돌았을떄의 비용

int tsp(int current_pos, int state) {
	int& ret = dp[current_pos][state];
	if(ret != -1) return ret;

	if(state == ((1<<N)-1)) {
		return (cost[current_pos][0] != 0) ? cost[current_pos][0] : INF;
	}

	ret = INF;
	for(int i=0; i<N; ++i) {
		if(state&(1<<i)) continue; // 이미 방문한 노드를 재방문할 필요는 없다.
		if(cost[current_pos][i] == 0) continue;  //현재 방문 불가능한 노드
		ret = min(ret, tsp(i, state|(1<<i))+cost[current_pos][i]);
	}
	return ret;
}

int main() {
	cin >> N;
	for(int i=0; i<N; ++i) {
		for(int j=0; j<N; ++j) {
			cin >> cost[i][j];
		}
	}

	memset(dp, -1, sizeof(dp));
	cout << tsp(0, 1) << '\n';
	return 0;
}
