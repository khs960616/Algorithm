#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/92344
  2022 KAKAO BLIND RECRUITMENT
  파괴되지 않은 건물
  --- 
  풀이 참고함 : https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/#%EB%AC%B8%EC%A0%9C-6-%ED%8C%8C%EA%B4%B4%EB%90%98%EC%A7%80-%EC%95%8A%EC%9D%80-%EA%B1%B4%EB%AC%BC
  다시 풀어볼 것..
   
  누적 합을 구하는 효율적인 방식에 대해 새로 알게됨.
  처음에 비트마스킹, 해쉬 등으로 접근해보려했는데 손도 못댐.. 
  
  아이디어는 skills가 일으키는 변화에 대해 매번 (r2-r1) *(c2-c1) 만큼 의 배열에 대해 연산을 진행하는 것이 아닌,
  2차원 누적합을 구하기 위해
  (r1, c1), (r2+1, c1)
  (r1, c2+1) (r2+1, c2+1) 4가지 값만 저장해두었다가 한번에 일괄적으로 개산하는 것임 
*/
int n = 0, m = 0;

int get_degree(int type, int degree) {
    return (type == 1) ? -degree : degree;
}

void add_pre_fix(vector<vector<int> >& ret, vector<vector<int>> skills) {
    for(vector<int> skill: skills) {
        int r1 = skill[1], c1 = skill[2];
        int r2 = skill[3], c2 = skill[4];
        int degree = get_degree(skill[0], skill[5]);
        ret[r1][c1] += degree;
        ret[r1][c2+1] -= degree;
        ret[r2+1][c1] -= degree;
        ret[r2+1][c2+1] += degree;
    }
}

void calc_pre_fix_row(vector<vector<int> >& ret) {
    for(int i=1; i<=n; ++i) {
        for(int j=0; j<=m; ++j) {
            ret[i][j] += ret[i-1][j];
        }
    }
}

void calc_pre_fix_column(vector<vector<int> >& ret) {
    for(int i=1; i<=m; ++i) {
        for(int j=0; j<=n; ++j) {
            ret[j][i] += ret[j][i-1];
        }
    }
}

vector<vector<int>> make_sum_window(vector<vector<int>> skills) {
    vector<vector<int> > ret(n+1, vector<int>(m+1, 0));
    add_pre_fix(ret, skills);
    calc_pre_fix_row(ret);
    calc_pre_fix_column(ret);
    return ret;
}

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    n = board.size();
    m = board[0].size();
    vector<vector<int>> pre_fix_sum = make_sum_window(skill);
    
    int answer = 0;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            if(board[i][j] + pre_fix_sum[i][j] > 0) answer++;
        }
    }
    return answer;
}
