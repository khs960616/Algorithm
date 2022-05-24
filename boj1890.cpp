#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/1890
점프
DP, Memoization
-----------
*/
int n;
vector<vector<int>> v;
vector<vector<long long>> cnt;  // 원점에서 cnt[i][j] 까지 올수있는 경우의 수 

long long calcCnt(int y, int x) {
    long long& ret = cnt[y][x];
    if(ret != -1) return ret;
    ret = 0;

    for(int i=0; i<y; ++i) {
        //같은 x축선에서, 현재 좌표의 위쪽에 있는 좌표 중, 현재 좌표로 올 수 있는 경우
        if((i + v[i][x]) == y) ret += calcCnt(i, x); 
    } 

    for(int i=0; i<x; ++i) {
        //같은 y축선에서, 현재 좌표의 왼쪽에 있는 좌표 중, 현재 좌표로 올 수 있는 경우
        if((i + v[y][i]) == x) ret += calcCnt(y, i);
    }
    return ret;
}

int main() {
    cin >> n;
    v = vector<vector<int>> (n, vector<int>(n, 0));
    cnt = vector<vector<long long>>(n, vector<long long>(n, -1));
    cnt[0][0] = 1;

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            cin >> v[i][j];
        }
    }

    cout << calcCnt(n-1, n-1);
    return 0;
}
