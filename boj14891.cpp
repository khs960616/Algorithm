#include <bits/stdc++.h>
#define N 0
#define S 1
#define clockwise 1

/*
  https://github.com/khs960616/Algorithm/new/master
  톱니바퀴
  ---
  구현, 재귀 함수 
*/
using namespace std;

string gears[4];

int get_score() {
	int ret = 0;
	for (int i = 0; i < 4; ++i) {
		if ((gears[i][0] - '0') == N) continue;
		ret += pow(2, i);
	}
	return ret;
}

// 매 함수 호출마다 양방향 회전 진행 시 무한루프에 빠질 수 있다. (2번 톱니바퀴 -> 1번 톱니바퀴 호출 -> 2번 톱니바퀴 호출 -> 1번 톱니바퀴 호출 ... 
// 이것을 방지하기 위해 최초 함수 호출 시 process_dir == 2로 현재 톱니바퀴를 기준으로 양뱡향 톱니바퀴가 회전 가능한 조건인지 확인 후 재귀적으로 함수를 호출하고,
// 이후 재귀적으로 호출된 함수들은 단방향으로만 회전을 전파한다. 

void rotate_gears(int current_gear, int rotate_dir, int process_dir) {
	if (current_gear != 0 && gears[current_gear-1][2] != gears[current_gear][6] && process_dir != 1) {
		rotate_gears(current_gear-1, -rotate_dir, 0);
	}

	if (current_gear != 3 && gears[current_gear][2] != gears[current_gear+1][6] && process_dir != 0) {
		rotate_gears(current_gear+1, -rotate_dir, 1);
	}

	int swap_cnt = 8;
	int start_idx = (rotate_dir == clockwise) ? 0 : 7;
	int prev = gears[current_gear][start_idx];
	while (swap_cnt--) {
		int tmp = gears[current_gear][(8 + start_idx + rotate_dir) % 8];
		gears[current_gear][(8 + start_idx + rotate_dir) % 8] = prev;
		prev = tmp;
		start_idx += rotate_dir;
	}
}

int main() {
	for (int i = 0; i < 4; ++i) cin >> gears[i];

	int K;
	cin >> K;
	for (int i = 0; i < K; ++i) {
		int gear_number, dir;
		cin >> gear_number >> dir;
		rotate_gears(gear_number-1, dir, 2);
	}

	cout << get_score();
	return 0;
}
