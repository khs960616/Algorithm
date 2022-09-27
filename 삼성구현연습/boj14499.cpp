#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/14499
  주사위 굴리기
  ---
  주사위 굴리는 상태를 시뮬레이션하여 구현
*/
int n = 0, m = 0, x = 0, y = 0, k = 0;

vector<int> dice_value = {0, 0, 0, 0, 0, 0};
vector<int> dice_info = {1, 6, 3, 4, 5, 2};
vector<pair<int, int> > dirs = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

bool is_valid(int x, int y) {
    return y>=0 && y<m && x>=0 && x<n;
}

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void rotate_dice(int op) {
    switch (op) {
    case 1:
        swap(dice_info[0], dice_info[3]);
        swap(dice_info[1], dice_info[2]);  
        swap(dice_info[2], dice_info[3]); 
        break;
    case 2:
        swap(dice_info[0], dice_info[2]);
        swap(dice_info[1], dice_info[3]);
        swap(dice_info[2], dice_info[3]);
        break;
    case 3:
        swap(dice_info[0], dice_info[4]);     
        swap(dice_info[1], dice_info[5]); 
        swap(dice_info[4], dice_info[5]); 
        break;
    case 4:
        swap(dice_info[0], dice_info[5]);  
        swap(dice_info[1], dice_info[4]);  
        swap(dice_info[4], dice_info[5]);
        break;
    }
}

int main() {
    cin >> n >> m >> x >> y >> k;

    vector<vector<int> > mp(n, vector<int>(m, 0));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin >> mp[i][j];
        }
    }

    for(int i=0; i<k; ++i) {
        int op;
        cin >> op;

        int next_x = x + dirs[op-1].first;
        int next_y = y + dirs[op-1].second;
        if(!is_valid(next_x, next_y)) continue;

        rotate_dice(op);
        x = next_x;
        y = next_y;
        if(mp[x][y] == 0) {
            mp[x][y] = dice_value[dice_info[1]-1];
        } else {
            dice_value[dice_info[1]-1] = mp[x][y];
            mp[x][y] = 0;
        }

        cout << dice_value[dice_info[0]-1] << '\n';
    }
}


/* 
다른 사람 풀이 -> 마주보는 두 면의 합이 언제나 7임을 이용하여 구현한 방식.. 주사위 시뮬레이션하는 방식은 이 방식으로 작성하는게 좀 더 간결하고, 이해하기 쉬운듯. 연산 자체도 더 적음

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <algorithm>
#include <queue>
#include <numeric>
using namespace std;

int arr[20][20];
int dy[5] = { 0,0,0,-1,1 };
int dx[5] = { 0,1,-1,0,0 };
int dice[7] = { 0,0,0,0,0,0,0 };
int front = 5;
int top = 1;
int east = 3;
// 두개 합은 무조건 7

void move(int dir)
{
	switch (dir)
	{
	case 1: // 동쪽
		swap(top, east);
		east = 7 - east;
		break;
	case 2: // 서쪽
		swap(top, east);
		top = 7 - top;
		break;
	case 3: // 북쪽
		swap(top, front);
		top = 7 - top;
		break;
	case 4: // 남쪽
		swap(top, front);
		front = 7 - front;
		break;
	}
}
int main(void)
{
	int N, M, x, y, K;
	cin >> N >> M >> y >> x >> K;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> arr[i][j];

	while (K--)
	{
		int dir;
		cin >> dir;

		if (y + dy[dir] < 0 || x + dx[dir] < 0 || y + dy[dir] > N - 1 || x + dx[dir] > M - 1)
			continue;

		y += dy[dir];
		x += dx[dir];
		move(dir);
		if (arr[y][x] == 0) 
			arr[y][x] = dice[7 - top];
		else
		{
			dice[7 - top] = arr[y][x];
			arr[y][x] = 0;
		}

		cout << dice[top] << endl;
	}
}


*/
