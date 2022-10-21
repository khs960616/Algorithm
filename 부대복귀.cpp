#include <bits/stdc++.h>
#define INF 200001
using namespace std;

/*
  https://github.com/khs960616/Algorithm/new/master
  부대복귀
  ---
  다익스트라
  - 주어진 destination에서 다른 모든 source로의 최단 경로를 구하면됨.
  
  다익스트라)
  테스트 11 〉	통과 (432.40ms, 137MB)   // 다익스트라의 경우 pq로 구현했으므로  O(|E||log|V|)
  
  단순 bfs)
  테스트 11 〉	통과 (8397.18ms, 137MB)  
  // 최악의 경우 모든 정점에서 모든 edge를 검사할 것이므로 O(E*V) -> 테스트 케이스에서 이런 경우가 없어 통과되긴 했으나, bfs를 요구하는 문제는 아닌듯. 
*/
vector<int> answer;
unordered_map<int, vector<int> > mp;

void init_map(vector<vector<int>> roads) {
    for(vector<int> road: roads) {
        int from = road[0];
        int to = road[1];
        mp[from].push_back(to);
        mp[to].push_back(from);
    }
}

vector<int> dijkstra(int n, int destination) {
    vector<int> ret(n+1, INF);
    ret[destination] = 0;
    
    priority_queue<pair<int, int> > pq;
    pq.emplace(-0, destination);
    while(!pq.empty()) {
        int cost = -pq.top().first;
        int src = pq.top().second;
        pq.pop();

        if(ret[src] < cost) continue;
        for(int road: mp[src]) {
            if(ret[road] <= cost+1) continue;
            ret[road] = cost+1;
            pq.emplace(-(cost+1), road);
        }
    }
    return ret;
}

vector<int> solution(int n, 
                     vector<vector<int>> roads, 
                     vector<int> sources, 
                     int destination) {
    init_map(roads);
    vector<int> min_distances = dijkstra(n, destination);
    for(int src: sources) {
        int cost = min_distances[src] == INF ? -1 : min_distances[src];
        answer.push_back(cost);
    }
    return answer;
}




/*
bfs 풀이

#include <bits/stdc++.h>
using namespace std;

vector<int> answer;
unordered_map<int, vector<int> > mp;

void init_map(vector<vector<int>> roads) {
    for(vector<int> road: roads) {
        int from = road[0];
        int to = road[1];
        mp[from].push_back(to);
        mp[to].push_back(from);
    }
}

int bfs(int n, int source, int destination) {
    vector<bool> is_visit(n+1, false);
    queue<pair<int, int> > q;
    q.emplace(0, source);
    is_visit[source] = true;
    
    while(!q.empty()) {
        int cost = q.front().first;
        int src = q.front().second;
        q.pop();
        
        if(src == destination) return cost;
        
        for(int road: mp[src]) {
            if(is_visit[road]) continue;
            is_visit[road] = true;
            q.emplace(cost+1, road);
        }
    }

    return -1;
}

vector<int> solution(int n, 
                     vector<vector<int>> roads, 
                     vector<int> sources, 
                     int destination) {
    init_map(roads);
    for(int src: sources) {
        answer.push_back(bfs(n, src, destination));
    }
    return answer;
}

*/
