#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/17687#
2018 KAKAO BLIND RECRUITMENT
[3차]n진수
---
문자열 
진수 변환
구현 
*/
string convertNum(int n, int num) {
    if(num == 0) return "0";
    
    string s = "";
    while(num != 0) {
        int r = num%n;
        string remain = "";
        
        if(r<10) {
            remain = to_string(r);
        } else {
            char c = r+55;
            remain += c;
        }
        
        s = remain + s;
        num/=n;
    }
    return s;
}

string solution(int n, int t, int m, int p) {
    string answer = "";
    int number = 0;
    int turn = p;
    
    while(answer.size() != t) {
        string s = convertNum(n, number);
        if(turn<=0) turn+=m;
        
        if(s.size() >= turn) answer+=s[turn-1];
        
        turn-=s.size();
        ++number;
    }
    
    return answer;
}
