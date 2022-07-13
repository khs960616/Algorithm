#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12985
  예상 대진표
  ---
  간단 구현 문제 
*/
int solution(int n, int a, int b) {
    int answer = 0;
    while(a!=b) {
        ++answer;
        a = (a / 2) + (a % 2);
        b = (b / 2) + (b % 2);
    };
    return answer;
}
