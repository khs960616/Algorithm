#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/2143
  두 배열의 합
  --- 
  누적합과 이분탐색 
  
  부배열의 정의 : 주어진 집합, a, b에 대하여, 연속된 원소들로만 이루어진 부분집합 (공집합 제외)
  배열 a와 배열 b의 부배열들의 합으로 t가 나오는 경우의 수를 구하는 문제이다. 
  배열의 사이즈는 최대 1000개이므로 부배열은 최대 1000^2 (10^6)만큼 존재할 수 있다. 
  
  ---
  solve)
  1. 주어진 배열 a, b에 대한 모든 부배열을 각각 구한다.
  2. 탐색의 기준이 될 배열을 정렬한다. (이 때 정렬된 배열을 target, 정렬되지 않은 배열을 d라고 하자)
  3. d의 모든 원소에 대해서 (t - d)의 원소값을 target 배열에 몇개 존재하는지 센다.
     
     lower_bound는 이상의 개념, upper_bound는 초과의 개념이므로 두 가지 함수의 결과값의 차이를 이용하면, 해당 원소가 몇개 존재하는지 알 수 있다.
  
*/
vector<long long> get_cumulative_sum(long long* target, int len) {
	vector<long long> ret;
	for(int i=0; i<len; ++i) {
		long long num = 0;
		for(int j=i; j<len; ++j) {
			num += target[j];
			ret.push_back(num);
		}
 	}
	return ret;
}

int main() {
	long long a[1000], b[1000];
	int t, a_len, b_len;
	cin >> t >> a_len;
	for(int i=0; i<a_len; ++i) {
		cin >> a[i];
	}
	cin >> b_len;
	for(int i=0; i<b_len; ++i) {
		cin >> b[i];
	}

	vector<long long> a_sum = get_cumulative_sum(a, a_len);
	vector<long long> b_sum = get_cumulative_sum(b, b_len);
	sort(b_sum.begin(), b_sum.end());

	int len = a_sum.size();
	long long answer = 0;
	for(int i=0; i<len; ++i) {
		long long value = t-a_sum[i];
		long long cnt = upper_bound(b_sum.begin(), b_sum.end(), value) - lower_bound(b_sum.begin(), b_sum.end(), value);
		answer += cnt;
	}
	cout << answer;
	return 0;
}
