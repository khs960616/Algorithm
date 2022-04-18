/*
https://leetcode.com/problems/word-break/

 string s와 dictionary wordDict이 주어진다.
 s가 wordDict에 있는 string들도 구성될 수 있는지 참/거짓을 반환
dictionary에 있는 각 단어는 소문자로 이루어져있으며 중복해서 사용 가능하며 각 단어는 unique하다. 

---
1. string s의 사이즈 + 1 만큼의 벡터를 생성한다. 
   - v[i]의 의미는 v[0]~v[i-1]까지를 포함하는 subString을 dictionary에 존재하는 단어로 만들 수 있음을 의미한다.
   
2. 0~sSize-1 만큼 반복문을 돌며, dictionary에 있는 단어들이 해당 반복문의 순서의 인덱스로 이어서 subString으로 만들수 있는지를 검사한다.

-> 차후 다시 풀어볼 것 

*/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int sSize = s.size();
        vector<bool> v(sSize+1, false); 
        v[0] = true;
        
        for(int i=0; i<sSize; ++i) {
            if(!v[i]) continue;
            
            for(string word: wordDict) {
                int wSize = word.size();
                if(s.substr(i, wSize).compare(word) == 0) {
                    v[i+wSize] = true;
                }
            }
        }
        return v[sSize];
    }
};
