//2020 KAKAO BLIND RECRUITMENT 문자열 압축 

#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

void init_divisor(queue<int> &s, int len){
    for(int i=1; i < len; i++){
        s.push(i);
    }
}

void concat_string(string &temp, string &prev, int &cnt){
    if(cnt!=1){
        temp += (to_string(cnt) + prev);
    }else{
        temp += prev;
    }
    cnt = 1;
}

int solution(string s) {
    queue<int> divisors;
    int str_size = s.size();
    int answer = str_size;
    int cnt = 1;
    string temp = "";
    init_divisor(divisors, str_size);
    
    while(!divisors.empty()){
        temp = "";
        int divisor = divisors.front();
        divisors.pop();
        
        string prev = s.substr(0, divisor);
        for(int i=divisor; i<str_size; i+=divisor){
            string current_sub_str = s.substr(i, divisor);
            if(prev.compare(current_sub_str) != 0){
                concat_string(temp, prev, cnt);
                prev = current_sub_str;
            }else{
                cnt++;
            }
            
            if((i+divisor) >= str_size){
                concat_string(temp, prev, cnt);
            }
        }
        if(temp.size() < answer) answer = temp.size();
    }
    return answer;
}
