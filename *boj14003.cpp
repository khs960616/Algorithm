#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> dp;
vector<int> arr;
vector<int> answer;


/*
  https://www.acmicpc.net/problem/14003 LIS
  가장 긴 증가하는 부분수열 5
  이분탐색, dp 
  
  --
  1. 단순히 길이를 구할 때는, 주어진 input을 순회하며 가장 큰 원소가 들어오는 경우 answer 배열에 push,
     그렇지 않은 경우 해당 원소보다 큰 원소 중 가장 작은 값을 해당 값으로 교체하는 방식으로 배열의 크기를 갱신해나간다.
     
  2. 1의 과정을 진행하며 각 원소별로 자기 자신을 부분 수열에 포함할 때의 길이를 dp로 저장한다.
  
  3. 가장 긴 부분수열을 만든 index부터 역으로 값을 추적해나가며 LIS 배열을 구한다. 
  
  
*/
int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	
	cin >> N;
	dp = vector<int>(N, 0);

	for(int i=0; i<N; ++i) {
		int num; 
		cin >> num;
		arr.push_back(num);
	}

	answer.push_back(arr[0]);
	dp[0] = 1;

	int max_idx = 0;

	for(int i=1; i<N; ++i) {
		if(answer.back() < arr[i]) {
			answer.push_back(arr[i]);
			dp[i] = answer.size();
			max_idx = i;
		}
		else {
			int idx = lower_bound(answer.begin(), answer.end(), arr[i]) - answer.begin();
			answer[idx] = arr[i];
			dp[i] = idx+1;
		}
	}

	cout << answer.size() << '\n';

	vector<int> lis;
	lis.push_back(arr[max_idx]);
	for(int i=max_idx-1; i>=0; --i) {
		if(dp[i]+1 == dp[max_idx] && arr[i] < arr[max_idx]) {
			lis.push_back(arr[i]);
			max_idx = i;
		}
	}
	
	for(int i=lis.size()-1; i>=0; --i) {
		cout << lis[i] << ' ';
	}

 	return 0;
}
