#include <bits/stdc++.h>

using namespace std;

vector<bool> isVisit(8, false);
vector<int> selectedColumn(8, 0);

/*
2019 KAKAO BLIND RECRUITMENT
https://programmers.co.kr/learn/courses/30/lessons/42890

DFS를 이용한 조합 알고리즘 
최소성 조건 

---

*/

void dfs(const vector<vector<string>>& relation,
        set<string>& candidateKey,
        const int columnSize,
        const int cnt,
        const int target) {
    
    if(cnt == target) {
        //유일성 체크
        set<string> s;
        for(vector<string> r: relation) {
            string concatString = "";
            for(int i=0; i<cnt; ++i) {
                concatString += r[selectedColumn[i]];
            }
            s.insert(concatString);
        }
        if(relation.size() != s.size()) return;
        
        //키 값 생성 
        string key = "";
        for(int i=0; i<cnt; ++i) {
            key+=to_string(selectedColumn[i]);
        }

        //키가 최소성을 만족하는지 체크 (이전에 키값으로 들어간 키의 char를 하나씩 뜯어서 만일 현재 키값에 해당값들이 다 포함되어있다면 최소성을 만족하지 않음)
        for(string c: candidateKey) {
            int keySize = c.size();
            int cnt=0;
            for(char ch: c) {
                if(key.find(ch) != std::string::npos) ++cnt;
                if(keySize == cnt) return;
            }
        }
        candidateKey.insert(key);
        return;
    }
    
    //조합
    for(int i=0; i<columnSize; ++i) {
        // 다음과 같이 조합을 오름차순으로 뽑게되면 두가지 이점이 있음 1. 키값이 정렬된 순서로 생성됨 2. 중복되는 키값을 체크하지 않으므로 함수 호출이 적어짐
        if(cnt!=0 && selectedColumn[cnt-1] >= i) continue;
        
        if(!isVisit[i]) {
            isVisit[i] = true;
            selectedColumn[cnt] = i;
            dfs(relation, candidateKey, columnSize, cnt+1, target);
            isVisit[i] = false;
        }
    }
}

int solution(vector<vector<string>> relation) {
    set<string> candidateKey;
    
    int columnSize = relation[0].size();
    for(int i=1; i<=columnSize; ++i) {
        dfs(relation, candidateKey, columnSize, 0, i);
    }

    return candidateKey.size();
}
