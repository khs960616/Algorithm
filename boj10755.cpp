#include <bits/stdc++.h>
#define MAX_SIZE 100001
using namespace std; 

/*
  https://www.acmicpc.net/problem/10775
  공항
  ----
  union-find 
  
  gi가 주어지면,
  해당 gi번째 노드의 parent노드를 구한다.
  
  만일 parent 노드가 방문할 수 없는 형태라면, 더 이상 비행기가 도킹할 수 없는 상태이므로 더 이상 answer값을 증가시키지 않는다.
  만일 parent 노드가 방문할 수 없는 상태라면 해당 parent노드에 비행기를 도킹시킨다.
   >> is_visited[parent]를 true로 설정하고,   par[ 해당노드] = 해당노드-1번쨰 노드의 부모노드를 대입한다. 
   
   >> 자기 자신보다 크기가 1작은 노드의 부모 노드를 대입하는 이유는, 현재 넣는 비행기는 1~gi까지의 게이트 어디에든 들어갈 수 있는 형태이고,
   차후 다른 비행기가 현재 위치에 도킹하려할때, 이전에 해당 게이트에 넣은 비행기를 1~gi까지 게이트중 넣을 수 있는 가장 큰 게이트로 옮기면 (실제 
   비행기는 한번 도킹하면 이동이 불가능하지만, union-find를 사용해서 이미 도킹된 비행기를 옮긴다는 의미는 애초에 시작부터 최적해 위치에 도킹하는 것으로 정답을 수정하는 과정이라 생각하면
   문제가 단순해진다.)
   비행기를 추가적으로 도킹할수 있기 때문이다.
*/
int par[MAX_SIZE];
bool is_visited[MAX_SIZE];

int find_par(int gate) {
	if(par[gate] == gate) return gate;
	return par[gate] = find_par(par[gate]);
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	int g = 0, p = 0, answer = 0;
	bool flag = true;
	cin >> g >> p;
	for(int i=1; i<=g; ++i) par[i] = i;

	for(int i=0; i<p; ++i) {
		int node;
		cin >> node;

		if(flag) {
			int root = find_par(node);
			if(is_visited[root]) {
				flag = false;
				continue;
			}

			is_visited[root] = true;
			par[root] = find_par(max(1, root-1));
			answer++;
		}
	}

	cout << answer;
	return 0;
}
