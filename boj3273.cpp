#include <bits/stdc++.h>
/*
  https://www.acmicpc.net/problem/3273
  두 수의 합
  투포인터
*/
using namespace std;

int main() {
    int n, k;
    cin >> n;
    
    vector<int> v(n, 0);
    for(int i=0; i<n; ++i) cin >> v[i];
    cin >> k;

    sort(v.begin(), v.end());

    int l = 0;
    int r = v.size() - 1;
    int answer = 0;
    while (l < r) {
        int result = v[l] + v[r];
        if(result < k) ++l;
        else if(result > k) --r;
        else {
            int lCnt = 0;
            int rCnt = 0;

            for(int i=l; i<r; ++i) {
                if(v[l] != v[i]) break;
                ++lCnt;
            }

            for(int j=r; j>l; --j) {
                if(v[r] != v[j]) break;
                ++rCnt;
            }

            answer = (answer + lCnt * rCnt);
            l+=lCnt;
            r-=rCnt;
        }
    }
    
    cout << answer;
}
