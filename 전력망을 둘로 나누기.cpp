#include <bits/stdc++.h>

using namespace std;

bool isVisit[101];

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/86971?language=cpp
  전력망을 둘로 나누기
  트리
  ---
  1. 트리의 노드를 BFS로 순회하며, 자기 자신을 포함한 서브트리의 크기를 구한다.
  2. 자기 자신을 포함한 서브트리의 연결을 끊었을 때, 나누어진 두 트리의 크기의 차이가 가장 작은 값을 반환한다. 
*/

int get_sub_tree_size(map<int, vector<int> >& mp,
                  int current_node, int n,
                  int& answer) {
    int ret = 1;
    for(int node : mp[current_node]) {
        if(isVisit[node]) continue;   // 이미 방문한 노드를 재 방문하게 되면, 루트를 기준으로 하는, 서브트리의 사이즈에 대한 일관성이 깨지므로 1번만 방문 해야 한다.
        isVisit[node] = true;
        ret += get_sub_tree_size(mp, node, n, answer);  // 자기 자신의 서브트리의 크기는, 자식노드들의 서브트리의 총합 + 1이 된다.
    }
    
    answer = min(answer, abs(n-(ret<<1)));   // (n-ret,  ret)  두 사이즈로 쪼개진 서브트리의 크기가 가장 작은 값을 답으로 선택한다. 
    return ret;
}

int solution(int n, vector<vector<int>> wires) {
    int answer = INT_MAX;
    map<int, vector<int> > mp;
    
    // 임의의 노드를 루트 노드로 지정한다.
    int root = wires[0][0];
    isVisit[root] = true;
    
    // 각 edges 정보를 재구성한다.
    for(vector<int> wire : wires) {
        mp[wire[0]].push_back(wire[1]);
        mp[wire[1]].push_back(wire[0]);
    }
    
    get_sub_tree_size(mp, root, n, answer);
    return answer;
}
