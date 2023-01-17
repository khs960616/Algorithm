#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/1005
  ACM 크래프트
  그래프, DP
  ---
  
  건물들의 선행 조건을 부모-자식 관계의 그래프로 표현하자. 
  이 때, 자식 건물을 J라 하자.
  J라는 건물을 짓는데 걸리는 최소 시간은 J를 짓는데 걸리는 시간 + J의 부모 건물 중 가장 늦게 지어지는 건물(K)의 시간이 된다. 
  
  이를 관찰해보면 해당 문제를 풀기 위해서는 부분 문제로 
  K를 짓는데 필요한 최소 비용을 구하는 문제로 변하게 된다
  따라서 재귀적으로 그래프의 루트까지 비용을 더해나가면 된다. 
  
  이 때, 밑의 그래프를 예시로 들면,
  
  1 - 2 - 3 - 4
          |   |
          5 - 6 
  
  6을 짓는데 필요한 최소비용을 구하기 위해서는 4와 5의 최소 비용을 구해된다.
  이 때 단순 재귀로 호출하게되면 건물 3을 짓는데 필요한 비용을 중복해서 구하게 되므로, DP로 이를 방지해서 연산수를 줄인다. 
*/
int N, K, W;
int cost[1001];
int dp[1001];
vector<int> parents[1001];

int get_cost(int node) {
	int& ret = dp[node];
	if(ret != -1) return ret;

	ret = cost[node];
	int parent_max_cost = 0;
	for(int parent: parents[node]) {
		parent_max_cost = max(parent_max_cost, get_cost(parent));
	}
	ret += parent_max_cost;
	return ret;
}

int main() {
	int T;
	cin >> T;
	for(int test_case=0; test_case<T; ++test_case) {
		memset(dp, -1, sizeof(dp));
		cin >> N >> K;
		for(int i=1; i<=N; ++i) {
			cin >> cost[i];
			parents[i].clear();
		}

		for(int i=0; i<K; ++i) {
			int parent, child;
			cin >> parent >> child;
			parents[child].push_back(parent);
		}
		cin >> W;
		cout << get_cost(W) << '\n';
	}
	return 0;
}
