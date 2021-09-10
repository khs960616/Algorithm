//프로그래머스 - 올바른 괄호
//stack 
#include<string>
#include<stack>
using namespace std;

bool solution(string s)
{
    if(s[0] == ')') return false;
    
    stack<char> c;
    int ssize = s.size();
    for(int i=0;i<ssize;i++){
        if(s[i] == '('){
            c.push(s[i]);
        }else{
            if(c.empty()) return false;
            c.pop();
        }
    }
    return c.empty();
}
