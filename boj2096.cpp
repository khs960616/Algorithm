#include <bits/stdc++.h>
#define INF 999999
using namespace std;

/*
  https://www.acmicpc.net/problem/2096  
  내려가기 
  ---
  DP
  구현은 비교적 간단하나, 최대 input Size 100,000에 메모리 제한이 4MB 이므로
  최대값, 최소값을 DP를 구하는 과정에서 모두 저장하면 메모리 제한에 걸리게된다.
  현재 최대값, 최소값을 갱신하고자하는 Line과 그 이전줄의 최대값, 최소값만을 저장해놓고 지속적으로 갱신하면 문제 조건을 만족시킬 수 있다.
*/
vector<int> dirs = {-1, 0, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    
    vector<int> input(3, 0);
    vector<int> prevMin(3, 0);
    vector<int> prevMax(3, 0);
    vector<int> currentMin(3, 0);
    vector<int> currentMax(3, 0);

    for(int i=0; i<3; ++i) {
        cin >> input[i];
        prevMax[i] = prevMin[i] = input[i];
    }

    for(int i=1; i<n; ++i) {
        for(int j=0; j<3; ++j) {
            cin >> input[j];

            int maxPrevElement = -1;
            int minPrevElement = INF;

            for(int dir: dirs) {
                int adj = j + dir;
                if(adj<0 || adj>2) continue;
                maxPrevElement = max(maxPrevElement, prevMax[adj]);
                minPrevElement = min(minPrevElement, prevMin[adj]);
            }

            currentMax[j] = input[j] + maxPrevElement;
            currentMin[j] = input[j] + minPrevElement;
        }

        for(int j=0; j<3; ++j) {
            prevMax[j] = currentMax[j];
            prevMin[j] = currentMin[j];
        }
    }

    cout << *max_element(prevMax.begin(), prevMax.end()) << ' ';
    cout << *min_element(prevMin.begin(), prevMin.end());
    return 0;
}
