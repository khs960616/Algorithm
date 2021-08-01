// 스택 
// 문제 자체에 구현 방법이 다 써있어서, 해당 방식 대로 재귀함수를 사용하면 쉽게 풀수 있었다.

#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

bool isValid(string p){
    int sz = p.size();
    stack<char> s;
    for(int i=0; i< sz; i++){
        if(p[i] == '(') s.push(p[i]);
        else{
            if(s.empty() || s.top() == ')') return false;
            s.pop();
        }
    }
    return s.empty();
}

string to_inverse(string p){
    int sz = p.size();
    if(p == "" || sz == 2) return "";
    string result = "";
    string tmp = p.substr(1, sz-2);
    int tsz = tmp.size();
    
    for(int i=0; i<tsz;i++){
        if(tmp[i] == '(') result += ')';
        else result += '(';
    }
    return result;
}

string test(string p){
    string result = "";
    int str_size = p.size();
    if(p.size() == 0) return "";
    
    int left = 0, right = 0;
    int sub_idx = 0;
    
    for(int i = 0; i < p.size(); i++){
        if(p[i] == '(') left++;
        if(p[i] == ')') right++;
        if(left == right){
            sub_idx = i+1;
            break;
        }
    }
    string u = p.substr(0, sub_idx);
    string v = p.substr(sub_idx);
    
    if(isValid(u)){
        result += u;
        result += test(v);
    } else{
        result += '(';
        result += test(v);
        result += ')';
        result += to_inverse(u);
    }
    
    return result;
}

string solution(string p) {
    string answer = test(p);
    return answer;
}
