#include <bits/stdc++.h>
#define INF 20000000
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/118669
  2022 KAKAO TECH INTERNSHIP
  등산코스 정하기
  ---
*/
vector<int> solution(int n, 
                     vector<vector<int>> paths, 
                     vector<int> gates, 
                     vector<int> summits) {
    
    vector<vector<pair<int, int> > > path_info(n+1, vector<pair<int, int> >());
    for(vector<int> path: paths) {
        path_info[path[0]].push_back({path[1], path[2]});
        path_info[path[1]].push_back({path[0], path[2]});
    }
    
    vector<int> answer(2, INF);
    queue<pair<int, int> > q;
    vector<int> chk(n+1, INF);
    
    vector<bool> is_gate(n+1, false);
    vector<bool> is_summit(n+1, false);
    for(int gate: gates) {
        q.emplace(gate, 0);
        is_gate[gate] = true;
    }
    for(int summit: summits) is_summit[summit] = true;
        
    while(!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        
        for(pair<int, int> info: path_info[p.first]) {
            if(is_gate[info.first]) continue;
            
            int current_max_intensity = max(p.second, info.second);
            if(chk[info.first] > current_max_intensity) {
                chk[info.first] = current_max_intensity;
                if(!is_summit[info.first]) q.emplace(info.first, current_max_intensity);
            }
        }
    }

    
    sort(summits.begin(), summits.end());
    for(int summit : summits) {
        if(answer[1] > chk[summit]) {
            answer[0] = summit;
            answer[1] = chk[summit];
        }
    }

    return answer;
}
