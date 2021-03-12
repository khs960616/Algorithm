#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    map<string, int> m;
    
    for(string a : completion){
        m[a] ++;
    }
    
    for(string a : participant){
        if(m[a]==0){answer = a;}
        m[a] --;
    }
    return answer;
}
