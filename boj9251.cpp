#include <bits/stdc++.h>

/*
https://www.acmicpc.net/problem/9251
LCS
-----------------------------------
DP, LCS

ex) 
ACAYKP
CAPCAK
*/
using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int s1Size = s1.size()+1; // 기저값을 설정해주기 위해 string의 길이보다 1개 크게 잡는다.
    int s2Size = s2.size()+1;

    vector<vector<int>> v(s1Size, vector<int>(s2Size, 0));

    for(int i=1; i<s1Size; ++i) {
        for(int j=1; j<s2Size; ++j) {
            if(s1[i-1] == s2[j-1]) {
                v[i][j] = v[i-1][j-1]+1; 
              /*
                만일 s1의 i번째, s2의 j번째 원소가 같은 경우,
                s1의 i-1번째, s2의 j-1번째 원소까지 값을 검사했을 때, 최대 공통 수열인 것 뒤에 현재 원소값을 추가한 것이 부분 최적해가 된다.
              */
            } else {
              /* 
                현재 검사했던 각 string의 원소가 일치하지 않았으므로 길이가 증가하지는 않으며, 
              */
                v[i][j] = max(v[i-1][j], v[i][j-1]);
            }
        }
    }

    cout << v[s1Size-1][s2Size-1];
    return 0;   
}
