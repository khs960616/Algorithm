#include <bits/stdc++.h>

using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/42861
  섬 연결하기 
  ---
  나이브한 풀이 
  1. 선택된 섬들을 부분집합으로 관리한다.
  2. 현재 부분집합과 연결되지 않은 섬중, 연결이 가능하며, cost가 가장 적은 bridge를 순차적으로 건설한다.
  
  erase로 인해, n^4 가량의 복잡도를 요구함  
  
  (erase시 배열 재배치 : 시간복잡도 n,  costs의 길이(((n-1) * n) / 2),  set이 n과 동일한 경우까지 반복하므로 n )
  대략 10^8정도..
  
  ---
  크루스칼 알고리즘 (그리디의 일종)
  https://chanhuiseok.github.io/posts/algo-33/
*/
bool cmp(vector<int> v1, vector<int> v2) {
    return v1[2] < v2[2];
}

set<int> selected_islands;

void select_bridges(vector<vector<int>>& costs, int idx) {
    selected_islands.insert(costs[idx][0]);
    selected_islands.insert(costs[idx][1]);
    costs.erase(costs.begin()+idx);
}

int get_include_island_cnt(vector<int> cost) {
    int ret = 0;
    if(selected_islands.find(cost[0]) != selected_islands.end()) ++ret;
    if(selected_islands.find(cost[1]) != selected_islands.end()) ++ret;
    
    return ret;
}

int solution(int n, vector<vector<int>> costs) {
    sort(costs.begin(), costs.end(), cmp);
    
    int answer = costs[0][2];
    select_bridges(costs, 0);
    
    while(selected_islands.size() < n) {
        int cost_size = costs.size();
        int idx = 0;
        for(; idx<cost_size; ++idx) {
            int check_cnt = get_include_island_cnt(costs[idx]);
            if(check_cnt == 1) break;
        }
        
        answer += costs[idx][2];
        select_bridges(costs, idx);
    }
    return answer;
}

/*
  크루스칼 알고리즘 
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int d[101];

int getParent(int node){
    if(node == d[node]){
        return node;
    }
    else return d[node] = getParent(d[node]);
}

bool compare(vector<int> a, vector<int> b){
    return a[2] < b[2];
}

int solution(int n, vector<vector<int>> costs) {

    int answer = 0;
    for(int i =0; i<n; i++){
        d[i] = i;
    }
    sort(costs.begin(), costs.end(), compare);
    for(int i=0; i<costs.size(); i++){
        int start = getParent(costs[i][0]);
        int end = getParent(costs[i][1]);
        int cost = costs[i][2];

        if(start != end){
            d[end] = start;

            answer += cost;
        }
    }


    return answer;
}
*/
