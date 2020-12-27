#include <string>
#include <vector>
#include <map>
using namespace std;

int solution(vector<vector<string>> clothes) {
    map<string,int> cloth_info;
    int answer = 1;
    for(int i=0; i < clothes.size(); i++){
        cloth_info[clothes[i][1]] ++;
    }
    map<string, int>::iterator iter;
    for(iter=cloth_info.begin();iter!=cloth_info.end();iter++){
        answer *= ((iter->second)+1);
    }
    answer-=1;
    return answer;
}
