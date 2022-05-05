#include <bits/stdc++.h>
using namespace std;
//DEBUG F5
/*
첫째 줄에 N과 M이 주어진다. (1 ≤ M ≤ N ≤ 8)
둘째 줄에 N개의 수가 주어진다. 입력으로 주어지는 수는 10,000보다 작거나 같은 자연수이다.
한 줄에 하나씩 문제의 조건을 만족하는 수열을 출력한다. 중복되는 수열을 여러 번 출력하면 안되며, 각 수열은 공백으로 구분해서 출력해야 한다.
수열은 사전 순으로 증가하는 순서로 출력해야 한다.
---
input으로 받은 수를 오름차순으로 정렬시키고 실행하는 경우 n과 m (1)번쨰 문제와 풀이가 동일하다. 
*/
int n, m;
bool isVisit[10];
int answer[10];

void solution(vector<int>& nums, vector<bool>& isVisit, int cnt) {
    if(cnt == m) {
        for(int i=0; i<cnt; ++i) {
            cout << answer[i] << ' ';
        }
        cout << '\n';
        return;
    }

    for(int i=0; i<n; ++i) {
        if(!isVisit[i]) {
            isVisit[i] = true;
            answer[cnt] = nums[i];
            solution(nums, isVisit, cnt+1);
            isVisit[i] = false;
        }
    }
}

int main() {
    cin >> n >> m;

    vector<bool> isVisit(n, false);
    vector<int> nums(n, 0);
    for (int i=0; i<n; ++i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());

    solution(nums, isVisit, 0);
}
