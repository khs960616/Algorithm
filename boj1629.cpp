#include <bits/stdc++.h>

using namespace std;

/*
https://www.acmicpc.net/problem/1629
곱셈
분할 정복
*/
int main() {
    long long base, target, mod;
    cin >> base >> target >> mod;
    long long result = 1;

    while(target != 0) {
        if(target % 2 != 0) {
            result = (result * base) % mod;
        }
        target/=2;
        base = (base * base) % mod;
    }

    cout << result;
    return 0;   
}
