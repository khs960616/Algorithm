//프로그래머스 - 카펫
//브루트포스, 약수 구하기 

#include <string>
#include <vector>
using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    vector<int> divisors;
    int total = brown+yellow;

    for(int i=1; i<total; i++){
        if(total % i == 0){
            int w = i > (total/i) ? i : (total/i);
            int h = i < (total/i) ? i : (total/i);
            int bound = (w+h)*2-4;
            if(bound == brown){
                answer.push_back(w);
                answer.push_back(h);
                break;
            }
        }
    }
    return answer;
}
