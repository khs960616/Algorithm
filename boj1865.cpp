#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

using namespace std;

/*
https://www.acmicpc.net/problem/1865
웜홀
------------------------------------
벨만포드 알고리즘
1. 한 정점에서 다른 정점까지의 최단 경로를 구할 수 있다.
2. 다익스트라가 그리디한 방식으로 최단 경로를 구하기 때문에 간선에 음수 가중치가 존재하면 최적해 보장이 안되는 것과 다르게, 벨만포드는 
음수 가중치가 존재해도 모든 경로를 체크하기 때문에 최적해가 보장된다.
3. 음수로 된 간선이 존재할 때, 해당 간선을 포함하는 cycle이 생기는 경우 최적해를 보장하기 어렵다. (해당 간선을 통해 무한히 cost가 낮아지므로)

-----
1. 출발하고자하는 노드를 설정한다. 
2. 최단 거리 테이블을 초기화 시킨다.
3. 현재 정점과 연결된 모든 간선을 확인한다.
4. 각 간선을 거쳐 다른 노드로 가는 비용을 계산하여 최단 거리 테이블을 갱신한다.
5. 3, 4번의 과정을 반복한다.

*/
void bellmanFord(vector<tuple<int, int, int>> connectInfos, int n, int startNode) {
    vector<long long> minDistance(n+1, INF);

    for(int i=0; i<n; ++i) {
        for(tuple<int, int, int> connectInfo: connectInfos) {
            int from = get<0>(connectInfo);
            int to = get<1>(connectInfo);
            int cost = get<2>(connectInfo);
          
            /* 
              최단 경로를 구하는 문제라면 일반적으로 minDistance[index]값이 INF상태로 아직 도달하지 않는 경우 체크하지 않는다.
              즉 현재까지 단계에서 한번이라도 방문한 노드들과 연결된 간선만 체크한다. 
              만일 이렇게 하지 않으면, 서로 연결되지 않은 정점들간에도 최단경로 값이 갱신되므로 최적해가 보장되지 않는다.
              해당 문제에서 요구하는 바는 음수 cycle이 존재하는지 여부를 체크하는 것이므로, 오히려 해당 조건을 뺴서 모든 정점을 체크해야한다. 
              (연결되지 않은 노드간에도 음수 cycle이 존재할 수 있으므로) 
            */
            if(minDistance[to] > minDistance[from] + cost) {
                minDistance[to] = minDistance[from] + cost;

                if(i==n-1) {
                    cout << "YES" << '\n';
                    return;
                }
            }
        }
    }

    cout << "NO\n";
}

int main() {
    int tc;
    cin >> tc;
    
    for(int i=0; i<tc; ++i) {
        int n, m, w;
        cin >> n >> m >> w;

        vector<tuple<int, int, int>> connectInfos;

        for(int j=0; j<m; ++j) {
            int s, e, t;
            cin >> s >> e >> t;
            connectInfos.push_back({s, e, t});
            connectInfos.push_back({e, s, t});
        }
        for(int j=0; j<w; ++j) {
            int s, e, t;
            cin >> s >> e >> t;
            connectInfos.push_back({s, e, -t});
        }

        bellmanFord(connectInfos, n, 1);
    }
    return 0;
}
