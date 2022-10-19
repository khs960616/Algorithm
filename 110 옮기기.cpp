#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/77886
  110 옮기기
  스택 
  ---
  1. 문자열에 어느 위치에 110이라는 토큰이 들어갈 수 있는 지 정의해야한다.
     1-1) 우선 문자열 내부에 "11" 과 같이 연속된 1이 두번 반복되는지 먼저 확인한다. 
     사전에서 우선순위가 낮은 문자열을 만들기 위해서는
     11(110) > (110)(11) 이므로 (110)이라는 토큰은 어떤 경우라도 11이라는 패턴 뒤에 와야한다.
     
     1-2) 다음으로 문자열에 뒤에서 부터 0이 존재하는지 확인한다.
          0(110) < 110(0) 이므로   110이라는 토큰은  1-1)의 경우를 제외하고는 0뒤에 와야한다.
          
     1-3) 문자열이 모두 1인 경우에는 해당 문자열 앞에 (110)이라는 토큰이 오면 된다.
     
     >> "110" 이라는 패턴이 여러개 존재하는 경우, 110이라는 개별 토큰을 매번 어디 넣을지 정하는 것이 아닌,
     해당 토큰을 모두 더한 (110110110...) 형태의 하나의 토큰을 위 규칙에 맞게 넣으면 된다.
     그 이유는 110 이라는 토큰 자체가 1-1)에 존재하는 11이라는 가장 우선순위가 높은 패턴을 가지고 있기 때문이다.
     
     
  2. 문자열에 존재하는 110이라는 패턴을 모두 분리해내야한다.
     ex)   011110000  형태이면,   011110000 -> 011000   (110)  -> 000   (110) (110) 다음의 형태로 모두 분리되야한다.
     
     stack 개념을 활용한다.
     
     문자열의 현재 인덱스에 해당하는 문자가 1이라면 stack에 1을 집어넣는다. 
     문자열의 현재 인덱스에 해당하는 문자가 0이라면 stack에 현재 1이 몇개 남았는지 확인한다.
     
     만약 1이 2개 이상 존재한다면 stack에서 1을 두개 제거하고,  110이라는 패턴을 1개 추가시킨다.
     만약 1이 2개 미만 존재한다면, 현재 스택에 존재하는 1들은 어떠한 경우에도 110이라는 패턴을 완성시킬수 없기 때문에, 스택에서 제거하고 원래 문자열에 추가한다.
     
 3. 2에서 분리한 110 토큰 집합을 1의 규칙에 맞게 적절한 위치에 삽입한다. 
 
 ---
 
 
*/
void add_1(string& s, int cnt) {
    if(cnt == 0) return;
    while(cnt--) s += "1";
}

pair<string, string> check(string num) {
    int len = num.size();
    int cnt = 0;
    string ret = "";
    string s = "";
    
    for(int i=0; i<len; ++i) {
        if(num[i] == '1') ++cnt;
        else {
            if(cnt < 2) {
                add_1(ret, cnt);
                cnt = 0;
                ret += "0";
            } else {
                s+="110";
                cnt-=2;
            }
        }
    }
    
    add_1(ret, cnt);
    return {ret, s};
}

string make_answer(string remain, string token) {
    int idx = remain.find("11");
    if(idx != string::npos) {
        remain.insert(idx, token);
        return remain;
    }
    
    idx = remain.rfind("0");
    if(idx != string::npos) {
        remain.insert(idx+1, token);
        return remain;
    }
    
    return token+remain;
}

vector<string> solution(vector<string> nums) {
    vector<string> answer;
    for(string& num: nums) {
        pair<string, string> p = check(num);
        string s = make_answer(p.first, p.second);
        answer.push_back(s);
    }
    return answer;
}
