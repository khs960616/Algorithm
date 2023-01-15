#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> answer;
set<string> s;

/*
  https://www.acmicpc.net/problem/15666
  n과 m(12)
  ---
  백트래킹, 조합 
*/

string get_prev_string(int idx) {
    string ret = "";
    for(int i=0; i<idx; ++i) {
        ret += to_string(answer[i]);
        if(i!=idx-1) ret += ' ';
    }
    return ret;
}

void solve(vector<int>& v, int idx) {
    if(idx == m) {
        for(int i: answer) cout << i << ' ';
        cout << '\n';
        return;
    }

    string prev_s = get_prev_string(idx);
    for(int i=0; i<n; ++i) {
        if(idx != 0 && answer[idx-1] > v[i]) continue;

        string current_s = prev_s + ' ' + to_string(v[i]);
        if(s.find(current_s) != s.end()) continue;

        s.insert(current_s);
        answer[idx] = v[i];
        solve(v, idx+1);
        answer[idx] = 0;
    }
}

int main() {
    cin >> n >> m;
    vector<int> v(n, 0);
    answer = vector<int> (m, 0);

    for(int i=0; i<n; ++i) cin >> v[i];
    sort(v.begin(), v.end());
    solve(v, 0);
}
