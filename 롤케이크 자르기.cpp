#include <bits/stdc++.h>
using namespace std;

int topping_cnts[10001];

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/132265
  롤케이크 자르기
  구현, set
*/
int solution(vector<int> topping) {
    int answer = 0;
    int t_size = topping.size();
    int topping_type = 0;
    
    for(int i=0; i<t_size; ++i) {
        if(topping_cnts[topping[i]] == 0) topping_type++;
        topping_cnts[topping[i]]+=1;
    }
    
    set<int> s;
    for(int i=0; i<t_size; ++i) {
        s.insert(topping[i]);
        topping_cnts[topping[i]] -= 1;

        if(topping_cnts[topping[i]] == 0) topping_type--;
        if(s.size() == topping_type) answer++;
        if(s.size() > topping_type) break;
    }
    
    return answer;
}
