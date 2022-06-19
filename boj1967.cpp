#include <bits/stdc++.h>
using namespace std;

void checkElementDistance(int n, int startNode, 
              vector<vector<pair<int, int>>>& edges,  
              vector<int>& distances) {

    priority_queue<pair<int, int>> pq;

    distances[startNode] = 0;
    pq.push({-0, startNode});

    while(!pq.empty()) { 
        int distance = -pq.top().first;
        int currentVertax = pq.top().second;
        pq.pop();
        
        for(pair<int, int> edge : edges[currentVertax]) {
            if(distances[edge.second] != -1) continue;
            distances[edge.second] = edge.first + distance;
            pq.push({-distances[edge.second], edge.second});
        }
    }
    

}

int main() {
    int n;
    cin >> n;

    vector<vector<pair<int, int>>> edges(n+1, vector<pair<int, int>>());
    vector<int> distances(n+1, -1);

    for(int i=1; i<n; ++i) {
        int from, to, distance;
        cin >> from >> to >> distance;
        edges[from].push_back({distance, to});
        edges[to].push_back({distance, from});
    }

    checkElementDistance(n, 1, edges, distances);

    int nextIndex = max_element(distances.begin(), distances.end())-(distances.begin());
    for(int& distance: distances) distance = -1;
    checkElementDistance(n, nextIndex, edges, distances);

    cout << *max_element(distances.begin(), distances.end());
    return 0;   
}
