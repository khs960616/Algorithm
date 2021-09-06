//프로그래머스 - 최대값과 최솟값
//문자열 파싱, 정렬 

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string solution(string s) {
    string number = "";
    vector<int> v;
    for(char c: s){
        if(c == ' '){
            v.push_back(stoi(number));
            number = "";
        } else{
            number += c;
        }
    }
    v.push_back(stoi(number));
    sort(v.begin(), v.end());
    number = to_string(v[0]) + ' ' + to_string(v[v.size()-1]);
    return number;
}
