// 프로그래머스 
// 수의 규칙 찾기
#include <string>
#include <vector>

using namespace std;

string solution(int n) {
    string answer = "";
    while(n>0){
        int mod = n%3;
        n/=3;
        
        if(mod == 0){
            answer = "4" + answer;
            n-=1;
        } else{
            answer = to_string(mod) + answer;
        }
    }    
    return answer;
}
