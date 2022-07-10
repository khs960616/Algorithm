#include <bits/stdc++.h>
#define MAX 100000
using namespace std;

/*
  https://www.acmicpc.net/problem/12851
  숨박꼭질 2
  ----------------
  BFS
*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k, cnt = 0;
    cin >> n >> k;
  
    vector<int> costs(MAX+1, INT_MAX);
    queue<pair<int, int>> q;
    q.push({n, 0});

    while (!q.empty()) {
        int position = q.front().first;
        int cost = q.front().second;
        
        if(costs[k] < cost) break;    //BFS 이므로 queue에는 항상 cost가 오름차순으로 정렬되어있으므로,
        costs[position] = cost;
        if(position == k) ++cnt;
        
        q.pop();
        
        // insert시에 cost를 갱신하지 않음으로써 queue에 중복되는 postion이 insert될 수 있게 된다.
        if(position-1 >= 0 && costs[position-1] == INT_MAX) q.push({position-1, cost+1});
        if(position+1 <= MAX && costs[position+1] == INT_MAX) q.push({position+1, cost+1});
        if(position*2 <= MAX && costs[position*2] == INT_MAX) q.push({position*2, cost+1});
    }
    
    cout << costs[k] << '\n';
    cout << cnt;
    return 0;
}
