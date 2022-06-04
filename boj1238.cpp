#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

map<int, vector<pair<int, int>>> mp;

/*
  https://www.acmicpc.net/problem/1238
  파티
  다익스트라
*/

//매개변수로 넘어온 vertax에서 i번째까지가는 최단 경로를 저장하는 벡터 v  (v[i] = vertax에서 i번째까지의 최단경로)
void dijkstra(vector<int>& v, int vertax) {
    priority_queue<pair<int, int>> pq;
    pq.push({0, vertax});
    v[vertax] = 0;    // 자기 자신의 마을에서 파티가 열리는 경우, 해당 학생은 이동할 필요가 없으므로. 
    
    while (!pq.empty()) {
        int distance = -pq.top().first;   // c++ pq는 compare함수로 매개변수를 넣어주지 않으면 default로 max heap이므로 min heap으로 사용하기 위함 
        int nextVertax = pq.top().second;  
        pq.pop();

        if(v[nextVertax] < distance) continue;  // 이전 단계에서 계산되었던 최단 경로가 현재의 최단경로보다 크다면, 이미 해당 정점을 방문한 것이므로 볼 필요가 없다. 

        for(pair<int, int> p: mp[nextVertax]) {
            if(v[p.second] > distance + p.first) { 
                v[p.second] = distance + p.first;
                pq.push({-v[p.second], p.second});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, x;
    cin >> n >> m >> x;

    vector<int> party(n+1, INF);
    for(int i=0; i<m; ++i) {
        int key, vertax, distance;
        cin >> key >> vertax >> distance;
        mp[key].push_back({distance, vertax});
    }

    dijkstra(party, x);

    int answer = -1;
    vector<int> info(n+1, INF);
    for(int i=1; i<n+1; ++i) {
        int distanceItoX = 0;
        if(i != x) {  
            dijkstra(info, i);
            distanceItoX = info[x];
            for(int& num : info) num = INF;
        }

        answer = max(answer, distanceItoX+party[i]);
    }

    cout << answer;
    return 0;   
}
