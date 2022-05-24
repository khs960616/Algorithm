#include <bits/stdc++.h>

using namespace std;

#define mod 1000000000
int n, k;
vector<vector<int>> v;
/*
    https://www.acmicpc.net/problem/2225
    합분해
    DP, Memoization
    -------------------
    0 ~ n 까지 정수 k개를 더해서 합이 n이 되는 경우의 수
    N(1 ≤ N ≤ 200), K(1 ≤ K ≤ 200)
    덧셈의 순서가 바뀐 경우는 다른 경우로 센다(1+2와 2+1은 서로 다른 경우). 또한 한 개의 수를 여러 번 쓸 수도 있다.

*/

int calcCnt(int select, int sum) {
    if(select == 1) return 1;

    int& ret = v[select][sum];
    if(ret != -1) return ret;
    
    ret = 0;
    for(int i=0; i<=n; ++i) {
        if(sum-i<0) break;
        ret = (ret + calcCnt(select-1, sum-i)) % mod;
    }

    return ret % mod;
}

int main() {
    cin >> n >> k;
    v = vector<vector<int>>(k+1, vector<int>(n+1, -1)); // v[i][j] = i개 만큼 더해서 j가 될 수 있는 경우의 수

    cout << calcCnt(k, n);
    return 0;   
}
