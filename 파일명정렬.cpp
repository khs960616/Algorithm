#include <bits/stdc++.h>

using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/17686#
2018 KAKAO BLIND RECRUITMENT
[3차] 파일명 정렬
-----
문자열 파싱, 정렬 
stable_sort  vs unstable_sort
값이 같은 경우에 기존과 순서를 동일하게 유지하는지, 값의 정렬만 이루어지고, 실질적인 순서 (index)는 교환이 가능한가에 대한 차이 
https://lemonlemon.tistory.com/136 (관련 포스팅중 가장 정리가 잘 되있는듯)

(stl 내부에서의 sorting 방식 
https://debugjung.tistory.com/entry/stl%EC%97%90%EC%84%9C-%EA%B5%AC%ED%98%84%ED%95%9C-intro-sort-%EC%B0%B8%EC%A1%B0)
*/

vector<string> divideString(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    int flag = 0, stringSize = s.size();
    string head = "", number = "", tail = "";
    
    for(int i=0; i<s.size(); ++i) {
        bool isNumber = s[i]>='0' && s[i]<='9';
        
        if(flag == 0) {
            if(isNumber) {
                flag = 1;
                number+=s[i];
                continue;
            }
            head+=s[i];
        } else if(flag == 1) {
            if(!isNumber || number.size()>4) {
                tail+=s[i];
                flag = 2;
                continue;
            }
            number+=s[i];
        } else {
            tail+=s[i];
        }
    }

    return {head, number, tail};
}

bool compare(string s1, string s2) {
    vector<string> tokens1 = divideString(s1);
    vector<string> tokens2 = divideString(s2);
    
    int num1 = stoi(tokens1[1]);
    int num2 = stoi(tokens2[1]);
    if(tokens1[0] == tokens2[0]) if(num1 != num2) return num1 < num2;

    return tokens1[0] < tokens2[0];
}

vector<string> solution(vector<string> files) {
    vector<string> answer = files;
    stable_sort(answer.begin(), answer.end(), compare);
    return answer;
}
