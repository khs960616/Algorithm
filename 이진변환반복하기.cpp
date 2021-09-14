//월간 코드 챌린지 이진변환 반복하기
//문자열 처리 

#include <string>
#include <vector>
using namespace std;

string remove_zero(string s){
    string result = "";
    for(char c : s){
        if(c!='0') result+=c;
    }
    return result;
}

string convert_length(string s){
    int ssize = s.size();
    string result = "";
    while(ssize!=0){
        result = to_string(ssize%2) + result;
        ssize/=2;
    }
    return result;
}

vector<int> solution(string s) {
    int cnt = 0; int remove_cnt = 0;
    
    while(s.size()!=1){
        int pre_size = s.size();
        s = remove_zero(s);
        remove_cnt +=(pre_size-s.size());
        s = convert_length(s);
        cnt++;
    }
    
    vector<int> answer;
    answer.push_back(cnt);
    answer.push_back(remove_cnt);
    return answer;
}
