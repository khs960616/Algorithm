#include<iostream>
using namespace std;

/*
  1. 만일 물건을 분할해서 넣을수 있다면 그리디 알고리즘으로 해결한다. (무게대비 가격이 높은것 위주로 먼저 넣도록)
  2. 만일 물건을 분할해서 넣을 수 없다면 DP를 활용한다. 
  ---
  sol)
  dp[i][j] -> 1~i번째 물건까지 존재하고 가방의 무게 제한이 j일때의 최대값
  i번째 물건을 현재 넣을 수 없다면, dp[i][j] = d[i-1][j]
  i번째 물건을 넣을 수 있다면, (d[i-1][j-현재물건무게]+현재물건의 값어치) 와 dp[i-1][j] 의 대소를 비교하여 더 큰쪽으로 값을 가지도록 한다. 
*/
int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;
    
	for(test_case = 1; test_case <= T; ++test_case) {
		int N, K;
        int products[101][2];
		int dp[101][1001];
        cin >> N  >> K;
        for(int i=1; i<=N; ++i) cin >> products[i][0] >> products[i][1];
        
        for(int i=0; i<=N; ++i) {
        	for(int j=0; j<=K; ++j) {
            	dp[i][j] = 0;
            }
        }
        
        for(int i=1; i<=N; ++i) {
            int volume = products[i][0];
            int price = products[i][1];
            
        	for(int j=1; j<=K; ++j) {
            	if(j < volume) {
                    dp[i][j] = dp[i-1][j];
                    continue;
                }
                
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-volume]+price);
            }
        }
        cout << '#' << test_case << ' ' << dp[N][K] << '\n';
	}
	return 0;
}
