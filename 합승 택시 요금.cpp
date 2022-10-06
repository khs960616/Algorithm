#include <bits/stdc++.h>
#define INF 50000000
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/72413
  2021 KAKAO BLIND RECRUITMENT
  합승 택시 요금 
  ---
  다익스트라 + 응용 
  
  S에서 출발하여 A, B 모두를 들르는 최소비용
  
  1. S, A, B를 각각 출발지로 하여 다익스트라 알고리즘을 이용해 해당 세 정점에서 다른 정점으로 가는 최소 비용을 구한다.
  2. 세 정점이 동일한 정점에 도달하는 비용의 합중 최솟값이 구하고자하는 답이다. 
  ---
  처음 실패
  S에서 A와 B로 각각 가능 경우,
  S에서 A를 먼저 들러 A->B로 가는 경우
  S에서 B를 먼저 들러 B->A로 가는 경우    
  로 처음에는 3가지 경우만 고려했는데 테스트 케이스 1번에서 실패함
  위 3가지 케이스만 고려하는 경우, S에서 A,B로 최소비용으로 가는 path가 중복되는 경우,
  즉 S-> (특정정점) 까지만 합승을하고 이후 A,B가 각각 따로가는 경우는 고려하지 못함.
  
*/
unordered_map<int, vector<pair<int, int> > > fares_map;

void init_fares_map(vector<vector<int>> fares) {
    for(vector<int> fare: fares) {
        fares_map[fare[0]].emplace_back(fare[1], fare[2]);
        fares_map[fare[1]].emplace_back(fare[0], fare[2]);
    }
}

vector<int> dijkstra(int n, int target) {
    vector<int> ret(n+1, INF);
    ret[target] = 0;
    
    //현재 cost, 현재 정점 
    priority_queue<pair<int, int> > pq;
    pq.emplace(-0, target);
    
    //이미 방문한 vertax는 다시 방문하지 않는다. 
    while(!pq.empty()) {
        int cost = -pq.top().first;
        int vertax = pq.top().second;
        pq.pop();
        
        if(ret[vertax] < cost) continue;
        
        for(pair<int, int> fare: fares_map[vertax]) {
            int next_vertax = fare.first;
            int next_cost = fare.second + cost;

            if(next_cost < ret[next_vertax]) {
                ret[next_vertax] = next_cost;
                pq.emplace(-next_cost, next_vertax);
            }
        }
    }
    return ret;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    init_fares_map(fares);

    vector<int> s_min = dijkstra(n, s);
    vector<int> a_min = dijkstra(n, a);
    vector<int> b_min = dijkstra(n, b);
    
    int answer = INT_MAX;
    for(int i=1; i<n+1; ++i) {
        answer = min(answer, s_min[i]+a_min[i]+b_min[i]);
    }
    return answer;
}
