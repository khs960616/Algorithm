#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAX_BLOCK 500
#define TASK_1_TIME 2
#define TASK_2_TIME 1

using namespace std;

int n, m, b;
int min_height=260, max_height=-1;
int ground[MAX_BLOCK][MAX_BLOCK];

struct Answer {
	int time;
	int height;
};

void init() {
	cin >> n >> m >> b;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> ground[i][j];
			if (ground[i][j] < min_height) min_height = ground[i][j];
			if (ground[i][j] > max_height) max_height = ground[i][j];
		}
	}
}

void solution() {
	Answer a = {99999999,0};

	for (int i = min_height; i <= max_height; i++){
		int task1 = 0, task2 = 0;
		
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				if (ground[j][k] < i) {
					task2 += (i-ground[j][k]);
				}
				else if (ground[j][k] > i) {
					task1 += (ground[j][k]-i);
				}
			}
		}
		if ((b + task1) < task2) continue;

		int current_time = (task1 * TASK_1_TIME) + (task2 * TASK_2_TIME);

		if (a.time >= current_time) {
			a.time = current_time;
			a.height = i;
		}
	}
	
	cout << a.time << ' ' << a.height;
}

int main() {
	init();
	solution();
	return 0;
}
