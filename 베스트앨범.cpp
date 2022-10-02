#include <bits/stdc++.h>
using namespace std;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/42579
베스트앨범
---
구현
*/
bool cmp(pair<int, int> p1, pair<int, int> p2) {
    if(p1.first == p2.first) return p1.second < p2.second;
    return p1.first > p2.first;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    unordered_map<string, int> genres_played_count;
    unordered_map<string, vector<pair<int, int> > > genres_music_list;
    
    vector<int> answer;
    int music_cnt = genres.size();
    for(int i=0; i<music_cnt; ++i) {
        string genre = genres[i];
        genres_played_count[genre] += plays[i];
        genres_music_list[genre].emplace_back(plays[i], i);
    }
    
    priority_queue<pair<int, string> > pq;
    for(auto a: genres_played_count) {
        pq.emplace(a.second, a.first);
    }
    
    while(!pq.empty()) {
        string genre = pq.top().second;
        pq.pop();
        sort(genres_music_list[genre].begin(), genres_music_list[genre].end(), cmp);
        
        int end_size = (genres_music_list[genre].size() == 1) ? 1 : 2;
        for(int i=0; i<end_size; ++i) {
            answer.push_back(genres_music_list[genre][i].second);
        }
    }
    
    return answer;
}
