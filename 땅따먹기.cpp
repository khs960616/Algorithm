/*
#include <iostream>
#include <vector>
#include <algorithm>
#define COLUMN_LENGTH 4
using namespace std;

int answer = 0;
int row_length = 0;

void calc_score(vector<vector<int> > &land, int prev_row, int prev_column, int score){
    if(prev_row == row_length-1){
        if(score > answer) answer = score;
        return;
    }
    
    int current_row = prev_row+1;
    for(int i=0; i < COLUMN_LENGTH; i++){
        if(prev_column == i) continue;
        int added_score = score + land[current_row][i];
        calc_score(land, current_row, i, added_score);
    }
}

int solution(vector<vector<int> > land)
{
    row_length = land.size();
    
    for(int i=0; i < COLUMN_LENGTH; i++){
        calc_score(land, 0, i, land[0][i]);
    }
    return answer;
}

초기 작성한 오답. 
시간복잡도 계산을 잘못했다.
초기 작성한 오답. 시간복잡도 계산을 잘못했다.
column의 길이가 4로 fix 되어있어있고, row의 길이도 100,000으로 비교적 크지 않아, 재귀적으로 브루트포스를 구현하면 되지않을까 생각했다. 
그러나 해당 모든 재귀함수의 호출을 트리로 생각해보면, 각 단계별로 3^n 점점 함수 호출이 거대해진다.. (초기 풀이 방법을 떠올릴 때 반복문만 고려해버림..)
사실 냅섹문제 처럼 바운더리를 구해서 함수 호출수를 줄여서 시간복잡도를 줄이고자 했는데 방법을 생각해내지 못했다.

DP식 풀이를 참고하였다.
일일히 선택하는 관점이 아닌,
이전 행중 자신이 선택할 수 있는 가장 큰값을 선택해서 현재 행에 더한 후,
마지막 행에서 가장 큰 값을 선택하는 방식이다.
시간 복잡도는 n (row_length)와 같다. 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define COLUMN_LENGTH 4
using namespace std;

int solution(vector<vector<int> > land)
{
    int answer = 0;
    int row_length = land.size();
    
    for(int i = 1; i < row_length; i++){
        int prev_index = i-1;
        land[i][0] += max(max(land[prev_index][1], land[prev_index][2]), land[prev_index][3]);
        land[i][1] += max(max(land[prev_index][0], land[prev_index][2]), land[prev_index][3]);
        land[i][2] += max(max(land[prev_index][0], land[prev_index][1]), land[prev_index][3]);
        land[i][3] += max(max(land[prev_index][0], land[prev_index][1]), land[prev_index][2]);
    }
    answer = *max_element(land[row_length-1].begin(), land[row_length-1].end());
    return answer;
}
