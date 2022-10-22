#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/76503
  모두 0으로 만들기
  트리
  ---
  1. 특정 노드를 루트로 지정한다.
  2. 해당 노드를 기준으로 자기 자신의 sub_tree의 value들을 재귀적으로 더한다.
     (이 때 sub_tree값들의 절대값이 실제로 두 노드간의 값 교환횟수가 된다.)
  3. 2번의 과정으로 루트노드로 지정한 노드값이 0이 될 수 있다면, 교환횟수를 return한다. 
  
*/
long long answer = 0;
int a_size = 0;
vector<bool> is_visit;
unordered_map<int, vector<int> > edges_map;

void pre_process(vector<int> a, vector<vector<int>> edges) {
    a_size = a.size();
    is_visit = vector<bool>(a_size, false);
    for(vector<int> edge: edges) {
        edges_map[edge[0]].push_back(edge[1]);
        edges_map[edge[1]].push_back(edge[0]);
    }   
}

long long solve(vector<int>& a, int current_idx) {
    long long ret = a[current_idx];
    is_visit[current_idx] = true;

    for(int edge: edges_map[current_idx]) {
        if(is_visit[edge]) continue;
        long long sub_tree_value = solve(a, edge);
        ret += sub_tree_value;
        answer+=abs(sub_tree_value);
    }
    return ret;
}

long long solution(vector<int> a, vector<vector<int>> edges) {
    pre_process(a, edges);
    if(solve(a, 0) != 0) answer = -1;
    return answer;
}
