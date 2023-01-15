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


/*

동일한 조합은 결국, call stack의 depth가 동일할 떄, ans 배열에 동일한 값을 넣을 때,
결과적으로 값이 동일한 함수를 중복해서 호출할 때 생성된다.
따라서 동일한 depth에서 동일한 값을 가진 함수 호출을 줄이면 된다. 이를 위해 이전에 함수 호출에 쓰인 값이 다시 쓰이지 않도록 만들면 된다. 

#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> answer;

void solve(vector<int>& v, int idx) {
    if(idx == m) {
        for(int i: answer) cout << i << ' ';
        cout << '\n';
        return;
    }

    int last = 0;
    for(int i=0; i<n; ++i) {
        if(idx != 0 && answer[idx-1] > v[i]) continue;
        if(last == v[i]) continue; // 함수 호출전 이미 v벡터는 정렬이 된 상태이므로, 별도 추가 조건을 걸지 않아도 중복호출이 발생하지 않는다. 
        
        last = v[i];
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

*/
