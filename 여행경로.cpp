#include <bits/stdc++.h>
using namespace std;

/*
    https://school.programmers.co.kr/learn/courses/30/lessons/43164
    여행경로
    ---
    DFS
    1. 도착지를 기준으로 tickets 배열을 오름차순 정렬한다.
    2. 현재 도시를 기준으로, 사용가능한 이동권 써서, 도시를 이동한다.
    3. (1)번에서 tickets 배열을 도착지 기준 오름차순으로 정렬하였으므로, 최초 모든 항공권을 다 쓰는 경우가, 사전순으로 가장 앞에 있는 여행경로가 된다.
*/


bool flag = false;
int t_size = 0;
vector<string> answer;

bool cmp(vector<string> v1, vector<string> v2) {
    return v1[1] < v2[1];
}

void dfs(string current_city,
         vector<string> paths,
         vector<bool> is_used, 
         vector<vector<string>> tickets) {
    if(flag) return;  // 이미 답을 구한 경우, 더 이상 함수를 실행시킬 필요가 없다.
    
    paths.push_back(current_city);
    if(paths.size() == t_size+1) {
        flag = true;
        answer = paths;
        return;
    }
    
    for(int i=0; i<t_size; ++i) {
        if(is_used[i] || (current_city != tickets[i][0])) continue;
        is_used[i] = true;
        dfs(tickets[i][1], paths, is_used, tickets);
        is_used[i] = false;
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    t_size = tickets.size();
    stable_sort(tickets.begin(), tickets.end(), cmp);
    
    vector<bool> is_used(t_size, false);
    vector<string> paths;
    dfs("ICN", paths, is_used, tickets);
    return answer;
}
