#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/120956
  옹알이
  
*/
int solution(vector<string> babblings) {
    int answer = 0;
    regex re("((aya(?!(aya)))?(ye(?!(ye)))?(woo(?!(woo)))?(ma(?!(ma)))?)+");
    
    for(string babbling: babblings) {
        if(regex_match(babbling, re)) {
            cout << babbling << '\n';
            answer++;
        }
    }
    return answer;
}
