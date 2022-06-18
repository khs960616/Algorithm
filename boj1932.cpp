#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1932
정수 삼각형
---
각 depth에서 자기자신의 index에 해당하는 값중, index-1 (왼쪽 대각선위 node) index(왼쪽 오른쪽위 node)의 값과 더한 max값을 차례로 구한다.
마지막 depth에서 가장 큰 값을 가지고 있는 값이 정답임 
*/
int getMaxValue(vector<int> v, int num, int depth, int index) {
    if(depth == 0) return num;
    if(index == depth) return num+v[depth-1];

    int ret = num;

    const int start = max(index-1, 0);

    for(int i = start; i <= index; ++i) {
        ret = max(ret, num+v[i]);
    }

    return ret;
}

int main() {
    int n, answer = 0;
    cin >> n;

    vector<vector<int>> triangle;
    for(int i=0; i<n; ++i) {
        vector<int> v;
        for(int j=0; j<i+1; ++j) {
            int num = 0;
            cin >> num;
            if(i != 0) {
                num = getMaxValue(triangle[i-1], num, i, j);
            }
            v.push_back(num);
        }
        triangle.push_back(v);
    }

    cout << *max_element(triangle[n-1].begin(), triangle[n-1].end());
    return 0;   
}
