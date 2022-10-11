#include <bits/stdc++.h>
#define MOD 1000000007

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12907
  거스름돈
  ---
  DP
  dp[i] : 보유한 돈으로 i원을 거슬러 줄 수 있는 경우의 수 
  dp[i] = dp[i] + dp[i-money] 
  
  점화식 자체는 단순하나 중복을 제거해야하는 것을 생각해내기가 어려웠다.
  ex) 
  moneys = {1, 2} 일 때, 
  3원을 거슬러줄 수 있는 경우는 {1, 2},   {2, 1} 이므로 이러한 중복을 제거해줘야한다. -> 각 동전별로 dp값을 따로 계산해주면 된다. 
  
  초기 실패한 코드는 
  
  for(int i=1; i<=n; ++i) {
    for(int money: moneys) {
      dp 갱신 코드 .. 
    }
  }
  형태로 위와 같이 중복되는 케이스가 존재하는 경우 통과하지 못했음. 
*/
using namespace std;
int dp[100001];

int solution(int n, vector<int> moneys) {
    dp[0] = 1;
    
    sort(moneys.begin(), moneys.end());
    for(int money: moneys) {
        for(int i=money; i<=n; ++i) {
            dp[i] = (dp[i] + dp[i-money]) % MOD;
        }
    }
    
    return dp[n];
}
