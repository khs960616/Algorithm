#include <bits/stdc++.h>

/*
  https://www.acmicpc.net/problem/2473
  세 용액
  투포인터
  ---
  1. 각 용액을 오름차순으로 정렬한다.
  2. 시작점을 pivot점으로 잡고 mid, end 값을 투포인터를 사용해서 구간을 줄여나간다.
     시작점을 고정했을 때, 만일 세 용액의 합이 음수이면 mid값을 키워서 0에 가깝게 해줘야하며, 양수인 경우 end 값을 줄여서 0에 가깝게 유도한다.
     구간을 줄여나가며 최적해를 찾는다.
  
  n은 최대 5000이므로, 투포인터를 활용하면 n^2 스케일에 문제를 해결할 수 있다.
*/
using namespace std;

vector<long> v;
int answer[3];
int n;

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	cin >> n;
	v = vector<long>(n);
	for (int i = 0; i < n; ++i) cin >> v[i];
	sort(v.begin(), v.end());

	long opt_value = LONG_MAX;

	for (int start = 0; start < n - 2; ++start) {
		int mid = start + 1, end = n - 1;

		while (mid < end) {
			long value = v[start] + v[mid] + v[end];
			long abs_value = std::abs(value);

			if (opt_value > abs_value) {
				answer[0] = v[start];
				answer[1] = v[mid];
				answer[2] = v[end];
				opt_value = abs_value;
			}

			if (value < 0) mid++;
			else end--;
		}
	}

	cout << answer[0] << ' ' << answer[1] << ' ' << answer[2];
	return 0;
}
