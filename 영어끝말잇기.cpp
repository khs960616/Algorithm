#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12981
  영어 끝말잇기
  ----
  간단 구현 
*/
vector<int> solution(int n, vector<string> words) {
    vector<int> answer(2, 0);
    map<string, bool> mp;
    mp[words[0]] = true;
    
    int wordSize = words.size();
    char lastChar = words[0].back();
    
    for(int i=1; i<wordSize; ++i) {
        if(words[i].front() != lastChar || mp.find(words[i]) != mp.end()) {
            int humanNum = (i % n) + 1;
            int currentHumanTurn = (i / n) + 1;
            answer[0] = humanNum;
            answer[1] = currentHumanTurn;
            break;
        }
        
        lastChar = words[i].back();
        mp[words[i]] = true;
    }
    return answer;
}
