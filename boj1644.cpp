#include <bits/stdc++.h>
#define MAX_SIZE 4000001
using namespace std;

/*
  https://www.acmicpc.net/problem/1644
  소수의 연속합
  에라토스테네스의 체, 누적합, 투포인터
  ---
  1. 에라토스테네스의 체를 이용해 소수인지 아닌지 여부를 판별한다.
  2. 주어진 수 N까지의 연속된 소수 배열을 만든다.
  3. 연속된 소수의 누적합 배열을 만든다.
  4. 이분 탐색을 통해 주어진 N보다 크거나 같은 index를 구한다.
  5. 투포인터를 활용하여 누적합 배열을 탐색하며, 주어진 구간합이 N이 되는지 여부를 판단한다. 
  
*/

long long sum[MAX_SIZE];
int N;
bool is_prime[MAX_SIZE];
vector<int> prime_nums;

void make_prime_nums() {
	memset(is_prime, true, sizeof(is_prime));
	is_prime[0] = is_prime[1] = false;

	for (int i = 2; i*i <= N; ++i) {
		if (!is_prime[i]) continue;
		for (int j = i+i; j <= N; j+=i) {
			is_prime[j] = false;
		}
	}

	for (int i = 2; i <= N; ++i) {
		if (is_prime[i]) prime_nums.push_back(i);
	}
}

int main() {
	cin >> N;
	if (N == 1) {
		cout << "0";
		return 0;
	}

	make_prime_nums();
	int len = prime_nums.size();
	sum[0] = prime_nums[0];

	for (int i = 1; i < len; ++i) {
		sum[i] = sum[i - 1] + prime_nums[i];
	}

	int left = 0, right = lower_bound(sum, sum + len, N) - sum;
	int answer = (right != len) && (sum[right] == N) ? 1 : 0;

	while (left < right && right < len) {
		long long current_sum = sum[right] - sum[left];

		if (current_sum > N) {
			left++;
		} else if (current_sum < N) {
			right++;
		} else {
			++answer;
			left++, right++;
		}
	}

	cout << answer;
	return 0;
}
