/*
  https://programmers.co.kr/learn/courses/30/lessons/92334?language=cpp
  2022 카카오 블라인드 
  문자열 
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    set<string> stop;
    map<string, int> reportCount;
    map<string, set<string>> userReportInfo;
    
    for (string id: id_list) {
        userReportInfo[id] = set<string>();
        reportCount[id] = 0;
    }
    
    for (string s: report) {
        int idx = s.find(' ');
        string user = s.substr(0, idx);
        string reportedUser = s.substr(idx+1);
        
        if(userReportInfo[user].find(reportedUser) == userReportInfo[user].end()) {
            userReportInfo[user].insert(reportedUser);
            ++reportCount[reportedUser];
        }
    }
    
    for (string id: id_list) {
        int mailCount = 0;
        for(string s : userReportInfo[id]) {
            if(reportCount[s] >= k) mailCount++;
        }
        answer.push_back(mailCount);
    }
    
    return answer;
}
