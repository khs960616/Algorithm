#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

/*
https://www.acmicpc.net/problem/11444
피보나치 수 6
---
다시 풀어볼것.. 
*/
vector<vector<long long>> operator *(vector<vector<long long>> v1, vector<vector<long long>> v2) {
    vector<vector<long long>> ret(2, vector<long long>(2, 0));
    for(int i=0; i<2; ++i) {
        for(int j=0; j<2; ++j) {
            for(int k=0; k<2; ++k) {
                ret[i][j] += (v1[i][k] * v2[k][j]); 
                ret[i][j] %= MOD;
            }
        }
    }

    return ret;
}

int main() {
    long long n;
    cin >> n;
    vector<vector<long long>> fibo = { {1,1}, {1,0} };
    vector<vector<long long>> answer = { {1,0}, {0,1} };

    while(n>0) {
        int modFlag = n % 2;
        if(modFlag == 1) answer = answer * fibo;
        fibo = fibo * fibo;
        n /= 2;
    }

    cout << answer[0][1];
    return 0;   
}

/*
  참고 사이트 : https://driip.me/00556a4c-0782-4c5b-a86a-8e27e5f4ac1b
  들어오는 Input의 크기가 굉장히 크기 때문에 일반적인 방법으로 피보나치 수를 구할 수 없다.
  최소한 O(log n) 수준으로 시간복잡도를 잡아야 풀 수 있다.
  
  해당 문제에서는 선형 점화식의 대표적인 예인 피보나치 수를 행렬 거듭제곱의 형태로 바꾸는 것을 찾았어야한다.
 
*/
