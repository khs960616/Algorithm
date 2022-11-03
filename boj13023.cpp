#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/13023
  ABCDE
  DFS
  ---
  그래프의 각 정점에서 DFS를 통해 길이가 4이상되는 경로가 존재하는지를 확인하면 되는 문제
*/

unordered_map<int, vector<int> > ump;
bool flag = false;

void dfs(vector<bool>& is_visited, int vertax, int cnt) {
    if(flag) return;
    if(cnt >= 4) {
        flag = true;
        return;
    }

    is_visited[vertax] = true;
    for(int i: ump[vertax]) {
        if(is_visited[i]) continue;
        dfs(is_visited, i, cnt+1);
    }
    is_visited[vertax] = false;
}

int main() {
    int n, m;
    cin >> n >> m;
    for(int i=0; i<m; ++i) {
        int from, to;
        cin >> from >> to;
        ump[from].push_back(to);
        ump[to].push_back(from);
    }

    vector<bool> is_visited(n, false);
    for(auto a: ump) {
        dfs(is_visited, a.first, 0);
        if(flag) break;
    }

    int answer = flag ? 1 : 0;
    cout << answer;
    return 0;
}
