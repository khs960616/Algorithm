#include <bits/stdc++.h>
#define INF 300000000

using namespace std;

/*
  https://www.acmicpc.net/problem/1504
  특정한 최단 경로
  1에서 출발하여 정점 v1, v2를 지나 N으로 가는 최단 경로
  (경로 중복선택 가능)
  --- 
  > 출발점, 종료점은 항상 1, N으로 고정되어있음 
  
  1 -> ???? -> v1 -> ????? -> v2 -> ?????  ->  N
  1 -> ???? -> v2 -> ????? -> v1 -> ?????  ->  N
  1 -> ???? -> N -> ????-> v1 --> ??? --> v2 --> N 등등
  
  경로를 중복해서 최단거리가 되게끔 선택하면 되기 떄문에 수많은 경로가 나올 것이므로 케이스를 전부 쪼개서 일일히 고려하기는 어렵다. 
  
  그러나 결국 도착점은 항상 N으로 고정되어있기 때문에 다음과 생각하면 편하다.
  다음 세 가지 선분이 존재한다고 가정한다.
  1. 1과 (v1 또는 v2)를 연결하는 선분
  2. v1과 v2를 연결하는 선분
  3. (v2 또는 v1)을 연결하는 선분
  
  결국 각 선분의 최단길이들을 구해 더하면 실제 구하고자 하는 정답이 된다.
  (각 경우마다 다익스트라 돌리면 됨) 
*/
int n;
map<int, vector<pair<int, int>>> mp;
map<int, vector<long long>> dijstraMap;

void dijkstra(int startVertax) {
    vector<long long> v (n+1, INF);
    v[startVertax] = 0;
    priority_queue<pair<long long, int>> pq;
    pq.push({0, startVertax});

    while(!pq.empty()) {
        long long distance = -pq.top().first;
        int vertax = pq.top().second;
        pq.pop();

        if(v[vertax] < distance) continue;

        for(pair<int, int> p: mp[vertax]) {
            if(v[p.first] > distance + p.second) {
                v[p.first] = distance + p.second;
                pq.push({-v[p.first], p.first});
            }
        }
    }

    for(int i=0; i<n+1; ++i) {
        dijstraMap[startVertax].push_back(v[i]);
    }
}

int main() {
    int e, v1, v2;   //정점 갯수 N, 간선 개수 E
    cin >> n >> e;

    for(int i=0; i<e; ++i) {
        int vertax1, vertax2, distance;
        cin >> vertax1 >> vertax2 >> distance;
        mp[vertax1].push_back({vertax2, distance});
        mp[vertax2].push_back({vertax1, distance});
    }
    cin >> v1 >> v2;

    long long answer = INF;
    dijkstra(1);
    dijkstra(v1);
    dijkstra(v2);

    long long middle = dijstraMap[v1][v2];

    if(dijstraMap[1][v1] != INF && middle != INF && dijstraMap[v2][n] != INF) {
        answer = min(answer, dijstraMap[1][v1]+middle+dijstraMap[v2][n]);
    }

    if(dijstraMap[1][v2] != INF && middle != INF && dijstraMap[v1][n] != INF) {
        answer = min(answer, dijstraMap[1][v2]+middle+dijstraMap[v1][n]);
    }

    answer = (answer == INF) ? -1 : answer;
    cout << answer;
    return 0;
}
