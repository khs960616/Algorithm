#include <bits/stdc++.h>
using namespace std;

map<int, int> snakes;
map<int, int> ladders;

/*
https://www.acmicpc.net/problem/16928
bfs 
*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, answer = INT_MAX;
    cin >> n >> m;

    for(int i=0; i<n; ++i) {
        int y, x;
        cin >> y >> x;
        ladders[y-1] = x-1;
    }

    for(int i=0; i<m; ++i) {
        int y, x;
        cin >> y >> x;
        snakes[y-1] = x-1;
    }

    vector<bool> isVisit(100, false);
    queue<pair<int, int>> q;
    q.push({0, 0});
    isVisit[0] = true;

    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();

        if(p.first == 99) {
            cout << p.second;
            break;
        }

        for(int i=1; i<7; ++i) {
            int nextX = p.first + i;
            if(nextX >= 100) break;

            if(ladders[nextX] != 0) nextX = ladders[nextX]; // 해당 위치에 사다리가 존재한다면 무조건 사다리로 이동한 위치로 이동
            if(snakes[nextX] != 0) nextX = snakes[nextX];   // 해당 위치에 뱀이 존재한다면 무조건 뱀을 타고 이동한 위치로 이동 
            if(!isVisit[nextX]) {
                isVisit[nextX] = true;      // queue(bfs)를 이용하므로 노드를 중복해서 방문할 필요가 없음 (재방문하는 경우, bfs 특성상 최소 경우가 될 수 없으므로)
                q.push({nextX, p.second+1});
            }
        }

    }
    
    return 0;   
}
