#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

/*
https://www.acmicpc.net/problem/2294
동전2
memoization
*/
int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> v(n, 0);
    vector<int> m(k+1, INF);  // m[i] -> i금액을 만족시키기 위해 필요한 동전의 최소 갯수
    m[0] = 0;

    for(int i=0; i<n; ++i) {
        cin >> v[i];

        for(int j=v[i]; j<=k; ++j) {
            m[j] = min(m[j], m[j-v[i]]+1); 
        }   
    }

    int result = (m[k] == INF) ? -1 : m[k];
    cout << result;
    return 0;
}
