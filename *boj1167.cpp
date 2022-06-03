#include <bits/stdc++.h>

using namespace std;
map<int, vector<pair<int, int>>> m;
int answer = 0, target = 0;

/*
  https://www.acmicpc.net/problem/1167
  트리의 지름
  -----------------------------------
  가정)
  1. 임의의 정점 x를 선택하여 y에서 가장 거리가 먼 정점을 DFS를 통해 구해낸다. (이 정점을 y라 하자)
  2. 정점 y에서 거리가 가장 먼 정점을 DFS를 통해 구한다. (이 때 정점을 z라 하자)
  3. 정점 y와 정점 z는 항상 트리의 지름을 나타낸다.
  ---
  트리이므로 각 노드끼리 아예 연결이 되어있지 않는 경우는 없다. 
  
  트리 지름의 시작점 u, 트리의 지름의 끝지점 v라 하자 
  증명)  
  1. 정점 x가 트리의 지름의 시작점 u와 동일한 경우 가정1)에 정점 y의 정의 (x에서 가장 거리가 먼 정점)에 의해 두 정점 x-y 사이의 거리는 트리의 길이이다.
  
  2. 정점 y가 트리의 지름의 끝지점인 v와 동일한 경우 가정1)에 의해 두 정점 x-y사이의 거리는 트리의 길이이다. 
  
  3. 두 정점 x, y의 가장 거리가 먼 경로가 트리의 지름을 이루는 경로와 하나의 정점(t)을 공유하는 경우
      u
    x t  y    왼쪽을 트리라고 가정하자, 이 때 가정에 의해 x-y 사이의 거리는 트리의 지름인 u-v 사이의 거리보다 항상 작거나 같아야 한다.
      v       이 때, (x->t), (t->y)가 두 정점 사이의 최대 거리를 이루므로 간선(t->y)는 항상 (u->t) 또는 (t->v)중 큰 것보다 길이가 같아야한다. 
              (크면 u-v가 트리의 지름이라는 가정에 위배된다 (u->t)+(t->y) or (y->t)+(t->v)가 (u->t->v) 보다 길이가 크게 되므로)
              따라서 (t->y) = max((u->t), (t->v)) 이고, 이때 정점 y에서 거리가 가장 먼 정점을 선택하면 트리의 지름이 될 수 밖에 없다.
              
  4. 두 정점 x, y가 가장 거리가 먼 경로가 트리의 지름을 이루는 경로와 하나의 정점도 공유하지 않는 경우 
   
   u  t1   v     왼쪽을 트리라 가정하자, (t1과 t2는 연결되어있다.) 
   x  t2   y     
      z           가정이 틀리다고 가정해보자 (y로부터 거리가 가장 먼 점 z를 선택할 경우, y-z는 지름이 되지 않는다 즉 z는 u또는 v가 아니라고 가정)
                  이 때 z는 y에서와의 거리가 가장 먼 점이므로 (t2->z) 는 max((t1->u), (t1->v)) 보다 항상 크거나 같아야한다.
                  이 경우 u-v를 트리의 지름으로 가정했는데 두 점 u, v는 더 먼 거리에 있는 점 z에 존재하게 되고 주어진 가정에 모순된다. (즉 z가 u 또는 v여야 가정한 조건과 일치한다)
                  
  따라서 가정에 따라 임의의 정점을 선택해 거리가 가장 먼점을 찾는 DFS를 연속으로 두번 실시하면 트리의 지름을 구할 수 있다.
   
*/
void dfs(vector<bool> isVisit, int node, int distance) {
    isVisit[node] = true;

    for(pair<int, int> connectedNode : m[node]) {
        int nodeNum = connectedNode.first;
        if(isVisit[nodeNum]) continue;

        int connectDistance = connectedNode.second;
        int sum = connectDistance + distance;
        isVisit[nodeNum] = true;

        if(sum > answer) {
            answer = sum;
            target = nodeNum;
        }
        dfs(isVisit, nodeNum, sum);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int v;
    cin >> v;

    for(int i=0; i<v; ++i) {
        int currentVertax = 0;
        cin >> currentVertax;

        while(1) {
            int connectedVertax = 0;
            int distance = 0;
            cin >> connectedVertax;
            if(connectedVertax == -1) break;
            cin >> distance;
            m[currentVertax].push_back({connectedVertax, distance});
        }
    }

    vector<bool> isVisit(v+1, false);
    dfs(isVisit, 1, 0);
    dfs(isVisit, target, 0);
    cout << answer;
    return 0;   
}
