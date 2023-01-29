#include <bits/stdc++.h>
#define INF 3000
using namespace std; 

string s;
int s_size;
int dp[2500][2500];
int answer[2500];

/*
  https://github.com/khs960616/Algorithm/new/master
  팰린드롬 분할 
  ---
  DP, 다시 풀어볼것 
  
  1. 회문 판단 알고리즘 작성 
     총 문자열의 길이가 최대 2,500 이므로 N^2인 알고리즘을 써도 통과 가능
     
     1-1) dp[i][j] 배열을 준비한다. 이 때, dp배열의 의미는 i~j (i<=j) 범위에 substring이 회문임을 나타내는 배열이다. 
     
     1-2) 길이가 1인 모든 문자열과, 길이가 2인 문자열 중, 동일한 알파뱃만 동일한 문자열은 모두 회문이다. 이를 초기값으로 설정한다.
     
     1-3) 시작 인덱스부터 문자열의 끝까지, 길이가 3인 문자열~문자열 전체의 범위까지 회문이 있는지 검사한다.
          이 때 만일 k ~ k+range 인덱스에 해당하는 부분 문자열을 검사한다면, k번째 문자와 k+range문자가 같고, (k+1, k+range-1)문자열이 팰린드롬 문자열이면
          dp[k][k+range] 또한 팰린드롬 문자열이 된다. 
  
  2. 최소 분할 정보 저장
     answer[i] 배열을 준비한다. 해당 배열은 0~i번째 문자열까지 팰린드롬 문자열로 문자열을 분할하는 최소의 분할 수를 저장한다. 
     answer[0] 은 0~0까지의 문자열, 즉 맨 처음 문자만 포함하므로 초기값을 1로 설정한다. 
  
     for(int end_pos = 1; end_pos<s_size; ++end_pos) {
		    answer[end_pos] = INF;
		    for(int start_pos=0; start_pos<=end_pos; ++start_pos) {
			    if(dp[start_pos][end_pos]) {
				    answer[end_pos] = min(answer[end_pos], answer[start_pos-1]+1);
			    }
		    }
	   }
     이 후 각 부분 문자열을 검사한다. 
     answer[end_pos] = min(answer[end_pos], answer[start_pos-1]+1);
     해당 점화식은, 만일 dp[start_pos][end_pos]가 팰린드롬 수라면  0~end_pos 까지의 팰린드롬의 분할은
     (0~start_pos-1)까지 최소 분할의 수 + (dp[start_pos][end_pos] 가 이루는 팰린드롬수 1개) 중 가장 작은 값임을 의미한다. 
*/

void palindrome() {
	cin >> s;
	s_size = s.size();
	dp[0][0] = true;
	for(int start_pos = 1; start_pos < s_size; ++start_pos) {
		dp[start_pos][start_pos] = true;
		if(s[start_pos-1] == s[start_pos]) dp[start_pos-1][start_pos] = true;
	}
  
  // range는 시작점을 포함하는 범위 이므로 실질적으로 range 2이면 범위가 0, 1, 2 이렇게 3개의 인덱스를 포함하는 범위이다. 
	for(int range = 2; range<s_size; ++range) {
		for(int start_pos=0; start_pos+range < s_size; ++start_pos) {
			int end_pos = start_pos+range;
			if(s[start_pos] == s[end_pos] && dp[start_pos+1][end_pos-1]) {
				dp[start_pos][end_pos] = true;
			}
		}
	}
}

void solve() {
	answer[0] = 1;
	for(int end_pos = 1; end_pos<s_size; ++end_pos) {
		answer[end_pos] = INF;

		for(int start_pos=0; start_pos<=end_pos; ++start_pos) {
			if(dp[start_pos][end_pos]) {
				answer[end_pos] = min(answer[end_pos], answer[start_pos-1]+1);
			}
		}
	}
}

int main() {
	palindrome();
	solve();
	cout << answer[s_size-1];
	return 0;
}
