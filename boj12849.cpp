#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

//DEBUG F5

long long d;
vector<vector<long long>> v;  //v[i][j] -> i분에 j position에 도달하는 경우의 수 

/*
https://www.acmicpc.net/problem/12849
DP, Memoization 
------------------------------------
지도 정보 : 
m[0] = {1, 2};
m[1] = {0, 2, 3};
m[2] = {0, 1, 3, 4};
m[3] = {1, 2, 4, 5};
m[4] = {2, 3, 5, 7};
m[5] = {3, 4, 6};
m[6] = {5, 7};
m[7] = {4, 6};
*/

long long calcCost(long long minute, int position) {
    if(minute == 0 && position == 0) return 1; //시작 포지션은 0이므로 
    if(minute == 0) return 0; //0에서 시작하지 않는 경우는 구하고자 하는 case가 아님

    long long& ret = v[minute][position];
    if(ret != -1) return ret;
    ret = 0;

    switch (position) {
        case 0:
            ret = (calcCost(minute-1, 1) + calcCost(minute-1, 2)) % MOD;
            break;
        case 1:
            ret = (calcCost(minute-1, 0) + calcCost(minute-1, 2) + calcCost(minute-1, 3)) % MOD;
            break;
        case 2:
            ret = (calcCost(minute-1, 0) + calcCost(minute-1, 1) + calcCost(minute-1, 3) + calcCost(minute-1, 4)) % MOD;
            break;
        case 3:
            ret = (calcCost(minute-1, 1) + calcCost(minute-1, 2) + calcCost(minute-1, 4) + calcCost(minute-1, 5)) % MOD;
            break;     
        case 4:
            ret = (calcCost(minute-1, 2) + calcCost(minute-1, 3) + calcCost(minute-1, 5) + calcCost(minute-1, 7)) % MOD;
            break;
        case 5:
            ret = (calcCost(minute-1, 3) + calcCost(minute-1, 4) + calcCost(minute-1, 6)) % MOD;
            break;
        case 6:
            ret = (calcCost(minute-1, 5) + calcCost(minute-1, 7)) % MOD;
            break;
        case 7:
            ret = (calcCost(minute-1, 4) + calcCost(minute-1, 6)) % MOD;
            break;           
    }

    return ret % MOD;
}

int main() {
    cin >> d;
    v = vector<vector<long long>>(d+1, vector<long long>(8, -1));
    cout << calcCost(d, 0);
    return 0;
}
