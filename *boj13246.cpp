#include <bits/stdc++.h>
using namespace std;
/*
https://www.acmicpc.net/problem/13246
행렬제곱의 합
분할정복 
---
점화식
*/
long long n, b;
vector<vector<long long>> s;
vector<vector<long long>> e; //항등행렬 

//행렬 곱 
vector<vector<long long>> sMul(vector<vector<long long>> a, vector<vector<long long>> b) {
    vector<vector<long long>> c(n, vector<long long>(n, 0));
    for(long long i=0; i<n; ++i) {
        for(long long j=0; j<n; ++j) {
            for(long long k=0; k<n; ++k) {
                c[i][j] = (c[i][j] + (a[i][k] * b[k][j])) % 1000;
            }
        }
    }
    return c;
}

//행렬 합
vector<vector<long long>> sAdd(vector<vector<long long>> a, vector<vector<long long>> b) {
    vector<vector<long long>> c(n, vector<long long>(n, 0));
    for(long long i=0; i<n; ++i) {
        for(long long j=0; j<n; ++j) {
            c[i][j] = (a[i][j]+b[i][j]) % 1000;
        }
    }
    return c;
}

//행렬 n제곱 
vector<vector<long long>> sPow(long long n) {
    vector<vector<long long>> ret = e;
    vector<vector<long long>> base = s;

    while(n) {
        if(n%2) ret = sMul(ret, base);
        base = sMul(base, base);
        n/=2;
    }

    return ret;
}

//Recursive
vector<vector<long long>> calcAnswer(long long n) {
    if(n==1) return s;

    vector<vector<long long>> ret = sMul(calcAnswer(n/2), sAdd(e, sPow(n/2)));
    if(n%2) ret = sAdd(ret, sPow(n));

    return ret;
}

int main() {
    cin >> n >> b;
    s = vector<vector<long long>>(n, vector<long long>(n, 0));
    e = vector<vector<long long>>(n, vector<long long>(n, 0));
    for(long long i=0; i<n; ++i) {
        for(long long j=0; j<n; ++j) {
            cin >> s[i][j];
            s[i][j]%=1000;
            if(i==j) e[i][j] = 1;
        }
    }

    vector<vector<long long>> answer = calcAnswer(b);

    for(long long i=0;i<n; ++i) {
        for(long long j=0; j<n; ++j) {
            cout << answer[i][j] << ' ';
        }
        if(i!=n-1) cout << '\n';
    }
    return 0;
}
