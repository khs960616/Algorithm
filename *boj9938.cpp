#include <bits/stdc++.h>
#define MAX_SIZE 300001
using namespace std;

/*
  https://www.acmicpc.net/problem/9938
  방 청소 
  ---
  union - find 
  다시 풀어볼 것 
  문제에서 주어진 "술병"은 서랍간의 연결 관계이고, 서랍은 노드로 생각하고 union find 알고리즘을 적용하는 문제임.
  ---
  
  일반 union-find 를 사용한 방법)
  
  주어진 술병의 이동 조건을 일일이 시뮬레이션하지 않고, 술병이 들어갈 수 있는 서랍들을 subset 형태로 연결하면서 방문 여부를 체크한다.
  이 때 각 subset의 root 노드가 될 수 있는 우선순위는 "아직 방문하지 않은 노드"를 최우선적으로 오도록 한다.
  
  1. 만일 술병을 A서랍에 넣을 수 있는 경우, A서랍과 B서랍을 union 하고 A서랍과 B서랍을 합치고, A서랍의 방문 여부를 true로 변경한다. 
     (같은 서브셋으로 둔다는 의미 : 만일 해당 술병을 옮겨야 하는 상황이오면, A서랍의 술은 B서랍이 비어있는 경우 이동이 가능하다는 의미이다.) 
     (즉 해당 서브셋에 속하는 노드들은, 루트 노드의 방문여부가 false이면, 같은 subset간의 술병의 이동을 통해, 특정 노드의 칸을 비울 수 있음을 의미한다.)
     
  2. A서랍이 가득찬 경우 B서랍, A서랍이 속한 subset의 루트노드, B서랍이 속한 subset의 루트노드에 대하여 1번의 과정을 반복한다.
  
  3. 만일 특정 subset의 루트노드의 방문상태가 true이면, 해당 subset에서는 술병간의 이동이 더 이상 불가능한 상태이므로 SMECE를 출력한다.
 
 --- 
  weighted union find 풀이 (https://mapocodingpark.blogspot.com/2020/05/9938.html)
  1. 각 subset에 넣을 수 있는 최대 수의 술병 (결국 해당 subset에 속하는 노드의 갯수)를 union 과정에서 root 노드에 표기한다.
  2. 1번의 과정 이후, 생성된 subset의 root에 몇개의 술병이 들어있는지 체크 후, 만일 아직 더 넣을 수 있다면 해당 값을 1 증가시키고 1의 과정을 반복한다. 
  
  개인적으로는 해당 풀이법이 좀 더 이해하기 쉬웠다. 
*/

int parents[MAX_SIZE];
bool is_visited[MAX_SIZE];

int find_parents(int node) {
	if(node == parents[node]) return node;
	return parents[node] = find_parents(parents[node]);
}

void merge(int node1, int node2) {
	int p1 = find_parents(node1);
	int p2 = find_parents(node2);
	if(p1 == p2) return;
	parents[p1] = p2;
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	int N, L;
	cin >> N >> L;
	for(int i=1; i<=L; ++i) {
		parents[i] = i;
	}
	for(int i=0; i<N; ++i) {
		int drawer1, drawer2;
		cin >> drawer1 >> drawer2;

		if(!is_visited[drawer1]) {
			is_visited[drawer1] = true;
			merge(drawer1, drawer2);
		} else if(!is_visited[drawer2]) {
			is_visited[drawer2] = true;
			merge(drawer2, drawer1);
		} else if(!is_visited[find_parents(drawer1)]) {
			is_visited[find_parents(drawer1)] = true;
			merge(drawer1, drawer2);
		} else if(!is_visited[find_parents(drawer2)]) {
			is_visited[find_parents(drawer2)] = true;
			merge(drawer2, drawer1);
		} else {
			cout << "SMECE\n";
			continue;
		}
		cout << "LADICA\n";
	}
	return 0;
}



/*

맨 처음 시도한 코드

#include <bits/stdc++.h>
#define MAX_SIZE 300001
using namespace std;

int alcohols[MAX_SIZE][2];
bool is_visited[MAX_SIZE];
int drawers[MAX_SIZE];

bool is_can_move(int d_idx) {
	int a_idx = drawers[d_idx];
	is_visited[d_idx] = true;
	bool ret = true;
	if(drawers[alcohols[a_idx][0]] != 0 && drawers[alcohols[a_idx][1]] != 0) {
		if(is_visited[drawers[alcohols[a_idx][0]]] && is_visited[drawers[alcohols[a_idx][1]]]) {
			is_visited[d_idx] = false;
			return false;
		}
		int next_d_idx = alcohols[a_idx][0] != d_idx ?  alcohols[a_idx][0] : alcohols[a_idx][1];
		ret = is_can_move(next_d_idx);
	} 

	if(ret) {
		int mov_d_idx = drawers[alcohols[a_idx][0]] == 0 ? alcohols[a_idx][0] : alcohols[a_idx][1];
		drawers[mov_d_idx] = a_idx;
		drawers[d_idx] = 0;
	}
	is_visited[d_idx] = false;
	return ret;
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	int N, L;
	cin >> N >> L;

	for(int i=1; i<=N; ++i) {
		cin >> alcohols[i][0] >> alcohols[i][1];

		if(drawers[alcohols[i][0]] == 0) drawers[alcohols[i][0]] = i;
		else if(drawers[alcohols[i][1]] == 0) drawers[alcohols[i][1]] = i;
		else if(is_can_move(alcohols[i][0])) {
			drawers[alcohols[i][0]] = i;
		} else if(is_can_move(alcohols[i][1])) {
			drawers[alcohols[i][1]] = i;
		} else {
			cout << "SMECE\n";
			continue;
		}
		cout << "LADICA\n";
	}
	return 0;
}

*/
