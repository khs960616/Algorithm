#include <bits/stdc++.h>
#define MAX_SIZE 2000
using namespace std;

/*
  https://www.acmicpc.net/problem/10942
  팰린드롬?
  ---
  DP
*/

int arr[MAX_SIZE];
bool is_valid[MAX_SIZE][MAX_SIZE];

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for(int i=0; i<n; ++i) cin >> arr[i];

	for(int i=0; i<n; ++i) {
		is_valid[i][i] = true;
		if(i!=n-1) {
			if(arr[i] == arr[i+1]) {
				is_valid[i][i+1] = true;
			}
		}
	}

	for(int range=2; range<n; ++range) {
		for(int start_idx = 0; start_idx+range<n; ++start_idx) {
			if(is_valid[start_idx+1][start_idx+range-1] && arr[start_idx] == arr[start_idx+range]) {
				is_valid[start_idx][start_idx+range] = true;
			}
		}
	}

	int m;
	cin >> m;
	for(int i=0; i<m; ++i) {
		int from, to;
		cin >> from >> to;
		if(is_valid[from-1][to-1]) cout << 1 << '\n';
		else cout << 0 << '\n';
	}

	return 0;
}

/*
  오답  코드
  String으로 회문 처리하라는 건줄 알고 고민했는데, 2000^2에, 각 요소의 크기가 최대 100,000 이므로 string에 관한 연산도 6자리안에 끝나므로 다음과 같이 시도했었는데..
  회문 판별이 아니라 그냥 숫자로 하면 되는 문제였음 
  
#include <bits/stdc++.h>
#define MAX_SIZE 2000
using namespace std;

int arr[MAX_SIZE];
bool is_valid[MAX_SIZE][MAX_SIZE];

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for(int i=0; i<n; ++i) cin >> arr[i];

	for(int i=0; i<n; ++i) {
		string num, reverse_num;
		num = reverse_num =  to_string(arr[i]);
		reverse(reverse_num.begin(), reverse_num.end());

		if(num == reverse_num) {
			is_valid[i][i] = true;
		}
		if(i!=n-1) {
			num+=to_string(arr[i+1]);
			reverse_num = num;
			reverse(reverse_num.begin(), reverse_num.end());
			if(num == reverse_num) {
				is_valid[i][i+1] = true;
			}
		}
	}

	for(int range=2; range<n; ++range) {
		for(int start_idx = 0; start_idx+range<n; ++start_idx) {
			string prefix = to_string(arr[start_idx]);
			string suffix = to_string(arr[start_idx+range]);
			reverse(suffix.begin(), suffix.end());

			if(is_valid[start_idx+1][start_idx+range-1] && prefix == suffix) {
				is_valid[start_idx][start_idx+range] = true;
			}
		}
	}

	int m;
	cin >> m;
	for(int i=0; i<m; ++i) {
		int from, to;
		cin >> from >> to;
		if(is_valid[from-1][to-1]) cout << 1 << '\n';
		else cout << 0 << '\n';
	}

	return 0;
}


*/
