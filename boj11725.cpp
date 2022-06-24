#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/11725
  트리의 부모 찾기 
  ---
  루트가 1로 고정되어있는 트리이므로 
  1부터 BFS로 각 노드들을 순차적으로 탐색하면 된다. (이때, 자기 자신을 queue에 집어넣도록 한 노드가 루트 노드가 된다.)
*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    vector<int> parents(n+1, -1);
    vector<vector<int>> edges(n+1, vector<int>());

    for(int i=0; i<n-1; ++i) {
        int from, to;
        cin >> from >> to;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    
    queue<int> q;
    q.push(1);
    parents[1] = 0;

    while(!q.empty()) {
        int currentNode = q.front();
        q.pop();
        
        for(int connectedNode: edges[currentNode]) {
            if(parents[connectedNode] != -1) continue;
            parents[connectedNode] = currentNode;
            q.push(connectedNode);
        }
    }

    for(int i=2; i<n+1; ++i) cout << parents[i] << '\n';
    return 0;
}
