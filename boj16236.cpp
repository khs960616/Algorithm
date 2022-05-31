#include <bits/stdc++.h>
using namespace std;
/*
  https://www.acmicpc.net/problem/16236
  BFS, 구현 
*/

int n;
int sharkSize = 2;
int sharkEats = 0;
vector<vector<int>> info;
vector<int> fishs = {0, 0, 0, 0, 0, 0, 0};  //크기별 생선이 몇마리씩 있는 지 저장 
vector<pair<int, int>> dirs = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };

bool isRemainSmallFish() {
    for(int i=1; i<=6; ++i) {
        if(i>=sharkSize) break;
        if (fishs[i] != 0) return true;
    }
    return false;
}

void eatFish(pair<int, int>& currentPosition, int y, int x) {
    --fishs[info[y][x]];  //먹은 생선 갯수 -1
    info[y][x] = 9; //생선을 먹는 경우 상어는 이동 
    info[currentPosition.first][currentPosition.second] = 0; // 이전 상어의 위치는 0
    currentPosition.first = y;
    currentPosition.second = x;
    sharkEats++;
    if(sharkSize == sharkEats) {
        sharkSize++;
        sharkEats = 0;
    }
}

int bfs(pair<int, int>& currentPosition) {
    int resultCnt = INT_MAX;
    int resultY = INT_MAX;
    int resultX = INT_MAX;

    vector<vector<int>> isVisit(n, vector<int>(n, false));
    queue<tuple<int, int, int>> q;  // <i, j, 현재 체크한  depth>

    q.push({currentPosition.first, currentPosition.second, 0});
    isVisit[currentPosition.first][currentPosition.second] = true;

    while (!q.empty()) {
        tuple<int, int, int> t = q.front();
        int currentY = get<0>(t);
        int currentX = get<1>(t);
        int currentCnt = get<2>(t);
        q.pop();

        if(resultCnt == currentCnt) break; // depth가 적은 순서를 최우선으로 상어가 이동하므로, 이미 정답이 나온 depth 이상으로는 더 이상 체크할 필요가 없다. 

        for(pair<int, int>dir: dirs) {
            int nextY = currentY + dir.first;
            int nextX = currentX + dir.second;
            int nextCnt = currentCnt + 1;

            bool validCoordinate = (nextY >= 0 && nextY < n) && (nextX >= 0 && nextX < n);
            if(validCoordinate && !isVisit[nextY][nextX] && sharkSize >= info[nextY][nextX]) {
                isVisit[nextY][nextX] = true;
                q.push({nextY, nextX, nextCnt});
                
                if(info[nextY][nextX] != 0 && sharkSize > info[nextY][nextX]) {
                    resultCnt = min(resultCnt, nextCnt);
                  //depth가 동일한 경우 > 1. y좌표가 적은 순서,  2. y좌표가 동일한 경우 x좌표가 적은 순서대로 상어가 다음에 잡아먹을 생선의 위치를 갱신함 
                    if(resultY > nextY || (resultY == nextY && resultX >= nextX) || resultY == INT_MAX) {
                        resultY = nextY;
                        resultX = nextX;
                    } 
                }   
            }
        }
    }

    if(resultCnt != INT_MAX) eatFish(currentPosition, resultY, resultX);
    return resultCnt != INT_MAX ? resultCnt : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;

    int answer = 0;
    pair<int, int> currentPosition;
    info = vector<vector<int>>(n, vector<int>(n, 0));

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            cin >> info[i][j];

            if(info[i][j] != 9) {
                 ++fishs[info[i][j]];
                continue;
            } 
            currentPosition.first = i;
            currentPosition.second = j;
        }
    }

    while (isRemainSmallFish()) {
        int tryEatFish = bfs(currentPosition);
        if(tryEatFish == 0) break;  // 더 이상 생선을 먹을 수 없는 경우 
        answer += tryEatFish;
    }

    cout << answer;
    return 0;   
}
