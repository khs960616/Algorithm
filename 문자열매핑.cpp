#include <bits/stdc++.h>

using namespace std;

/*
  주어진 패턴이 존재할 때 문자열이 해당 패턴에 매칭 되느냐 여부를 검사하는 로직..
  토큰 단위로 분리한 뒤, 각 패턴에 대응되는 문자를 대입하며 확인한다.
  만일 패턴에 대응되는 문자가 이미 map에 들어있는데, 현재 문자가 map에 들어있는 문자와 다르면 
  패턴에 일치하지 못함을 의미한다.
*/
vector<string> get_tokens(string s) {
    stringstream ss(s);
    string token;
    vector<string> tokens;

    while (ss >> token) tokens.push_back(token);
    return tokens;
}

bool is_match(string pattern, vector<string> tokens) {
    map<char, string> pattern_mapper;
    int len = pattern.length();

    for(int i=0; i<len; ++i) {
        if(pattern_mapper.find(pattern[i]) == pattern_mapper.end()) {
            pattern_mapper[pattern[i]] = tokens[i];
            continue;
        }

        if(pattern_mapper[pattern[i]] != tokens[i]) return false;
    }
    return true;
}

int main() {
    string pattern = "abab";
    string s = "dog cat dog cat";
    vector<string> tokens = get_tokens(s);

    if(is_match(pattern, tokens)) cout << "match\n";

}
