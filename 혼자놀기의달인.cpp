#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/131130
  혼자 놀기의 달인
  ---
  dfs, 재귀
  
  1. cards를 각각 서브그룹으로 나눈다.
    - 서브 그룹 유형 1) cards[i]-1 = i 
    - 서브 그룹 유형 2) cards[i]-1를 이용해 순차적으로 순회를 할 때 cycle이 생기는 경우 
  
  2. 서브그룹이 존재하지 않는다면 0을 출력하며, 서브그룹이 여러개 존재하면, 그중 크기가 큰 2개의 서브그룹의 크기를 곱하여 return
*/
int card_size = 0;
vector<bool> is_visit;

void get_sub_group_size(vector<int> cards, int current, int& cnt) {
    if(is_visit[current]) return;
    
    is_visit[current] = true;
    cnt+=1;
    get_sub_group_size(cards, cards[current]-1, cnt);
}

int solution(vector<int> cards) {
    card_size = cards.size();
    is_visit = vector<bool>(card_size, false);
    
    vector<int> sub_group;
    sub_group.push_back(0);
    
    for(int i=0; i<card_size; ++i) {
        if(is_visit[i]) continue;
        int cnt = 1;
        is_visit[i] = true;
        get_sub_group_size(cards, cards[i]-1, cnt);
        sub_group.push_back(cnt);
    }
    
    sort(sub_group.begin(), sub_group.end(), greater<>());
    return sub_group[0] * sub_group[1];
}
