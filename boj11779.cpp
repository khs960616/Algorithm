#include <bits/stdc++.h>
#define INF 300000000
using namespace std;

/*
https://www.acmicpc.net/problem/11779
최소비용 구하기 2
-----------------
다익스트라 알고리즘
*/
pair<int, vector<int>> dijkstra(int n, int start, int end, map<int, vector<pair<int, int>>>& mp) {
    vector<int> ret(n+1, INF);
    vector<vector<int>> pInfo(n+1);

    priority_queue<tuple<int, int, vector<int>>> pq;
    ret[start] = 0;
    pq.push({-0, start, {start}});

    while (!pq.empty()) {
        int cost = -get<0>(pq.top());
        int city = get<1>(pq.top());
        vector<int> paths = get<2>(pq.top());
        pq.pop();

        if(ret[city] < cost) continue;
        for(pair<int, int> p : mp[city]) {
            int newCost = cost + p.first;

            if(ret[p.second] > newCost) {
                paths.push_back(p.second);
                ret[p.second] = newCost;
                pInfo[p.second] = paths;
                pq.push({-newCost, p.second, paths});
                paths.pop_back();
            }
        }
    }
    
    return {ret[end], pInfo[end]};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n, m, start, end;
    cin >> n >> m;

    map<int, vector<pair<int, int>>> mp;
    for(int i=0; i<m; ++i) {
        int from, to, cost;
        cin >> from >> to >> cost;
        mp[from].push_back({cost, to});
    }

    cin >> start >> end;
    pair<int, vector<int>> info = dijkstra(n, start, end, mp);

    cout << info.first << '\n' << info.second.size() << '\n';
    for(int i: info.second) cout << i << ' ';
    return 0;
}
