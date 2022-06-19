#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/25289
가장 긴 등차 부분 수열
다시 풀어볼 것
---
dp
공차가 나올수 있는 구간을 고정해두고, 각각 DP를 돌리는 방식 
*/
int getMaxLength(int comDiff, vector<int> v) {
    vector<int> answer(101, 0); 
    int vSize = v.size();

    for(int i=0; i<vSize; ++i) {
        int diff = v[i]-comDiff;
        if(diff < 1 || diff > 100) {
            answer[v[i]] = 1;
            continue;
        }

        answer[v[i]] = answer[diff]+1;  
    }
    
    int ret = *max_element(answer.begin(), answer.end());
    return ret;
}

int main() {
    int n, answer = 0;
    cin >> n;
    vector<int> v(n, 0); 

    for(int i=0; i<n; ++i) cin >> v[i];
    for(int i=-99; i<100; ++i) answer = max(answer, getMaxLength(i, v));

    cout << answer;
    return 0;   
}
