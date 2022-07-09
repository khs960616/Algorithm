#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/76502
  괄호 회전하기
  ---------
  stack 
*/
bool isValid(string s, int startIdx, int length) {
    stack<char> st;

    for(int i=startIdx; i<length+startIdx; ++i) {
        int currentIdx = i % length;
        
        if(s[currentIdx] == '(' || s[currentIdx] == '[' || s[currentIdx] == '{') {
            st.push(s[currentIdx]);
            continue;
        }
        
        if(st.empty()) return false;
        
        switch(s[currentIdx]) {
            case ')':
                if(st.top() != '(') return false;
                break;
            case ']':
                if(st.top() != '[') return false;
                break;
            case '}':
                if(st.top() != '{') return false;
                break;
        }
        st.pop();
    }
    return st.empty();         
}

int solution(string s) {
    int answer = 0;
    int sSize = s.size();
    
    for(int i=0; i<sSize; ++i) {
        if(isValid(s, i, sSize)) ++answer;
    }
    return answer;
}
