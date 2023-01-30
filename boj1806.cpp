#include <bits/stdc++.h>
#define MAX_SIZE 100000
using namespace std;

/*
  https://www.acmicpc.net/problem/1806
  부분합
  ---
  부분합 + 이분탐색 + 투포인터 
  
  1. 각 배열의 누적합을 구한다.
  2. s보다 큰 누적합이 있는지 여부를 이분탐색을 통해 검색한다. (배열의 모든 원소가 자연수이므로 별도 sort없어도 누적합 배열은 오름차순으로 정렬되어있다.)
  3. 이분탐색의 결과를 기준으로, 투포인터 알고리즘을 이용해, s보다 크거나 같고, 길이가 더 짧은 부분합이 있는지 검사한다. 
  
*/
int sum[MAX_SIZE];

int main() {
	int n, s, num;
	cin >> n >> s >> num;

	sum[0] = num;
	for (int i = 1; i < n; ++i) {
		cin >> num;
		sum[i] = (sum[i - 1] + num);
	}

	if (sum[n - 1] < s) cout << 0;
	else {
		int left = 0, right = lower_bound(sum, sum + n, s) - sum;
		int current_sum = sum[right];
		int answer = right+1;   // sum[i] 는 0부터 i까지 총 i+1개의 누적합이므로 초기값은 right+1개이다.
		while (left < right && right < n) {
			if (sum[right] - sum[left] >= s) {
				answer = min(answer, right - left);  // right 는 right+1개 원소의 누적합, left는 left+1개의 누적합이므로, sum[right]-sum[left]는 right-left개 원소의 합이다.
				left++;
			}
			else right++;
		}
		cout << answer;
	}
	return 0;
}
