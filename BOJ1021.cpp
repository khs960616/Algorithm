#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <deque>

using namespace std;

int main() {
	int N, M;
	int answer = 0;
	cin >> N >> M;
	
	deque<int> location(M, 0);
	deque<int> index(N, 0);

	for (int i = 0; i < M; i++) cin >> location[i];
	for (int i = 0; i < N; i++) index[i] = (i + 1);

	for (int i = 0; i < M; i++) {
		int target = location[i];
		int left = 0, right = 0;
		if (target == index.front()) {
			index.pop_front();
			continue;
		}
		for (int j = 1; j < index.size(); j++) {
			if (target != index[j]) continue;
			right = j;
			break;
		}
		left = index.size() - right;

		if (left > right) {
			answer += right;
			while ((right--) != 0) {
				int temp = index.front();
				index.pop_front();
				index.push_back(temp);
				
			}
		}
		else {
			answer += left;
			while ((left--) != 0) {
				int temp = index.back();
				index.pop_back();
				index.push_front(temp);
			}
		}
		index.pop_front();
	}
	cout << answer;
	return 0;
}
