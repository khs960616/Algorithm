#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;
/*
https://www.acmicpc.net/problem/1916
최소비용 구하기
---
다익스트라 
*/
vector<int> dijstra(map<int, vector<pair<int, int>>> busInfos, 
                    int cityCnt, 
                    int startNode) {
    vector<int> distances(cityCnt+1, INF);
    distances[startNode] = 0;

    priority_queue<pair<int, int>> pq;
    pq.push({0, startNode});

    while(!pq.empty()) {
        int distance = -pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if(distances[node] < distance) continue;
        for(pair<int, int> bus: busInfos[node]) {
            if(distances[bus.second] > distance+bus.first) {
                distances[bus.second] = distance+bus.first;
                pq.push({-distances[bus.second], bus.second});
            }
        }
    }
    
    return distances;
}

int main() {
    int cityCnt, busCnt;
    cin >> cityCnt >> busCnt;

    map<int, vector<pair<int, int>>> busInfos;
    for(int i=0; i<busCnt; ++i) {
        int from, to, distance;
        cin >> from >> to >> distance;
        busInfos[from].push_back({distance, to});
    }

    int startNode, endNode;
    cin >> startNode >> endNode; 
    vector<int> answer = dijstra(busInfos, cityCnt, startNode);
    cout << answer[endNode];
    return 0;   
}
