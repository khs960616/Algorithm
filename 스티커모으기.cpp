#include <bits/stdc++.h>
#define MAX_STICKER_SIZE 100000
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12971
  스티커 모으기
  ---
  DP, 원형벡터 선형으로 바꿔서 생각하는 방법 
  
  dp[i] : i번째 스티커까지 확인했을 때, 스티커를 떼서 얻을 수 있는 최대값 
  문제 조건에 의해 sticker은 원형으로 처음과 끝이 연결된 형태의 벡터이다.
  
  ---
  ex) sticker :[14, 6, 5, 11, 3, 9, 2, 10] 
  
  dp의 진행방향은 왼쪽에서 오른쪽으로 차례대로 진행하며, 점화식은 
  dp[i] = max(dp[pprev_idx]+sticker[i], dp[prev_idx])와 같다.
  즉 사용중인 배열의 결과값은 현재 i번째 스티커에서 i-1번째, i-2번째 순서만을 확인한다.
  이 때, 마지막 원소의 선택여부는 첫번째 스티커의 선택 여부에 종속적이기 때문에, 
  주어진 벡터 전체를 사용하는 경우 첫 번째 스티커와 마지막 스티커가 같이 선택되는 케이스가 생기게 된다. 
  
  따라서 주어진 벡터를 [14, 6, 5, 11, 3, 9, 2]와 [6, 5, 11, 3, 9, 2, 10]와 같이 처음 원소를 선택 여부를 기준으로 
  선형적인 자료구조로 생각하고 dp과정을 진행하면, 문제가 단순해진다.
*/
int s_size;
int dp[MAX_STICKER_SIZE];

void calc_dp_range(vector<int> sticker, int start, int end) {
    for(int i=start; i<end; ++i) {
        int prev_idx = (s_size + i - 1) % s_size;
        int pprev_idx = (s_size + prev_idx - 1) % s_size;
        dp[i] = max(dp[pprev_idx]+sticker[i], dp[prev_idx]);
    }
}

int solution(vector<int> sticker) {
    s_size = sticker.size();
    calc_dp_range(sticker, 0, s_size-1);
    
    int answer = dp[s_size-2];
    memset(dp, 0, sizeof(dp));
    calc_dp_range(sticker, 1, s_size);
    answer = max(answer, dp[s_size-1]);
    return answer;
}
