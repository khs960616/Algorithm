#include <bits/stdc++.h>
#define MAX 100001
using namespace std;

/*
https://www.acmicpc.net/problem/13549
숨박꼭질 3
---
0-1 BFS

모든 Operation의 가중치가 같지 않다. (+1, -1 *2) 따라서 순서에 무관하게 BFS를 그냥 돌리게 되면 결과값이 항상 최단거리(cost)임을 보장할 수 없다.

구현 방식
1. 우선순위큐를 사용하여 cost가 낮은순으로 정렬되도록 삽입한다. (이때 결과값이 도달하고자하는 k값에 도달하면 우선순위큐의 성질에 의해 항상 참이 된다.)
2. deque를 사용하여 cost가 0이 드는 연산의 경우 queue의 맨 앞에 삽입하도록 한다. (bfs를 사용하는 경우 queue는 FIFO 이므로, 현재 삽입되는 원소의 cost와 다음 원소의 cost는 같다.)

*/

vector<bool> isVisit(MAX, false);
bool isValid(int position) {
    return position >= 0 && position <= 100000 && !isVisit[position];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;

    deque<pair<int, int>> q;
    q.push_back({n, 0});

    while (!q.empty()) {
        int position = q.front().first;
        int cost = q.front().second;
        if(position == k) {
            cout << cost;
            break;
        }
        q.pop_front();

        if(position != 0 && isValid(position*2)) {
            q.push_front({position*2, cost});
            isVisit[position*2] = true;
        }
        if(isValid(position-1)) {
            q.push_back({position-1, cost+1});
            isVisit[position-1] = true;
        }
        if(isValid(position+1)) {
            q.push_back({position+1, cost+1});
            isVisit[position+1] = true;
        }
    }
    
    return 0;
}
