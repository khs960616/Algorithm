#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/138476
  귤고르기
  ---
  크기가 동일한 갯수가 많은 귤부터 먼저 넣으면, 
  k개의 귤을 담았을 때, 귤의 종류가 최소가 된다.
*/
unordered_map<int, int> size_cnt_map;
int solution(int k, vector<int> tangerines) {
    int answer = 0;
    vector<pair<int, int> > v;
    for(int tangerine : tangerines) {
        size_cnt_map[tangerine]++;
    }
    
    for(auto i: size_cnt_map) {
        v.emplace_back(i.second, i.first);
    }
    
    sort(v.begin(), v.end(), greater<>());
    for(pair<int, int> p: v) {
        answer++;
        if(p.first >= k) break;
        k-=p.first;
    }
    
    return answer;
}
