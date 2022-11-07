#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/133501
  야간 전술보행
  정렬
*/
int solution(int distance, 
             vector<vector<int>> scopes, 
             vector<vector<int>> times) {
    
    int n = scopes.size();

    vector<tuple<int, int, int> > scope_infos;
    for(int i=0; i<n; ++i) {
        int start = min(scopes[i][0], scopes[i][1]);
        int end = max(scopes[i][0], scopes[i][1]);
        scope_infos.emplace_back(start, end, i);
    }
    sort(scope_infos.begin(), scope_infos.end());
    
    for(auto [start, end, idx]: scope_infos) {
        int total_time = times[idx][0] + times[idx][1];
        
        for(int time=start; time<=end; ++time) {
            int rm = time % total_time;
            if(rm > 0 && rm <= times[idx][0]) return time;
        }
    }
    
    return distance;
}
