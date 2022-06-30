#include <bits/stdc++.h>
#define INF 100000
using namespace std;

/*
    https://programmers.co.kr/learn/courses/30/lessons/49189
    가장 먼 노드
    그래프, 다익스트라
    ------------------------
    노드 1 ~ n까지 번호가 정해짐
    1번 노드에서 가장 멀리 떨어진 노드의 개수를 구하려함
    가장 멀리 떨어진 노드 : 최단 경로로 이동했을때, 이동에 필요한 간선의 개수가 가장 많은 노드
    
    (노드간의 거리는 1로 설정하고 다익스트라를 활용하면 된다)
*/

int dijkstra(int n, map<int, vector<int>>& mp) {
    priority_queue<pair<int, int>> pq;
    vector<int> answer(n+1, INF);
    answer[0] = -1;
    pq.push({0, 1});
    
    while(!pq.empty()) {
        int distance = -pq.top().first;
        int node = pq.top().second;
        pq.pop();
        
        if(answer[node] != INF) continue;
        answer[node] = distance;
        
        for(int num : mp[node]) {
            pq.push({-(distance+1), num});
        }
    }
    sort(answer.begin(), answer.end());
    int ret = 1;
    int maxElement = answer[n];

    for(int i=n-1; i>0; --i) {
        if(answer[i] != maxElement) break;
        ++ret;
    }
    
    return ret;
} 

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    map<int, vector<int>> mp;
    for(vector<int> v : edge) {
        mp[v[0]].push_back(v[1]);
        mp[v[1]].push_back(v[0]);
    }
    
    return dijkstra(n, mp);
}
