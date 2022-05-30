#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> graphs;
vector<vector<int>> answer;

/*
https://www.acmicpc.net/problem/11403
경로 찾기 
DP, 플로이드 와샬 
-------------------------------------
플로이드 와샬 
모든 정점 -> 모든 정점으로의 
최단경로, 최대경로, 경로 존재의 여부를 구할 때 유용
*/

int calcReachable(int i, int j) {
    int& ret = answer[i][j];
    if(graphs[i][j] == 1) ret = 1;
    if(ret != -1) return ret;

    ret = 0;
    for(int k=0; k<n; ++k) {
        int sum = calcReachable(i, k) + calcReachable(k, j);
        if(sum == 2) {
            ret = 1;
            break;
        }
    }

    return ret;
}

int main() {
    cin >> n;
    graphs = vector<vector<int>>(n, vector<int>(n, 0));

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            cin >> graphs[i][j];
        }
    }

    answer = vector<vector<int>> (n, vector<int>(n, -1));

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            answer[i][j] = calcReachable(i, j);
            cout << answer[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;   
}
