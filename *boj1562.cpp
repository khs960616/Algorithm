https://www.acmicpc.net/problem/1562

#include <bits/stdc++.h>
#define MOD 1000000000
#define MAX_STATE 1024

using namespace std;

long long dp[101][10][MAX_STATE]; 

/*
  https://www.acmicpc.net/problem/1562
  계단수
  비스마스킹, dp
  ---
  dp[i][j][k]  -> 길이가 i이며, j로 끝나고 k의 상태를 가지는 계단수의 갯수
  상태: 0~1023 까지 비트마스킹 형태로 10bit로 표현되며 가장 오른쪽 비트부터 숫자 0~9까지를 현재 계단수가 가지고 있는지 여부를 나타낸다.
  ex) 0000000010 -> 1로만 이루어진 계단수,  
  
  ---
  기본적인 점화식의 형태는 다음과 같다.
  
  dp[i][j][k|(1<<j)] = dp[i-1][j-1][k] + dp[i-1][j+1][k];
  
  마지막 숫자가 j-1, j+1인 숫자 뒤에 j가 추가되어야 숫자가 계단수임이 보장된다.
  또한 j번째 숫자가 추가되기 위해서는 현재 dp배열의 상태에는 j번째 숫자가 포함됨이 보장되야한다. 
  별도로 j가 0 또는 9일 때  -1, 10은 예외처리 해주어야한다.
  --
  재귀로 구현한 코드들 
  -  dp의 의미를 조금 다르게 해석해야한다. (기본적으로 dp배열의 인덱스에 대한 해석은 동일)
  dp[i][j][k]  -> 길이가 i이고, 현재 번호가 j, 상태가 k인 계단수로부터 파생될 수 있는 계단 수의 수
  
  https://melonicedlatte.com/algorithm/2018/03/15/160637.html
  
  https://algosketch.tistory.com/m/123 
  dp[i][j][2][2]   -> dp[i][j][0][0] 
  첫번쨰, 두번쨰 인덱스에 대한 정의는 같으나 세번째 인덱스는 계단수에 0을 포함하는지 여부이며, 네번째 인덱스는 계단수에 9를 포함하는지 여부이다. 
  어쩌피 재귀로 구현하면, 함수 호출이 계단수에 알맞게 호출되므로, 0과 9 모두를 포함하면 그 사이에 수들은 모두 포함된다는 아이디어.
*/

int main() {
	int n;
	cin >> n;

	for(int i=1; i<10; ++i) dp[1][i][1<<i] = 1;

	for(int len=2; len<=n; ++len) {
		for(int last_num=0; last_num<10; ++last_num) {
			for(int state=0; state<MAX_STATE; ++state) {
				long long& current_dp_num = dp[len][last_num][state|(1<<last_num)];

				if(last_num) {
					current_dp_num = (current_dp_num + dp[len-1][last_num-1][state]) % MOD;
				} 
				if(last_num != 9) {
					current_dp_num = (current_dp_num + dp[len-1][last_num+1][state]) % MOD;
				}
			}
		}
	}
	
	long long answer = 0;
	for(int i=0; i<10; ++i) {
		answer = (answer+dp[n][i][MAX_STATE-1]) % MOD;
	}
	cout << answer;

	return 0;
}
