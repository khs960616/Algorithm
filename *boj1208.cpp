#include <bits/stdc++.h>
using namespace std; 

/*
  https://www.acmicpc.net/problem/1208
  부분수열의 합 2
  ---
  meet in the middle
  
  1. 단순 브루트포스로 문제 접근시 최대 2^40이므로 시간초과 발생
  2. 문제에서 구하고자하는 정답은 "부분 집합의 합이 S가 되는 경우의 수" 이다.  a+b = c -> c-a = b   등식의 성질을 활용한다.
      2-1) 각 집합을 2개로 분할한다. 이 떄 분할된 각 집합을 subset1, subset2라 하자.
      2-2) subset1에 모든 부분집합을 구한 후, 각 부분집합의 합에 대한 경우의 수를 계산한다. (map에 각 부분집합의 합을 count한다.)
      2-3) subset2에 대한 모든 부분집합을 구한 후  
            2-2)에서 구한 map, 2에 나온 등식의 성질을 이용해 mp[S- subset2의 부분집합의합]을 정답에 더해주면 된다.
  
     
  3. 문제 조건에 의해 공집합이 아닌 부분집합만을 포함해야하므로 S=0인 경우 별도 예외 처리를 해줘야한다.
  4. 40 0 {0, 0, 0, .......0} 인 경우 공집합을 제외한 모든 부분집합의 합이 0이므므로 최대 2^40에 가까운 값이 정답이 되므로 데이터 타입은 long long을 선택해야한다. 
*/

int N, S;
int nums[41];
unordered_map<int, int> mp;
void fast_io() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
}

void insert() {
	cin >> N >> S;
	for(int i=0; i<N; ++i) cin >> nums[i];
}

void calc_prev_half(int idx, int value) {
	if(idx == N/2) {
		mp[value]++;
		return;
	}

	calc_prev_half(idx+1, value+nums[idx]);
	calc_prev_half(idx+1, value);
}

/*
  집합을 분할한다는 개념은 같지만, 정답을 구하는 방식은 여러가지가 존재한다.
  
  1. map에 연산의 결과를 저장후 활용하는 방법.
  2. 각 subset의 부분집합의 합을 vector에 저장한 후, 투포인터를 사용해 S가 되는 경우를 count하는 방법
  3. 각 subset의 부분집합의 합을 vector에 저장후, 각각을 오름차순, 내림차순으로 정렬해 이분탐색하는 방법
*/
void inc_answer(long long& answer, int idx, int value) {
	if(idx == N) {
		answer += mp[S-value];    
		return;
	}

	inc_answer(answer, idx+1, value+nums[idx]);
	inc_answer(answer, idx+1, value);
}

int main() {
	fast_io();
	insert();

	long long answer = (S == 0) ? -1 : 0;
	calc_prev_half(0, 0);
	inc_answer(answer, N/2, 0);
	cout << answer;
	return 0;
}
