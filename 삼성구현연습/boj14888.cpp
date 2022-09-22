#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/14888
  연산자 끼워넣기
  ---
  브루트 포스 
*/

int n;
int answer[2];  // 최솟값, 최대값
int op_cnts[4]; // + - * /
vector<int> nums;

int calc(int prev_result, int value, int op) {
    switch (op) {
    case 0:
        return prev_result+value;
    case 1:
        return prev_result-value;
    case 2:
        return prev_result*value;
    }
    return prev_result/value;
}

void solve(int prev_result, int current_idx) {
    if(current_idx == n) {
        answer[0] = min(answer[0], prev_result);
        answer[1] = max(answer[1], prev_result);
        return;
    }

    for(int i=0; i<4; ++i) {
        if(op_cnts[i] == 0) continue;
        op_cnts[i]-=1;
        solve(calc(prev_result, nums[current_idx], i), current_idx+1);
        op_cnts[i]+=1;
    }
}

int main() {
    answer[0] = INT_MAX;
    answer[1] = INT_MIN;

    cin >> n;
    for(int i=0; i<n; ++i) {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    for(int i=0; i<4; ++i) cin >> op_cnts[i];
    
    solve(nums[0], 1);
    cout << answer[1] << '\n' << answer[0];
}
