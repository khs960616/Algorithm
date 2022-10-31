#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/16953
  A->B
  BFS, 최단 경로
*/

int main() {
    long long a = 0, b = 0;
    cin >> a >> b;

    int answer = -1;
    queue<pair<long long, int> > q;
    q.emplace(a, 1);

    while (!q.empty()) {
        auto [num, cost] = q.front();
        q.pop();

        if(num == b) {
            answer = cost;
            break;
        }

        if(num*2<=b) q.emplace(num*2, cost+1);
        if(num*10+1 <= b) q.emplace(num*10+1, cost+1);
    }
    cout << answer;
}
