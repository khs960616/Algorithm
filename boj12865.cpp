#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/12865
평범한 배낭
knapsack
---
dp, memoization
*/
int n, k;
vector<pair<int, int>> v;
vector<vector<int>> m;

void init() {
    cin >> n >> k;
    v = vector<pair<int, int>>(n);
    m = vector<vector<int>>(n, vector<int>(k+1, -1));
    for(int i=0; i<n; ++i) {
        int weight, value;
        cin >> weight >> value;
        v[i] = {weight, value};
    }
}

int calcCost(int currentIdx, int currentWeight) {
    if(currentIdx == n) return 0;

    int& ret = m[currentIdx][currentWeight];
    if(ret != -1) return ret;

    ret = calcCost(currentIdx+1, currentWeight);
    int remain = currentWeight-v[currentIdx].first;
    if(remain >= 0) {
        ret = max(ret, calcCost(currentIdx+1, remain)+v[currentIdx].second);
    } 

    return ret;
}

int main() {
    init();
    cout << calcCost(0, k);
    return 0;
}
