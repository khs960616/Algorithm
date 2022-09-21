#include <bits/stdc++.h>
using namespace std;

int answer = INT_MAX;
int n;
int target;
vector<vector<int> > v;
vector<int> selectedNum;

/*
  https://www.acmicpc.net/problem/14889
  백트래킹
  ---
  https://cocoon1787.tistory.com/170 << 구현 참고 
  
    초기 위 블로그 포스팅 처럼 boolean변수 해서 구현해보려했는데 
      solve(idx+1, selectCnt);
   
    selectedNum[??] = true;
    solve(idx+1, selectCnt);
    selectedNum[??] = false;
    
    이런 식으로 짜놔서, 모든 경우의 수가 안타지게 되서 구현에 실패해서 결국 정수값을 저장하는 식으로 우회함. // 속도면이나 코드 자체가 위 블로그 방식이 좀 더 괜찮은듯.
*/
int get_diff() {
    int team1_sum = 0;
    int team2_sum = 0;

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(i==j) continue;
            int member1 = find(selectedNum.begin(), selectedNum.end(), i) - selectedNum.begin();
            int member2 = find(selectedNum.begin(), selectedNum.end(), j) - selectedNum.begin();

            bool is_pair = (member1 != target) && (member2 != target);
            bool is_not_include = (member1 == target) && (member2 == target);

            if(is_pair) {
                team1_sum += v[selectedNum[member1]][selectedNum[member2]];
                continue;
            }

            if(is_not_include) {
                team2_sum += v[i][j];
            }
        }
    }
    return abs(team1_sum-team2_sum);
}

void solve(int idx, int selectCnt) {
    if(target > (n-idx)+selectCnt) return;
    if(target == selectCnt) {
        answer = min(answer, get_diff());
        return;
    }
    if(idx >= n) return;
    //현재 멤버를 선택하지 않는 경우 
    solve(idx+1, selectCnt);
    //현재 멤버를 선택하는 경우
    selectedNum[selectCnt++] = idx;
    solve(idx+1, selectCnt);
}

int main() {
    cin >> n;  
    target = n/2;
    v = vector<vector<int> >(n, vector<int>(n, 0));
    selectedNum = vector<int>(target, -1);

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            cin >> v[i][j];
        }
    }

    solve(0, 0);
    cout << answer;
}
