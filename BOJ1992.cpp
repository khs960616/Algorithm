#include <string>
#include <iostream>

using namespace std;

char video[64][64];
string answer;

void quardTree(int y, int x, int size) {
	if (size == 1) {
		answer += video[y][x];
		return;
	}

	int half = size / 2;
	const int firstValue = video[y][x];

	for (int i = y; i < y + size; i++) {
		for (int j = x; j < x + size; j++) {
			if (video[i][j] != firstValue) {
				answer += '(';
				quardTree(y, x, half);
				quardTree(y, x + half, half);
				quardTree(y + half, x, half);
				quardTree(y + half, x + half, half);
				answer += ')';
				return;
			}
		}
	}

	answer += firstValue;
	return;
}

int main() {
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> video[i][j];
		}
	}

	quardTree(0,0,n);
	cout << answer;
	return 0;
}
