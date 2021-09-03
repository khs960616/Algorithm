#include <string>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

vector<int> init_vector(){
    vector<int> v(5,0);
    v[4] = 1;
    
    for(int i=3; i>=0;i--){
        v[i] = v[i+1] + pow(5,4-i);
    }
    return v;
}
void init_map(map<char,int> &m){
    m.insert(make_pair('A',0));
    m.insert(make_pair('E',1));
    m.insert(make_pair('I',2));
    m.insert(make_pair('O',3));
    m.insert(make_pair('U',4));
}

int solution(string word) {
    vector<int> v = init_vector();
    map<char, int> m;
    init_map(m);
    int len = word.length();
    int answer = 0;
    for(int i=0;i<len;i++){
        answer += (v[i]*(m[word[i]])+1);
    }
    return answer;
}
