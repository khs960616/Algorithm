#include <iostream>
#include <algorithm>
#define NUMBER_OF_LAN 10000
using namespace std;

/*
https://www.acmicpc.net/problem/1654
랜선 자르기
---
이분탐색 
*/
long long max_length = -1;
long long length[10000];

int countLan(long long midValue, int k);
void binarySearch(int n, int k);

int main() {
	int k = 0, n = 0;
	cin >> k >> n;

	for (int i = 0; i < k; i++) {
		long long temp = 0;
		cin >> temp;
		length[i] = temp;
		if (temp > max_length) max_length = temp;
	}

	binarySearch(n, k);
}

int countLan(long long midValue, int k) {
	int cnt=0;
	for (int i = 0; i < k; i++) cnt = cnt+(int)(length[i] / midValue);
	return cnt;
}

void binarySearch(int n, int k) {
	long long begin = 1, cnt = 0, result = 0, mid=0;
	while (begin<=max_length) {
		mid = (begin + max_length) / 2;
		cnt = countLan(mid, k);
	
		if (cnt >= n) {
			result = mid;
			begin = mid + 1;
		}
		else max_length = mid-1;
	}
	cout << result;
}
