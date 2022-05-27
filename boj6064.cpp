#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/6064
유클리드 호제법
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
        int ret = -1;
        int currentY = x;
        for(int i=x; i<=max; i+=m, currentY+=m) {
            currentY %= n;
            if(currentY == 0) currentY = n;
            if(currentY == y) {
                ret = i;
                break;
            }
        }

        cout << ret << '\n';
    }
    return 0;   
}
