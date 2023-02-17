#include <bits/stdc++.h>

using namespace std;

/*
  https://www.acmicpc.net/problem/2461
  대표선수
  2pointer approach 
  ---
  n, m의 최댓값은 1000이므로 나이브하게 조합을 이용해서 풀면 1000^1000이므로 불가능하다.
  
  (조건1) : 탐색하는 구간 내에 모든 학급의 학생이 적어도 1명 이상 존재 

  1) left ~ right  사이에 (조건1)을 만족하지 않는다면 조건을 만족 할 때 까지 right값을 오른쪽으로 옮긴다.
  2) 정답을 갱신한다. 
  2) left값을 (조건1)이 만족하지 않을때까지 반복하며  (2)를 반복한다.			//결국에 left, right 둘다 n*m만큼 이동하면 종료되기 때문에 복잡도는 10^6안에 끊김
*/

int range_check[1001];
int n=0, m=0, answer = INT_MAX;

bool cmp(pair<int, int> p1, pair<int, int> p2) {
	return p1.second < p2.second;
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	cin >> n >> m;

	vector<pair<int, int> > v; 
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int value = 0; 
			cin >> value;
			v.emplace_back(i, value);
		}
	}
	sort(v.begin(), v.end(), cmp);

	int left = 0, right = 0, flag = n - 1;
	range_check[v[0].first] += 1;

	while (1) {
		while (flag != 0 && right<n*m) {
			right++;
			if (right == n * m) {
				cout << answer;
				return 0;
			}
			if (range_check[v[right].first]++ == 0) flag--;
		}

		while (flag == 0 && left <= right) {
			answer = min(answer, v[right].second - v[left].second);
			if (--range_check[v[left].first] == 0) flag++;
			left++;
		}
	}

	return 0;
}
