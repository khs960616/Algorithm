#include <bits/stdc++.h>

using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12904
  가장 긴 팰린드롬 
  --- 
  two pointer approach
  
  1. 문자열의 각 인덱스를 기준으로 
     1-1) 길이가 짝수인 펠린드롬
     1-2) 길이가 홀수인 펠린드롬을 확인한다.
     
  n^2의 시간복잡도를 가진다.
  
  Manacher's Algorithm
  https://doooooooong.tistory.com/41
  
  >> n의 시간복잡도를 가진다. 
*/

int n = 0;
bool is_valid(int idx) {
    return idx>=0 && idx < n;
}

int get_palindrome_length(string s, int left, int right, int init_value) {
    int ret = init_value;
    while(1) {
        if(!is_valid(left) || !is_valid(right)) break;
        if(s[left--] != s[right++]) break;
        ret+=2;
    }
    return ret;
}

int naive_solve(string s) {
    int ret = 1;
    for(int i=0; i<n; ++i) {
        ret = max(ret, get_palindrome_length(s, i-1, i+1, 1));
        ret = max(ret, get_palindrome_length(s, i, i+1, 0));
    }
    return ret;
}

int solution(string s) {
    n = s.length();
    return naive_solve(s);
}
