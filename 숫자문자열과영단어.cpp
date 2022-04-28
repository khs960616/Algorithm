/*
https://programmers.co.kr/learn/courses/30/lessons/81301

2021 카카오 채용연계형 인턴십

문자열 문제 
*/

#include <bits/stdc++.h>

using namespace std;

int solution(string s) {
    vector<string> alphaNum = {"zero", "one", "two", "three", "four",
                     "five", "six", "seven", "eight", "nine"};
    string num_string = "";
    string temp = "";
    for (char c: s) {
        if (c>='0' && c<='9') {
            num_string += c;
        } else {
            temp+=c;
            if (temp != "") {
                auto iter = find(alphaNum.begin(), alphaNum.end(), temp);
                if(iter != alphaNum.end()) {
                    char n = (iter - alphaNum.begin())+'0';
                    num_string += n;
                    temp = "";
                }
            }
        }
    }
    
    return stoi(num_string);
}
