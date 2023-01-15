#include <bits/stdc++.h>

using namespace std;

vector<int> answer = {0, 0};
vector<int> discounts;
int n, m;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/150368
  이모티콘 할인행사
  ---
  구현, 브루트포스, 조합
*/
void brute_force(int idx, vector<vector<int>>& users, vector<int>& emoticons) {
    if(idx >= m) {
        vector<int> users_cost(n, 0);
        for(int i=0; i<m; ++i) {
            int discount_cost = (emoticons[i] * discounts[i]) / 100;
            int current_cost = emoticons[i] - discount_cost;
            for(int j=0; j<n; ++j) {
                if(users[j][0] > discounts[i]) continue;
                else users_cost[j] += current_cost;
            }
        }
        
        int plus_services = 0, total_prices = 0;
        for(int i=0; i<n; ++i) {
            if(users[i][1] <= users_cost[i]) {
                plus_services++;
                continue;
            }
            total_prices += users_cost[i];
        }
  
        if(answer[0] < plus_services) {
            answer[0] = plus_services;
            answer[1] = total_prices;
        } else if(answer[0] == plus_services) {
            answer[1] = max(answer[1], total_prices);
        }
        return;
    }
    
    for(int i=10; i<50; i+=10) {
        discounts[idx] = i;
        brute_force(idx+1, users, emoticons);
    }
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    n = users.size(), m = emoticons.size();
    discounts = vector<int>(m, 0);
    brute_force(0, users, emoticons);
    return answer;
}
