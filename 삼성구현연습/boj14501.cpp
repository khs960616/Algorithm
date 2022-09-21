/*
https://www.acmicpc.net/problem/14501
퇴사
---
내가푼 거 : DFS   // O(2^n)

DP풀이법 참고 : https://codejin.tistory.com/173 // DP로 푸는게 좀 더 좋을듯함.   O(n)
*/


#include <bits/stdc++.h>
using namespace std;

int answer = 0;
int n = 0;
vector<pair<int, int> > v;

void get_max_cost(int idx, int sum) {
    if(idx >= n) {
        answer = answer > sum ? answer : sum;
        return; 
    }

    // 현재 상담을 선택하지 않고 넘어가는 경우 
    get_max_cost(idx+1, sum);

    // 현재 상담을 선택하는 경우
    if(idx+v[idx].first <= n) {
        get_max_cost(idx+v[idx].first, sum+v[idx].second);
    }
}

int main() {
    cin >> n;
    for(int i=0; i<n; ++i) {
        int cost, value;
        cin >> cost >> value;
        v.push_back({cost, value});
    }
    get_max_cost(0, 0);
    cout << answer;
    return 0;
}
