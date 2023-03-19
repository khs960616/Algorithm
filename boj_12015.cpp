#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> arr;
vector<int> answer;


/*
  https://www.acmicpc.net/problem/12015
  가장 긴 증가하는 부분수열2
  이분탐색
*/
int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	
	cin >> N;
	for(int i=0; i<N; ++i) {
		int num; 
		cin >> num;
		arr.push_back(num);
	}

	answer.push_back(arr[0]);

	for(int i=1; i<N; ++i) {
		if(answer.back() < arr[i]) answer.push_back(arr[i]);
		else {
			int idx = lower_bound(answer.begin(), answer.end(), arr[i]) - answer.begin();
			answer[idx] = arr[i];
		}
	}
	cout << answer.size();
	return 0;
}
