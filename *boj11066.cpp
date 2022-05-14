#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11066
파일 합치기
DP
---
왼쪽 구간합 + 오른쪽 구간합의 최소값을 memoization해서 답을 도출한다. 
1. m[i][j] -> v[i] ~ v[j] 까지 구간의 최소 cost

m[i][i] -> 0 (파일 하나만 존재하는 경우 별도의 추가적인 cost가 필요하지 않고 자기자신의 value만 cost로 생각하면된다)

ex) 
40 30 30
40 60  (cost 60 + 0~2까지 전체 원소의 합) 

------
초기 파일을 합칠때 연속적인 index 끼리 합쳐나가는 조건을 보지 못해서 priority_queue (min heap)를 사용해서 처리하려하다 실패함..

문제로부터 유추해야 될 상태들 : 현재 최소 cost를 구하고자 하는 "구간"  
*/


int fileCnt;
vector<int> v;
vector<vector<int>> m;

int getSum(int startIdx, int endIdx) {
    int ret = 0;
    for(int i=startIdx; i<=endIdx; ++i) ret+=v[i];
    return ret;
}

int calcCost(int startIdx, int endIdx) {
    if(startIdx > endIdx) return 0x3f3f3f3f;

    int& ret = m[startIdx][endIdx];
    if(endIdx-startIdx == 1) ret = v[startIdx] + v[endIdx];
    if(startIdx==endIdx) ret = 0;
    if(ret != INT_MAX) return ret;

    int sum = getSum(startIdx, endIdx);
    for(int i=startIdx; i<endIdx; ++i) {
        int left = calcCost(startIdx, i);  
        int right = calcCost(i+1, endIdx);   
        ret = min(ret, left+right+sum);
    }

    return ret;
}


int main() {
    int t;
    cin >> t;

    while(t--) {
        cin >> fileCnt;
        v = vector<int>(fileCnt, 0);
        m = vector<vector<int> >(fileCnt, vector<int>(fileCnt, INT_MAX));
        for(int i=0; i<fileCnt; ++i) cin >> v[i];
        cout << calcCost(0, fileCnt-1) << '\n';
    }
    return 0;
}
