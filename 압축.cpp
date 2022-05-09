#include <bits/stdc++.h>
/*
https://programmers.co.kr/learn/courses/30/lessons/17684#
2018 KAKAO BLIND RECRUITMENT
[3차 압축]
--------
구현
*/
using namespace std;

vector<int> solution(string msg) {
    vector<int> answer;
    vector<string> v = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
        "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
        "U", "V", "W", "X", "Y", "Z"
    };
    
    int msgSize = msg.size();
    int i = 0;      
    while(i < msgSize) {
        int cnt = 2;

        while(msgSize-i-cnt >= 0) {
            //현재 position (=i)를 기준으로 뒤쪽 substring들이 dictionary(=v)에 존재하는지 체크한다.
            string substr = msg.substr(i, cnt);
            auto iter = find(v.begin(), v.end(), substr);
            if(iter == v.end()) {
                //만일 substring들을 검사하다 dictionary에 존재하지 않는 단어가 존재한다면 dictionary에 넣어준다.
                v.push_back(substr);
                break;
            }
            ++cnt;
        }
        
        //해당 position을 기점으로 하는 가장 긴 substring의 색인을 answer에 넣어준다.
        int index = find(v.begin(), v.end(), msg.substr(i, cnt-1)) - v.begin() + 1;
        answer.push_back(index);
        
        i+=(cnt-1);
    }
    
    return answer;
}
