#include <bits/stdc++.h>
using namespace std;

vector<set<int>> dp(8);

/*
https://programmers.co.kr/learn/courses/30/lessons/42895?language=cpp
DP, Memoization, 구현
-----------------------
다시 풀어볼것 
*/
int solution(int N, int number) {
    int continousN = 0;
    for(int i=0; i<8; ++i) {
        continousN = continousN*10 + N;
        dp[i].insert(continousN);
    }
    
    for(int i=1; i<8; ++i) {
        for(int j=0; j<i; ++j) {
            for(int num1: dp[j]) {
                for(int num2: dp[i-j-1]) {
                    dp[i].insert(num1+num2);
                    dp[i].insert(num1-num2);
                    dp[i].insert(num1*num2);
                    if(num2 != 0) {
                        dp[i].insert(num1 / num2);
                    }
                }
            }
        }
    }
    
    for(int i=0; i<8; ++i) {
        if(dp[i].find(number) != dp[i].end()) {
            return i+1;
        }
    }
    return -1;
}

/*
초기 문제 풀이시 vector<int> dp[320001] 로 잡고 dp[i] -> i번째까지 도달하는데 필요한 n의 최소 개수로 접근하려했으나 
풀이가 너무 복잡해지고 케이스를 나누기 어려워서 구현에 실패

dp[i] -> i개의 n으로 만들수 있는 숫자들의 집합   // 해당 개념으로 바꾸면 문제풀이가 굉장히 쉬워졌다.. 

i개의 n으로 만들 수 있는 수를 생각해보면
1) i개의 n을 연속적으로 이어붙힌 수
2) j개 n으로 만들 수 있는 수,  (i-j)개로 만들 수 있는 수  두가지 수를 사칙연산을 통해 만들 수 있는 수 
두 가지 케이스가 존재한다. 

8번 반복하며 만드는 수를 생각해보자 (중복은 따로 고려하지 않는다면)
ex) n = 5라면

1개로 만들수 있는 수 
5

2개로 만들 수 있는 수 
case 1 : 5 + 5
case 2 : 55
case 3 : 5 - 5
case 4 : 5 / 5
case 5 : 5 * 5

3번째 
case 1 의 결과에 사칙연산, n을 이어붙히는 경우 -> 총 5개
case 2 의 결과에 사칙연산, n을 이어붙히는 경우 -> 총 5개
...
case 2 의 결과에 사칙연산, n을 이어붙히는 경우 -> 총 5개

연산의 종류가 5개 이므로 i개의 n으로 만들 수 있는 수는 5^(i-1) (i>=1 && i<=8) 이다. (중복되는 수를 무시한다면)
*/
