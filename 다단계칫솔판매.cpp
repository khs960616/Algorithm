#include <bits/stdc++.h>
using namespace std;

int member_size = 0; 
int parent[100001];
unordered_map<string, int> name_index_map;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/77486
  다단계 칫솔 판매
  ---
  트리
  
  1. 조직도를 트리 형태로 구성한다.
     >> 조직도의 index를 이용해서 각 트리의 구조를 나타낸다. (만일 자기 자신의 부모가 자신의 index와 같다면 해당 노드는 서브 트리의 루트임을 의미한다.)
     
  2. 현재 자신이 얻을 수 있는 이득은 90%만 자기자신이 가지고, 10%는 부모 노드에게 전달한다. 
*/
void save_name_index_map(vector<string> enroll) {
    for(int i=0; i<member_size; ++i) name_index_map[enroll[i]] = i;
}

void save_parent_info(vector<string> enroll, vector<string> referral) {
    for(int i=0; i<member_size; ++i) {
        if(referral[i] == "-") {
            parent[i] = i;
            continue;
        }
        
        parent[i] = name_index_map[referral[i]];
    }
}

void add_cost_to_parent(vector<int>& cost, int child_idx, int remain) {
    int parent_idx = parent[child_idx];
    if(parent_idx == child_idx) return;
    
    int next_cost = remain/10;
    cost[parent_idx] += (remain-next_cost);
    add_cost_to_parent(cost, parent_idx, next_cost);
}

vector<int> calc_cost(vector<string> seller, vector<int> amount) {
    vector<int> ret(member_size, 0);
    int amount_size = amount.size();
    
    for(int i=0; i<amount_size; ++i) {
        int current_idx = name_index_map[seller[i]];
        ret[current_idx] += (amount[i] * 90);
        add_cost_to_parent(ret, current_idx, amount[i]*10);
    }

    return ret;
}

vector<int> solution(vector<string> enroll, 
                     vector<string> referral, 
                     vector<string> seller, 
                     vector<int> amount) {
    member_size = enroll.size();
    save_name_index_map(enroll);
    save_parent_info(enroll, referral);
    return calc_cost(seller, amount);
}
