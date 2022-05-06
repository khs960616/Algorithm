#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/72412
2021 KAKAO BLIND RECRUITMENT
순위검색
문자열 파싱, map
---
조합의 경우 2^4 = 16가지밖에 없으므로 코드상으로 중첩이 깊어보여도 2중 for문을 도는거보다 훨씬 적음 50,000 * 100,000 ,  (50,000 * 15 + 100,000)
*/
vector<bool> isVisit(4, false);
vector<int> selectedIdx(4, -1);
vector<vector<int>> combinations;

void parseQueryInfo(string s, string& key, int& score) {
    stringstream ss(s);
    string lang, job, career, food, tmp;
    ss >> lang >> tmp >> job >> tmp >> career >> tmp >> food >> score;
    if(lang!="-") key+=lang;
    if(job!="-") key+=job;
    if(career!="-") key+=career;
    if(food!="-") key+=food;
}

void dfs(int cnt, int target) {
    if(cnt == target) {
        vector<int> combination;
        for(int i=0; i<cnt; ++i) {
            combination.push_back(selectedIdx[i]);
        }
        combinations.push_back(combination);
        return;    
    }
    
    for(int i=0; i<4; ++i) {
        if(cnt!=0 && selectedIdx[cnt-1]>=i) continue;
        if(!isVisit[i]) {
            isVisit[i] = true;
            selectedIdx[cnt] = i;
            dfs(cnt+1, target);
            isVisit[i] = false;
        }
    }
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    map<string, vector<int> > infoMaps; 
    //조합 생성
    for(int i=1; i<5; ++i) {
        dfs(0, i);
    }
    //info 정보 map에 저장
    for(string s: info) {
        stringstream ss(s);
        string token;
        vector<string> tokens;
        while(getline(ss, token, ' ')) {
            tokens.push_back(token);
        }
        
        int score = stoi(tokens[4]);
        infoMaps[""].push_back(score);
        
        for(vector<int> combination: combinations) {
            string key = "";
            for(int num : combination) {
                key+=tokens[num];
            }
            infoMaps[key].push_back(score);
        }
    }
    
    for(auto& infoMap: infoMaps) {
        sort(infoMap.second.begin(), infoMap.second.end());
    }
    
    //query의 score 보다 map에 저장되어있는 수가 더 크면 카운트값 증가! 
    for(string s: query) {
        string key = "";
        int score = 0;
        parseQueryInfo(s, key, score);
        vector<int> v = infoMaps[key];
        int value = v.end() - lower_bound(v.begin(), v.end(), score);
        answer.push_back(value);
    }
    return answer;
}
