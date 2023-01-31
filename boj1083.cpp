#include <bits/stdc++.h>

using namespace std;

int arr[50];

/*
  https://www.acmicpc.net/problem/1083
  소트
  ---
  1. 현재 인덱스를 기준으로 현재인덱스+s 까지의 원소를 탐색하며 최대 원소를 찾는다.
     1-1) 만일 현재 인덱스가 가장 크다면 해당 index는 이미 사전순으로 가장 뒤에 오도록 정렬이 완료된 상태이므로 다음 index로 넘어가서 확인한다.
     1-2) 만일 최대원소의 인덱스가 현재 검색중인 index보다 크다면, 현재 검색 중인 인덱스까지 오도록 원소를 swap해준다.
          (1번에서 탐색 범위를 현재 인덱스 ~ 현재인덱스+s 이내의 범위만 탐색하므로, 만일 1-2) 조건에 오는 경우 항상 현재 index까지 swap이 가능함이 보장된다.)
 
  2. 만일 원소를 바꿀수 있는 횟수 s가 0이 아니고 배열의 전체 원소를 한번씩 순회한 것이 아니라면 1번의 과정을 반복한다. 
*/
int main() {
	int n, s;
	cin >> n;
	for(int i=0; i<n; ++i) cin >> arr[i];
	cin >> s;

	for(int i=0; i<n && s>0; ++i) {
		int range = min(i+s+1, n);
		int max_idx = max_element(arr+i, arr+range)-arr;
		if(max_idx <= i) continue;

		for(int j=max_idx; j>i; --j) {
			swap(arr[j], arr[j-1]);
			if(--s == 0) break;
		}
	}

	for(int i=0; i<n; ++i) cout << arr[i] << ' ';
	return 0;
}


/*
초기 실패한 코드.
테스트케이스만 보고 앞에서부터 순차적으로 큰 원소가 오도록 바꾸면 정렬이 된다고 생각했는데,
모든 원소를 정렬하는 것이 아닌 사전순으로 가장 뒤에 오도록 정렬하는 것이므로 답이 성립하지 않았다. 

반례) 다음과 같은 케이스에서 최적해가 나올 수 없다.


1 2 3 4 5 6        s = 3
2 1 3 4 5 6    (s = 2)
2 3 1 4 5 6    (s = 1)

코드상의 결과 : 3 2 1 4 5 6    (s = 0)     
answer : 4 1 2 3 5 6  

#include <bits/stdc++.h>

using namespace std;

int arr[50];

int main() {
	int n, s;
	cin >> n;
	for(int i=0; i<n; ++i) cin >> arr[i];
	cin >> s;

	while(s--) {
		for(int i=1; i<n; ++i) {
			if(arr[i-1] < arr[i]) {
				swap(arr[i-1], arr[i]);
				break;
			}
		}
	}

	for(int i=0; i<n; ++i) cout << arr[i] << ' ';
	return 0;
}
*/
