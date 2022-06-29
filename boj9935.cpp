#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/9935
문자열 폭팔
문자열, 스택
------
Deque를 stack처럼 활용한다.
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string s, explosion;
    cin >> s >> explosion;
    
    int eSize = explosion.size();
    deque<char> st;

    for(char c: s) {
        st.push_back(c);
        int stackSize = st.size();
        if(stackSize < eSize) continue;

        string checkTop = "";
        for(int i = stackSize-eSize; i<stackSize; ++i) {
            checkTop += st[i];
        }

        if(checkTop == explosion) {
            for(int i=0; i<eSize; ++i) st.pop_back();
        }
    }

    if(st.empty()) cout << "FRULA";
    else {
        for(char c: st) cout << c;
    }
    return 0;
}
