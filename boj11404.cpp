#include <bits/stdc++.h>
#define INF 100000005
using namespace std;

void floydWarshall(vector<vector<int>>& v, int n) {
    for(int k=1; k<n+1; ++k) {
        for(int i=1; i<n+1; ++i) {
            for(int j=1; j<n+1; ++j) {
                if(i==j) continue;
                v[i][j] = min(v[i][j], v[i][k]+v[k][j]);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> v(n+1, vector<int>(n+1, INF));
    for(int i=0; i<m; ++i) {
        int from, to, distance;
        cin >> from >> to >> distance;
        v[from][to] = min(v[from][to], distance);
    }

    floydWarshall(v, n);

    for(int i=1; i<n+1; ++i) {
        for(int j=1; j<n+1; ++j) {
            if(v[i][j] == INF) cout << 0;
            else cout << v[i][j];
            cout << ' ';
        }
        cout << '\n';
    }

    return 0;   
}
