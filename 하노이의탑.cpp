#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12946#
  재귀함수 연습
*/
void hanoi(vector<vector<int>>& answer, int remain, int from, int to) {
    if(remain == 1) {
        answer.push_back({from, to});
        return;
    }
    
    int nextPosition = 6-from-to;
    hanoi(answer, remain-1, from, nextPosition);  // 1. n-1개 모양의 하노이탑을 출발점과 도착점 모두 아닌 지점으로 이동 
    answer.push_back({from, to}); //2. 현재 블록중 가장 큰 블록을 본 목적지로 이동 시킴 
    hanoi(answer, remain-1, nextPosition, to); //3. 1에서 이동시킨 n-1 모양의 하노이탑을 실제 목적지로 이동시킴
}

vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;
    hanoi(answer, n, 1, 3);
    return answer;
}
