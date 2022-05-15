#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11049
행렬곱셈순서
DP, memoization
----------------
상태 : 현재 곱셈의 최소 횟수를 구하는 구간

*/
//DEBUG F5

int t;
vector<pair<int, int>> v;
vector<vector<int>> m;  // [i][j] 까지의 곱셉연산 최소 수 

int calcMin(int startIdx, int endIdx) {
    if(startIdx == endIdx) return m[startIdx][endIdx] = 0;  //자기 자신인 경우 곱셈의 횟수는 없다.
    int& ret = m[startIdx][endIdx];

    if(endIdx-startIdx == 1)  ret = v[startIdx].first * v[startIdx].second * v[endIdx].second; //서로 인접한 행렬인 경우 두 행렬의 곱시 일어나는 곱셈의 수를 반환
    if(ret!=INT_MAX) return ret;

    for(int i=startIdx; i<endIdx; ++i) {
        int currentCost = v[startIdx].first *v[i+1].first * v[endIdx].second; 
        // currentCost -> calcMin(startIdx, i) 와 calcMin(i+1, endIdx) + currentCost) 두 구간으로 나눈 행렬곱을 하나의 행렬로 합치기 위해 필요한 cost 
        ret = min(ret, calcMin(startIdx, i) + calcMin(i+1, endIdx) + currentCost);
    }
    return ret;
}

int main() {
    cin >> t;
    m = vector<vector<int>>(t, vector<int>(t, INT_MAX));

    for(int i=0; i<t; ++i) {
        int j, k;
        cin >> j >> k;
        v.push_back(make_pair(j, k));
    }

    cout << calcMin(0, t-1);
    return 0;
}
