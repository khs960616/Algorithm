/*
https://leetcode.com/problems/decode-ways/

A -> 1
Z -> 26  으로 각각의 알파벳이 number에 match 된다.

string s로 숫자로 변환된 문자열이 주어질 때, 이를 매칭시킬 수 있는 문자열의 갯수를 return 해야한다.
---
memoization
v[i][0] : 순서쌍의 마지막 수가 1 또는 2인 원소들의 개수
v[i][1] : 순서쌍의 마지막 수가 3~26 사이인 원소들의 개수

*/

class Solution {
public:
    int numDecodings(string s) {
        if(s[0] == '0') return 0;
        
        int answer = 0;
        int sLength = s.length();
        vector<vector<int>> v(sLength, vector<int>(2, 0));
        int num = s[0] - '0';
        
        if(num == 1 || num == 2) ++v[0][0];
        else ++v[0][1];
        
        for(int i=1; i<sLength; ++i) {
            num = s[i] - '0';
            if(num == 0) {
                if(!v[i-1][0]) return 0;
                else {
                    v[i][1] = v[i-1][0];
                    continue;
                }
            }
            
            if(num < 3) v[i][0] = v[i-1][0] + v[i-1][1];
            else v[i][1] = v[i-1][0] + v[i-1][1];
            
            int prevValue = stoi(s.substr(i-1, 2));
            if(prevValue<27) v[i][1] += v[i-1][0];
        }
        
        answer = v[sLength-1][0] + v[sLength-1][1];
        return answer;
    }
};
