#include <bits/stdc++.h>
#define X 1000000007
using namespace std;

/*
https://www.acmicpc.net/problem/13172
Σ
거듭제곱 빠르게 구하기, 정수론 모듈러, 합동 개념 
---
≡ : 합동
정수 a, b를 양의 정수 m으로 나눈 나머지가 같을 때, a와 b가 m을 법으로 하여 합동이라 한다.
즉 a % m == b % m 을 의미하며, 이를 m ∣ (a-b) 형태로 표현할 수 있다.
 기호로 표현하면 : a ≡ b (mod m)
*/
int M, N, S;

int get_gcd(int a, int b) {
    if(b == 0) return a;
    return get_gcd(b, a % b);
}

long long convert_num(long long s, long long n) {
    return (s*n) % X;
}

long long get_reciprocal(int n) {
    long long ret = 1;
    long long lv = n;
    long long cnt = X - 2;

    while(cnt != 0) {
        if(cnt % 2 != 0) ret = (ret * lv) % X;
        lv = (lv*lv) % X;
        cnt /= 2;
    }
    return ret % X;
}

int main() {
    cin >> M;
    long long ret = 0;
    for(int i=0; i<M; ++i) {
        cin >> N >> S;
        int gcd = get_gcd(S, N);
        S /= gcd; N /= gcd; 
        long long reciprocal = get_reciprocal(N);
        ret = ((ret) + ((S * reciprocal) % X)) % X;
    }
    cout << ret << '\n';
}
