//프로그래머스 - 위클리 챌린지 7주차

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//먼저 들어가고 나중에 나간 것이 확실한 경우 반드시 만난다. 
vector<int> solution(vector<int> enter, vector<int> leave) {
    int esize = enter.size(); int cnt =0;
    vector<int> answer(esize, 0);
    vector<int> seq;
    
    for(int i=0; i<esize;i++){
        seq.push_back(enter[i]);
        for(cnt; cnt<esize; cnt++){
            auto iter = find(seq.begin(), seq.end(), leave[cnt]);
            if(iter!=seq.end()){
                seq.erase(iter);
                answer[leave[cnt]-1] +=(seq.size());
                for(int i:seq){
                    answer[i-1]++;
                }
            }else{
                break;
            }
        }
    }
    return answer;
}
