#include <bits/stdc++.h>

using namespace std; 

/*
  https://www.acmicpc.net/problem/14890
  경사로
  구현 
  ---
  solve)
  1. 경사로는, 길이가 L이며 높이가 1인 구조물이다. 
     
     ex) L=2 일 때, 
     3 2 2 2 2 형태의 길이 존재한다면, 1번째 index의 위치부터 시작해서 2번째 index까지 길이가 2인 내리막 경사로를 설치하면 이동이 가능한 형태가 된다. 
     2 2 3 3 3 형태의 길이 존재한다면, 1번째 index의 위치부터 시작해서 0번째 index까지 길이가 2인 오르막 경사로를 설치하면 이동이 가능한 형태가 된다. 
     
     위각 길을 확인할 떄 index값을 순차적으로 증가시키며 검사하고, 만일 이전노드와 높이 차이가 1이 나면 현재 위치부터, +L의 위치까지 경사로를 설치할 수 있어야 하는지 확인해아하며,
     이전 노드와 높이 차이가 -1이라면, (현재위치-1) 의 위치에서 -L의 위치까지 경사로를 설치할 수 있는지 여부를 확인해야한다.
     (경사로를 설치할 수 있다는 뜻은 -> 경사로 설치의 시작점부터 끝점까지 모든 값이 같고, 해당 위치에 다른 경사로가 설치되지 않은 상태임을 의미한다.)
  
  2. 1번의 경사로에 대한 정의를 확인한다.
     (경사로를 설치해서 끝까지 이동이 가능하거나)
     (처음부터 모든 길의 값이 같아 이동이 가능한 경우)  
     각 행과 열에 대해서 다음의 조건을 확인하면 답을 구할수 있다.
  ---
  
  최초 풀이 이후 고민한 점
  (ramp_row, ramp_col)와  (can_pass_row, can_pass_col) 중복이 상당히 많음.
  코테 볼때 항상 2차원 grid에 대한 구현 문제를 마주치면 이런 중복을 어떻게 제거할까 고민하게됨.
  
  고민한 처리 방법
  1. 데이터를 입력받은 이후 각 데이터를 전처리하는 과정을 추가하고 로직을 하나로 합친다.
  
    ex)   
        3 3 3 3 3 3
        2 3 3 3 3 3
        2 2 2 3 2 3
        1 1 1 2 2 2
        1 1 1 3 3 1
        1 1 2 3 3 2     
        
        형태의 grid가 주어질때, 데이터를 전처리 한다. 
        (1) 각 행에 대한 배열 {333333,  233333, 222323 ... },
        (2) 각 열에 대한 배열 {322111,  332111, 332112 ... }    에 대해서, 두 배열을 합친 길의 정보를 담은 배열을 추가적으로 저장한다.
        
  >> 일단은 해당 문제에서는 input size가 상당히 작으므로, 해당 전처리하는 부분을 추가하는 것이, 유지보수하기 좋은 코드라 생각한다. 
        
  2. 기존 함수에 parameter로 is_row등의 boolean parameter로 받아서 분기 처리
     >> 해당 방식으로 리팩토링 해봤는데 차라리, 기존 형태가 나은 듯 하다고 느꼈다. 
     
     코드의 줄 수는 줄어들었지만 각 로직별로 삼항연산자 또는 if문 형태로 처리하는 경우가 많아 가독성이 크게 떨어졌고, 중복도 제거되었다고 느껴지지 않았다.
  
  차후 다른 방식이 있다면 더 고민해보자..
*/

int N, L;
int paths[100][100];
bool is_used[100];

bool is_valid(int x) {
	return x>=0 && x<N;
}

bool is_ramp_row(int row, int col, int dir) {
	if(dir == -1) col-=1;

	int len = L;
	int base = paths[row][col];
	while(len--) {
		if(!is_valid(col) || is_used[col] || paths[row][col] != base) return false;
		col += dir;
	}

	len = L;
	while(len--) {
		col-=dir;
		is_used[col] = true;
	}
	return true;
}

bool is_ramp_col(int row, int col, int dir) {
	if(dir == -1) row-=1;

	int len = L;
	int base = paths[row][col];
	while(len--) {
		if(!is_valid(row) || is_used[row] || paths[row][col] != base) return false;
		row += dir;
	}

	len = L;
	while(len--) {
		row-=dir;
		is_used[row] = true;
	}
	return true;
}

bool can_pass_row(int x) {
	int prev = paths[x][0];
	memset(is_used, false, sizeof(is_used));

	for(int i=1; i<N; ++i) {
		if(prev == paths[x][i]) continue;
		
		int diff = prev-paths[x][i];
		if(diff > 1) return false;
		if(!is_ramp_row(x, i, diff)) return false;
		prev = paths[x][i];
	}
	return true;
}

bool can_pass_col(int x) {
	int prev = paths[0][x];
	memset(is_used, false, sizeof(is_used));

	for(int i=1; i<N; ++i) {
		if(prev == paths[i][x]) continue;
		
		int diff = prev-paths[i][x];
		if(diff > 1) return false;
		if(!is_ramp_col(i, x, diff)) return false;
		prev = paths[i][x];
	}
	return true;
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);

	int answer = 0;
	cin >> N >> L;
	for(int i=0; i<N; ++i) {
		for(int j=0; j<N; ++j) {
			cin >> paths[i][j];
		}
	}

	for(int i=0; i<N; ++i) {
		if(can_pass_row(i)) answer++;
		if(can_pass_col(i)) answer++;
	}
	cout << answer << '\n';
	return 0;
}
