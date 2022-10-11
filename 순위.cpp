#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/49191
  순위
  ---
  bfs
  
  1. 각 권투선수를 노드로, 경기의 결과를 (승리->패배) 형태로 단방향 edge로 표현한다.)
  2. 1번 선수부터 n번 선수까지 bfs를 통해 이동 가능한 노드들을 순회하여, 승패 정보를 기록한다.
     ex) i번째 노드로 부터 시작해서  j, m, k 번째 순서의 노드를 방문하면,
     i번째 선수는 (j, m, k)번 선수를 이긴 것이 되며,  (j, m, k)선수들은 i번째 선수에게 진 것이므로, 해당 정보를 저장한다.
   
  3. 모든 노드에 대해서, 자기 자신을 제외한 (n-1)개의 노드와 연결되어있는 노드는 순위가 확실한 노드이므로 해당 갯수를 세서 리턴한다.
  
*/

unordered_map<int, vector<int> > win_edges;
unordered_map<int, set<int> > connected_infos;

void init_edges_map(vector<vector<int>> results) {
    for(vector<int> result: results) {
        win_edges[result[0]].push_back(result[1]);
    }
}

void bfs(int n, int start_node) {
    vector<bool> is_visit(n, false);

    queue<int> q;
    q.push(start_node);
    is_visit[start_node] = true;
    
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        
        for(int next_node: win_edges[node]) {
            if(is_visit[next_node]) continue;
            connected_infos[next_node].insert(start_node);
            connected_infos[start_node].insert(next_node);
            q.push(next_node);
            is_visit[next_node] = true;
        }
    }
}

void make_connected_info(int n) {
    for(int i=1; i<=n; ++i) bfs(n, i);
}

int solution(int n, vector<vector<int>> results) {
    init_edges_map(results);
    make_connected_info(n);
    
    int answer = 0;
    for(int i=1; i<=n; ++i) {
        if(connected_infos[i].size() == n-1) answer++;
    }
    return answer;
}
