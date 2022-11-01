#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/15811
  복연산?!
  DFS
  ---
  브루트 포스 
  
  1. 주어진 string에 존재하는 모든 문자의 종류를 구한다.
  2. 각 문자에 0~9까지의 수를 대입해본다, 단 서로 다른 문자는 서로 다른 수가 되야한다는 조건을 만족하도록 매칭한다.
  3. 존재하는 모든 문자에 숫자가 대입해보았다면, 주어진 string 덧셈이 올바른지 확인한 후 결과를 return한다.
*/
vector<char> v;
int word_match[27];
int character_type = 0;
bool is_used[10];
bool flag = false;

int convert_string_to_num(string s) {
    int ret = 0;

    for(char c: s) {
        ret *= 10;
        ret += word_match[c-'A'];
    }

    return ret;
}

void dfs(string& s1, string& s2, string& s3, int cnt) {
    if(flag) return;
    if(cnt == character_type) {
        int a = convert_string_to_num(s1);
        int b = convert_string_to_num(s2);
        int c = convert_string_to_num(s3);
        if(a+b == c) flag = true;
        return;
    }

    for(int i=0; i<10; ++i) {
        if(is_used[i]) continue;
        is_used[i] = true;
        word_match[v[cnt]-'A'] = i;
        dfs(s1, s2, s3, cnt+1);
        is_used[i] = false;
    }
}

int main() {
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    unordered_set<int> characters;
    for(char c: s1) characters.insert(c);
    for(char c: s2) characters.insert(c);
    for(char c: s3) characters.insert(c);
    character_type = characters.size();

    if(character_type > 10) cout << "NO";
    else {
        v = vector<char>(character_type);
        copy(characters.begin(), characters.end(), v.begin());

        dfs(s1, s2, s3, 0);
        if(flag) cout << "YES";
        else cout << "NO";
    }
}
