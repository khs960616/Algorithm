#include <bits/stdc++.h>
#define INF 800000   
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12978
  배달
  ---
  다익스트라
*/
vector<int> dijkstra(int n, vector<vector<pair<int, int> > >& roads) {
    vector<int> ret(n+1, INF);
    ret[1] = 0;
    
    priority_queue<pair<int, int> > pq;
    pq.push({-0, 1});
    
    while(!pq.empty()) {
        int distance = -pq.top().first;
        int city = pq.top().second;
        pq.pop();
        if(ret[city] < distance) continue;
        
        for(pair<int, int> road: roads[city]) {
            int newCost = distance + road.first;
            if(ret[road.second] > newCost) {
                ret[road.second] = newCost;
                pq.push({-newCost, road.second});
            }
        }
    }
    
    return ret;
}

int solution(int N, vector<vector<int> > road, int K) {
    // make conntected info
    vector<vector<pair<int, int> > > roads(N+1);
    for(vector<int> v: road) {
        roads[v[0]].push_back({v[2], v[1]});
        roads[v[1]].push_back({v[2], v[0]});
    }
    
    // get distance with dijstra
    vector<int> minDistances = dijkstra(N, roads);
    
    // calc answer
    int answer = 0;
    for(int i=1; i<=N; ++i) {
        if(minDistances[i] <= K) answer+=1;
    }
    return answer;
}
