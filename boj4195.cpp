#include <bits/stdc++.h>

using namespace std;

int parents[200001];
int inc_idx;
map<string, int> idx_map;

/*
  https://www.acmicpc.net/problem/4195
  친구 네트워크 
  ---
  weighted union find
  
  solve)
     친구의 이름 두 개가 들어오면
     
     1. 두 친구가 같은 네트워크에 속하는지 여부를 우선 판별해야한다.
        -> 같은 경우 네트워크의 크기를 반환한다.
        -> 다른 경우 두 친구가 속한 네트워크를 합친후, 네트워크의 크기를 반환한다.
        -> weighted union find 알고리즘을 선택
        
           subset의 루트는 음수 형태로, 해당 그래프의 크기를 저장하도록 한다.
           따라서 parent를 찾을 때, parent값이 음수인 노드는 각 그래프의 루트 노드가 되도록 find 함수를 작성한다.
           
        
     2. 주어진 데이터는 string 이다. union find를 배열을 활용해서 하기 위해서는 주어진 데이터를 정수 형태로 변환하는 과정이 필요하다.
        만약 주어진 string이 이전에 등장하지 않았으면, 해당 string에게 node번호를 부여하는 것을 map을 활용해서 구현하였다. 
        (db에서 auto increment 하듯, 인덱스값을 증가시켜주는 변수를 하나 두면 비교적 편하게 구현이 가능하다.)
*/
string insert_map() {
	string s;
	cin >> s;
	if(idx_map.find(s) == idx_map.end()) {
		parents[inc_idx] = -1;
		idx_map[s] = inc_idx++;
	}
	return s;
}

int find_parent(int node) {
	if(parents[node] < 0) return node;
	return parents[node] = find_parent(parents[node]);
}

int merge_sub_set(int node1, int node2) {
	int p1 = find_parent(node1);
	int p2 = find_parent(node2);

	if(p1 == p2) return parents[p1];

	int parent = parents[p1] > parents[p2] ? p2 : p1;
	int child = parents[p1] <= parents[p2] ? p2 : p1;

	parents[parent] += parents[child];
	parents[child] = parent;
	return parents[parent];
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	for(int test_case = 0; test_case < T; test_case++) {
		inc_idx = 0;
		idx_map.clear();

		int K;
		cin >> K;
		for(int i=0; i<K; ++i) {
			string s1 = insert_map(), s2 = insert_map();
			cout << -1 * merge_sub_set(idx_map[s1], idx_map[s2]) << '\n';
		}
	}
	return 0;
}
