#include <bits/stdc++.h>

using namespace std;

/*
https://www.acmicpc.net/problem/17626
DP, Memoization
*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    vector<int> v(n+1, 0);
    v[1] = 1;

    for(int i=2; i<=n; ++i) {
        v[i] = v[i-1] + 1;    // (i-1)을 만들기 위해 필요한 제곱 수의 갯수 + 1 
        for(int j = 2; j*j <= i; ++j) {
            v[i] = min(v[i], v[i-j*j]+1); // (i - j*j)를 만들기 위한 제곱수의 갯수 + j*j (제곱수 1개 추가)
        }
    }  

    cout << v[n];
    return 0;   
}
