#include <bits/stdc++.h>

using namespace std;

/*
https://www.acmicpc.net/problem/1043
그래프, 구현
*/

bool isNotContainTrues(vector<int> party, set<int> s) {
    for(int i: s) {
        if(find(party.begin(), party.end(), i) != party.end()) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, trues;
    cin >> n >> m;
    cin >> trues;
    vector<vector<int>> partys(m, vector<int>());
    vector<int> v(trues, 0);
    map<int, set<int>> mp;
    set<int> s;

    for(int i=0; i<trues; ++i) {
        cin >> v[i];
    }   

    for(int i=0; i<m; ++i) {
        int num;
        cin >> num;

        for(int j=0; j<num; ++j){
            int people;
            cin >> people;
            partys[i].push_back(people);
        }

        for(int j=0; j<num; ++j) {
            for(int k=0; k<num; ++k) {
                if(j == k) continue;
              // 문제조건에 의해서 하나라도 같은 파티에 참여한적 있는 사람끼리는 그래프로 관계를 표시해줘야함
                mp[partys[i][j]].insert(partys[i][k]);
                mp[partys[i][k]].insert(partys[i][j]);
            }
        }
    }
     
    // 진실을 아는 사람과 한번이라도 같은 파티에 참여한 사람(1), 혹은 (1)과 같은 파티에 참여한 사람들은 모두 과장되지 않은 이야기를 들어야함 
    vector<int> isVisit(n+1, false);
    for(int i=0; i< trues; ++i) {
        isVisit[v[i]] = true;

        queue<int> q;
        q.push(v[i]);
        //그래프의 연결상태를 체크하며, 만일 이야기의 진실을 아는사람과 접촉한 사람들은 모두 set에 넣어줌
        while(!q.empty()) {
            int i = q.front();
            s.insert(i);
            q.pop();
            for(auto connect: mp[i]) {
                if(isVisit[connect]) continue;
                isVisit[connect] = true;
                q.push(connect);
            }
        }
    }

    int answer = 0;
    for(vector<int> party : partys) {
        if(isNotContainTrues(party, s)) answer++; 
    }  
    
    cout << answer;
    return 0;   
}
