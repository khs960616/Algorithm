#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2293
동전 1

Memoization, DP
----------------

*/

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n, 0);
    vector<long long> m(k+1, 0); // k값에 도달할 수 있는 (코인의 조합이 중복되지 않는)경우의 수 

    m[0] = 1;
    for(int i=0; i<n; ++i) cin >> v[i];
    sort(v.begin(), v.end());

    for(int i=0; i<n; ++i) {
        for(int j=v[i]; j<=k; ++j) {
            m[j] += m[j-v[i]];
        }
    }
    cout << m[k];
    return 0;
}



/*
실패한 코드
ex) 코인 =  {1, 2, 3, 4, 5, 6}, K = 20
m[20] = m[20-6] + m[20-5] + m[20-4] + m[20-3] + m[20-2] + m[20-1]  << 이런식을 접근함 
이 경우 문제점 : 사용한 동전의 구성이 같은데, 순서만 다른 것은 같은 경우이다. << 해당 문제 조건을 만족 시킬 수 없음 

반례)

m[3] = m[2] + m[1] + m[0] = 2 + 1 + 1 = 4  
----> (1,1,1), (2, 1), (3, 0), (1, 2)   다음과 같이 중복되는 것이 포함되어버림 
m[2] = m[1] + m[0] = 2; -> (1,1) (2)
m[1] = m[0] = 1;     -> (1)


long long calcCost(int remain) {
    if(remain < 0) return 0;
    if(remain == 0) return 1;
    long long& ret = m[remain];
    if(ret != -1) return ret;
    ret = 0;

    for(int i=0; i<n; ++i) {
        int prevRemain = remain - v[i];
        if(prevRemain<0) break;

        ret += calcCost(prevRemain); 
    }
    return ret;
}
*/
