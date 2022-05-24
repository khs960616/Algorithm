#include <bits/stdc++.h>

using namespace std;
/*
https://www.acmicpc.net/problem/1965
LIS, DP, Memoization
-------------------
*/

int n;
vector<int> v;
vector<int> m;

int main() {
    cin >> n;
    v = vector<int>(n, 0);  //input
    m = vector<int>(n, 1);  //m[i]  i번째 박스를 마지막으로 할때 최대 갯수
    for(int i=0; i<n; ++i) cin >> v[i];

    for(int i=1; i<n; ++i) {
        for(int j=i-1; j>=0; --j) {
            if(v[j]>=v[i]) continue;
            m[i] = max(m[j]+1, m[i]);
        }
    }

    cout << *max_element(m.begin(), m.end());

    return 0;   
}
