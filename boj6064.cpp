#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

/*
https://www.acmicpc.net/problem/6064
카잉 달력
유클리드 호제법 
-------------
10, 12  -> <10, 12> 가 되기 위해 필요한 수:
x도 주어진 수 M을 만족해야하며, y로 주어진 수 N을 만족시켜야 하므로
최소 두수의 공배수만큼은 이동해야 (M, N)의 순서쌍을 얻을 수 있다. 
*/

int m, n;

int gcd(int base, int mod) {
    if(mod == 0) return base;
    return gcd(mod, base%mod);
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int m, n, x, y;
        cin >> m >> n >> x >> y;

        int max = m*n/gcd(m, n);
        int currentY = x;
        int ret = -1;
        for(int i=x; i<=max; i+=m, currentY+=m) {
            currentY %= n;

            if(currentY == y) {
                ret = i;
                break;
            }
        }

        cout << ret << '\n';
    }
    return 0;   
}
