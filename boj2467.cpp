#include <bits/stdc++.h>

using namespace std;

/*
  https://www.acmicpc.net/problem/2467
  용액
  투포인터
  ---
*/
int answer[2];

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> v(n);
	for(int i=0; i<n; ++i) cin >> v[i];
	sort(v.begin(), v.end());

	int left = 0, right = n-1;
	int currnet_abs = INT_MAX;

	while(left < right) {
		int sum = v[left] + v[right];
		if(abs(sum) < currnet_abs) {
			answer[0] = v[left];
			answer[1] = v[right];
			currnet_abs = abs(sum);
		}
		if(sum < 0) left++;
		else right--;
	}
	cout << answer[0] << ' ' << answer[1];
	return 0;
}
